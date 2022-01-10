#include "LuaEngine.h"
#include "CoreDefine.h"
#include "windows.h"


LuaEngine* LuaEngine::instance=nullptr;

LuaEngine* LuaEngine::getInstance()
{
	if (nullptr == instance)
		instance = new LuaEngine;
	return instance;
}

LuaEngine::LuaEngine()
	:luaState_(nullptr)
{

}


std::string LuaEngine::loadResource(const std::string& fileName, const std::string& tag)
{
	std::string ret;

	HMODULE hModule = ::GetModuleHandleA(MODULE_NAME);
	HRSRC hRsrc = ::FindResourceA(hModule, fileName.c_str(), tag.c_str());

	if (NULL == hRsrc)
		return ret;
	//加载资源
	HGLOBAL hGlobal = ::LoadResource(hModule, hRsrc);
	if (NULL == hGlobal)
		return ret;
	//锁定资源
	LPVOID pBuffer = ::LockResource(hGlobal);
	if (NULL == pBuffer)
		return ret;
	//获取资源的大小
	DWORD dwSize = ::SizeofResource(hModule, hRsrc);
	if (0 == dwSize)
		return ret;

	try
	{

		ret = std::string((char*)pBuffer, dwSize);

	}
	catch (...)
	{
		::FreeResource(hGlobal);
		return ret;
	}

	::FreeResource(hGlobal);
	return ret;
}

LuaEngine::~LuaEngine()
{

}

void LuaEngine::init()
{
	luaResTag_.insert("LUACORE");
	luaResTag_.insert("LUACHAR");

	if (luaState_ == nullptr)
	{
		luaState_ = luaL_newstate();
		luaL_openlibs(luaState_);
	}

#ifdef _DEBUG
	AllocConsole();
	FILE* fDummy;
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
#endif
	loadScript("test.lua", "LUACORE");
}

void LuaEngine::uninit()
{
	if (luaState_ != nullptr)
	{
		lua_close(luaState_); 
		luaState_ = nullptr;
	}

#ifdef _DEBUG
	FreeConsole();
#endif
}

void LuaEngine::loadScript(const std::string& fileName, const std::string& tag)
{
	std::string text;
	if (!tag.empty())
	{
		text = loadResource(fileName, tag);
	}
	else {
		for (std::string resTag : luaResTag_)
		{
			text = loadResource(fileName, tag);
			if(!text.empty())
			{ 
				break;
			}
		}
	}
	

	if (luaL_dostring(luaState_, text.c_str()) != LUA_OK)
	{
		printf("Error: %s\n", lua_tostring(luaState_, -1));
		lua_pop(luaState_, 1); // pop error message
	}
}


