#ifndef _STRING_CODEC_H
#define _STRING_CODEC_H

#include <windows.h>

#include <string>


namespace base {

	std::wstring Utf8ToUnicode(const char* sUtf8)
	{
		//UTF8 to Unicode 
		int sLen = MultiByteToWideChar(CP_UTF8, NULL, sUtf8, -1, NULL, 0);
		wchar_t* sUnicode = new wchar_t[sLen];
		MultiByteToWideChar(CP_UTF8, NULL, sUtf8, -1, sUnicode, sLen);

		std::wstring ret(sUnicode);

		delete[] sUnicode;
		sUnicode = NULL;

		return ret;
	}

	std::string UnicodeToAnsi(const wchar_t* sUnicode)
	{
		//unicode to ansi
		int sLen = WideCharToMultiByte(CP_ACP, NULL, sUnicode, -1, NULL, 0, NULL, NULL);
		char* sAnsi = new char[sLen];

		WideCharToMultiByte(CP_ACP, NULL, sUnicode, -1, sAnsi, sLen, NULL, NULL);


		std::string ret(sAnsi);
		delete[] sAnsi;
		sAnsi = NULL;

		return ret;
	}



	std::string UnicodeToUtf8(const wchar_t* sUnicode)
	{

		// unicode to UTF8 
		int sLen = WideCharToMultiByte(CP_UTF8, NULL, sUnicode, -1, NULL, 0, NULL, NULL);
		//UTF8虽然是Unicode的压缩形式，但也是多字节字符串，所以可以以char的形式保存 
		char* sUtf8 = new char[sLen];
		//unicode版对应的strlen是wcslen 
		WideCharToMultiByte(CP_UTF8, NULL, sUnicode, -1, sUtf8, sLen, NULL, NULL);
		std::string ret(sUtf8);

		delete[] sUtf8;
		sUtf8 = NULL;


		return ret;
	}

	std::wstring AnsiToUnicode(const char* sAnsi)
	{
		//ansi to unicode
		int sLen = MultiByteToWideChar(CP_ACP, NULL, sAnsi, -1, NULL, 0);
		wchar_t* sUnicode = new wchar_t[sLen];
		//wchar_t* sUnicode = (wchar_t*)malloc(sLen*sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, NULL, sAnsi, -1, sUnicode, sLen);

		std::wstring ret(sUnicode);

		delete[] sUnicode;
		sUnicode = NULL;
		//free(sUnicode);

		return ret;
	}

	std::string  Utf8ToANSI(const char* str)
	{
		std::wstring strUnicode = Utf8ToUnicode(str);
		std::string strAnsi = UnicodeToAnsi(strUnicode.c_str());
		return strAnsi;
	}

	std::string AnsiToUtf8(const char* str)
	{
		std::wstring unicodeStr = AnsiToUnicode(str);
		std::string strUtf8 = UnicodeToUtf8(unicodeStr.c_str());

		return strUtf8;
	}

}


#endif
