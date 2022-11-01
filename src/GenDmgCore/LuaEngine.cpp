#include "LuaEngine.h"
#include "CoreDefine.h"
#include "windows.h"
#include <iostream>
#include <algorithm>

LuaEngine* LuaEngine::instance=nullptr;



int LuaResourceLoader(lua_State* L)
{
	const char* name = luaL_checkstring(L, 1);  // Module name

	LuaEngine::getInstance()->loadLuaModule(name);
	return 1;
}


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
	std::string text;
	if (!tag.empty())
	{
		text = loadResourceWithouSearch(fileName, tag);
	}
	else {
		for (std::string resTag : luaResTag_)
		{
			text = loadResourceWithouSearch(fileName, resTag);
			if (!text.empty())
			{
				break;
			}
		}
	}
	return text;
}

std::string LuaEngine::loadResourceWithouSearch(const std::string& fileName, const std::string& tag)
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



std::map<std::string, int> LuaEngine::genDmgList(const std::string& luaPath, const CharacterConfig* conf)
{
	std::map<std::string, int> ret;

	lua_getglobal(luaState_, "SetCharacterConf");

	lua_newtable(luaState_);

	lua_pushinteger(luaState_, conf->getBaseHp());
	lua_setfield(luaState_, -2, "baseHp");

	lua_pushinteger(luaState_, conf->getBaseAtk());
	lua_setfield(luaState_, -2, "baseAtk");

	lua_pushinteger(luaState_, conf->getBaseDef());
	lua_setfield(luaState_, -2, "baseDef");

	lua_pushinteger(luaState_, (int)conf->getSpecialPropType());
	lua_setfield(luaState_, -2, "specialPropType");

	lua_pushnumber(luaState_, (int)conf->getSpecialPropVal());
	lua_setfield(luaState_, -2, "specialPropVal");

	if (lua_pcall(luaState_, 1, 0, 0) != 0)
	{
		std::string err = lua_tostring(luaState_, -1);
		std::cerr << err << std::endl;
	}

	doScript(luaPath, "LUACHAR");
	


	return ret;
}

void LuaEngine::initResourceLoader()
{
	lua_register(luaState_, "resource_loader", LuaResourceLoader);

	std::string str;

	//  str += "table.insert(package.loaders,   2, my_loader) \n";   // Older than lua v5.2
	str += "table.insert(package.searchers, 2, resource_loader) \n";

	luaL_dostring(luaState_, str.c_str());
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
		initResourceLoader();
	}

#ifdef _DEBUG
	AllocConsole();
	FILE* fDummy;
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
#endif

	doScript("character.lua", "LUACORE");
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

void LuaEngine::doScript(const std::string& fileName, const std::string& tag)
{
	std::string text;
	text = loadResource(fileName, tag);
	

	if (luaL_dostring(luaState_, text.c_str()) != LUA_OK)
	{
		printf("Error: %s\n", lua_tostring(luaState_, -1));
		lua_pop(luaState_, 1); // pop error message
	}
}

void LuaEngine::loadLuaModule(const std::string& moduleName, const std::string& tag)
{
	BOOL luaSuccess = FALSE;
	std::string luaFile = moduleName;

	if (moduleName.find(".lua") == std::string::npos)
	{
		luaFile += ".lua";
	}

	std::string text = LuaEngine::getInstance()->loadResource(luaFile, tag);
	
	int errcode = luaL_loadbufferx(luaState_, (const char*)text.c_str(), text.length(), moduleName.c_str(), nullptr);

	if (errcode != LUA_OK)
	{
		char const* msg = lua_tostring(luaState_, -1);
		std::string message = msg ? msg : "null string";

		std::string context = "When parsing a string to lua, ";

		if (errcode == LUA_ERRSYNTAX) {
			context += " a syntax error";
		}
		else if (errcode == LUA_ERRMEM) {
			context += " a memory error";
		}
		else if (errcode == LUA_ERRGCMM) {
			context += " an error in garbage collection metamethod";
		}
		else {
			context += " an unknown error";
		}

		lua_pop(luaState_, 1);

		lua_pushfstring(luaState_, "can't load module '%s'", moduleName);

		std::cerr << message << std::endl;
		std::cerr << context<<std::endl;
	}
}


