
#ifndef _RMT_OPER_LOGGER_H
#define _RMT_OPER_LOGGER_H

#include "CommonLogger.h"

#define LOG_TYPE_NAME "Core"



#define  LOG_INIT(lv) \
{\
Logger* logger = Logger::getInstance();\
std::map<std::string, LoggerInfo> loggerInfos;\
LoggerInfo rmtOperInfo;\
rmtOperInfo.typeName = LOG_TYPE_NAME;\
rmtOperInfo.minLogLevel = static_cast<LogLevel>((lv));\
loggerInfos[LOG_TYPE_NAME] = rmtOperInfo;\
logger->init(loggerInfos);\
}


#define  LOG_UNINIT() \
{\
	Logger* logger = Logger::getInstance();\
	logger->uninit();\
}


#define LOG_TRACE(tag,txt) LOG_TRACE_WITH_TYPE(tag, txt, LOG_TYPE_NAME)
#define LOG_DEBUG(tag,txt) LOG_DEBUG_WITH_TYPE(tag, txt, LOG_TYPE_NAME)
#define LOG_INFO(tag,txt) LOG_INFO_WITH_TYPE(tag, txt, LOG_TYPE_NAME)
#define LOG_ERROR(tag,txt) LOG_ERROR_WITH_TYPE(tag, txt, LOG_TYPE_NAME)
#define LOG_WARN(tag,txt) LOG_WARN_WITH_TYPE(tag, txt, LOG_TYPE_NAME)
#define LOG_FATAL(tag,txt) LOG_FATAL_WITH_TYPE(tag, txt, LOG_TYPE_NAME)


#endif
