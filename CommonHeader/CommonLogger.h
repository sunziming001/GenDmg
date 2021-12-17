#ifndef _COMMON_LOGGER_H
#define _COMMON_LOGGER_H

#include <string>
#include <set>
#include <iostream>
#include <locale>
#include <fstream>
#include <vector>
#include <queue>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>
#include <boost/thread.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <iostream>


enum class LogLevel {
	Trace,
	Debug,
	Info,
	Warn,
	Error,
	Fatal,
	None,
};

typedef struct _LoggerInfo
{
	std::string dir="./log/";
	std::string typeName= "default";
	std::string filePath;
	unsigned int maxFileInDir = 5;
	LogLevel minLogLevel = LogLevel::Trace;

	bool operator<(const _LoggerInfo& v)const
	{
		std::string s1 = dir + typeName;
		std::string s2 = v.dir + v.typeName;

		return s1 < s2;
	}
}LoggerInfo;

typedef struct _LoggerData
{
	std::string filePath;
	std::string txt;
}LoggerData;



class Logger {

private:
	Logger() 
		:loggerThread_(nullptr)
		,isLoggerThreadRunning_(false)
	{
	
	}
public:
	~Logger() {}

	static Logger* getInstance()
	{
		static Logger* instance = nullptr;
		if (instance == nullptr)
			instance = new Logger;
		return instance;
	}
	
	void init(const std::map<std::string, LoggerInfo>& loggerInfos = { std::make_pair("default",LoggerInfo()) })
	{
		loggerInfos_ = loggerInfos;
		for (auto iter = loggerInfos_.begin(); iter != loggerInfos_.end(); iter++)
		{
			LoggerInfo& ref = iter->second;
			initLogger(ref);
		}

		startLoggerThread();
	}

	void uninit()
	{
		stopLoggerThread();
		loggerInfos_.clear();
	}

	void writeLog(LogLevel lv, const std::string& tag, const std::string& txt, const std::string typeName)
	{
		std::string lvTxt = getLvString(lv);
		std::string timeTxt = getFormatTimeString("%H:%M:%S%F");
		std::string threadTxt = boost::lexical_cast<std::string>(boost::this_thread::get_id());
		auto iter = loggerInfos_.find(typeName);
		if (iter != loggerInfos_.end())
		{
			LoggerInfo& info = iter->second;
			if (lv >= info.minLogLevel)
			{
				std::string logTxt = timeTxt + " " + lvTxt + "\t[" + tag + "](" + threadTxt + ") " + txt;
				postLog(info.filePath, logTxt);
				std::cout << logTxt << std::endl;
			}
			
		}
	}

private:
	void initLogger(LoggerInfo& loggerInfo)
	{
		boost::filesystem::path dstFolder = loggerInfo.dir;
		boost::filesystem::create_directories(dstFolder);
		const boost::regex my_filter(loggerInfo.typeName+".*.log");
		std::vector<std::string> oldFiles;

		loggerInfo.filePath = genNewFilePath(loggerInfo);
		

		//search old files
		boost::filesystem::directory_iterator end_itr; // Default ctor yields past-the-end
		for (boost::filesystem::directory_iterator i(loggerInfo.dir); i != end_itr; ++i)
		{
			// Skip if not a file
			if (!boost::filesystem::is_regular_file(i->status())) continue;

			boost::smatch what;

			if( !boost::regex_match( i->path().filename().string(), what, my_filter ) ) continue;

			// File matches, store it
			oldFiles.push_back(i->path().filename().string());
		}

		//delete old files
		if (oldFiles.size() > loggerInfo.maxFileInDir)
		{
			std::sort(oldFiles.begin(), oldFiles.end());
			for (unsigned int i = 0; i < oldFiles.size() - loggerInfo.maxFileInDir; i++)
			{
				std::string filePath = loggerInfo.dir + "/" + oldFiles[i];
				boost::filesystem::remove(filePath);
			}

		}

		//create file
		std::fstream fs(loggerInfo.filePath.c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);
		fs.close();

		
	}

	std::string genNewFilePath(const LoggerInfo& loggerInfo)
	{
		//std::string timeTail = getFormatTimeString("_%Y_%m_%d_%H_%M_%S%F");
		std::string timeTail = getFormatTimeString("_%Y_%m_%d_%H_%M_%S");
		std::string ret = loggerInfo.dir + "/" + loggerInfo.typeName + timeTail + ".log";
		return ret;
	}

	std::string getFormatTimeString(const std::string& format)
	{
		const boost::posix_time::ptime time = boost::posix_time::microsec_clock::local_time();
		std::stringstream stream;
		boost::posix_time::time_facet* facet = new boost::posix_time::time_facet();
		facet->format(format.c_str());
		stream.imbue(std::locale(std::locale::classic(), facet));
		stream << time;

		return stream.str();
	}

	std::string getLvString(LogLevel lv)const
	{
		std::string ret;
		switch (lv)
		{
		case LogLevel::Trace:
			ret = "[Trace]";
			break;
		case LogLevel::Debug:
			ret = "[Debug]";
			break;
		case LogLevel::Info:
			ret = "[Info]";
			break;
		case LogLevel::Warn:
			ret = "[Warn]";
			break;
		case LogLevel::Error:
			ret = "[Error]";
			break;
		case LogLevel::Fatal:
			ret = "[Fatal]";
			break;
		case LogLevel::None:
			ret = "None";
			break;
		default:
			ret = "[Unknown]";
			break;
		}

		return ret;
	}

	void postLog(const std::string& filePath, const std::string& txt)
	{
		boost::lock_guard<boost::mutex> guard(queueMutex_);
		LoggerData data;
		data.filePath = filePath;
		data.txt = txt;
		loggerQueue_.push(data);
	}

	void procLoggerData(const LoggerData& data)
	{
		std::fstream fs(data.filePath.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
		fs << data.txt << std::endl;
		fs.close();
	}

	void procLoggerQueue()
	{
		boost::lock_guard<boost::mutex> guard(queueMutex_);

		while (!loggerQueue_.empty())
		{
			auto& data = loggerQueue_.front();
			procLoggerData(data);
			loggerQueue_.pop();
		}
	}

	void startLoggerThread()
	{
		if (isLoggerThreadRunning_)
		{
			return;
		}
		isLoggerThreadRunning_ = true;
		loggerThread_ = new boost::thread([this]() {
			while (isLoggerThreadRunning_)
			{
				procLoggerQueue();
				boost::this_thread::sleep_for(boost::chrono::milliseconds(300));
			}

			procLoggerQueue();
		});
	}

	void stopLoggerThread()
	{
		isLoggerThreadRunning_ = false;
		if (loggerThread_ != nullptr
			&& loggerThread_->try_join_for(boost::chrono::seconds(3)))
		{
			loggerThread_->interrupt();
		}

		if (loggerThread_)
		{
			delete loggerThread_;
			loggerThread_ = nullptr;
		}
		
	}
private:
	std::map<std::string, LoggerInfo> loggerInfos_;
	std::queue<LoggerData> loggerQueue_;
	boost::mutex queueMutex_;
	boost::thread *loggerThread_;
	bool isLoggerThreadRunning_;
};



#define LOG_TRACE_WITH_TYPE(tag, txt, logType) Logger::getInstance()->writeLog(LogLevel::Trace,tag,txt,logType);
#define LOG_DEBUG_WITH_TYPE(tag, txt, logType) Logger::getInstance()->writeLog(LogLevel::Debug,tag,txt,logType);
#define LOG_INFO_WITH_TYPE(tag, txt, logType) Logger::getInstance()->writeLog(LogLevel::Info,tag,txt,logType);
#define LOG_WARN_WITH_TYPE(tag, txt, logType) Logger::getInstance()->writeLog(LogLevel::Warn,tag,txt,logType);
#define LOG_ERROR_WITH_TYPE(tag, txt, logType) Logger::getInstance()->writeLog(LogLevel::Error,tag,txt,logType);
#define LOG_FATAL_WITH_TYPE(tag, txt, logType) Logger::getInstance()->writeLog(LogLevel::Fatal,tag,txt,logType);

#endif