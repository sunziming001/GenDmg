#include "LuaEngine.h"
#include "CoreDefine.h"
#include "windows.h"


LuaEngine* LuaEngine::instance=nullptr;



int LuaResourceLoader(lua_State* L)
{
	const char* name = luaL_checkstring(L, 1);  // Module name
	std::string luaFile = std::string(name) + ".lua";

	BOOL loadSuccess = FALSE;
	BOOL luaSuccess = FALSE;

	std::string text = LuaEngine::getInstance()->loadResource(luaFile);
	
	if (luaL_loadbufferx(L, (const char*)text.c_str(), text.length(), name, nullptr) != LUA_OK)
	{
		luaSuccess = FALSE;
	}
	else {
		luaSuccess = TRUE;
	}
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
	//������Դ
	HGLOBAL hGlobal = ::LoadResource(hModule, hRsrc);
	if (NULL == hGlobal)
		return ret;
	//������Դ
	LPVOID pBuffer = ::LockResource(hGlobal);
	if (NULL == pBuffer)
		return ret;
	//��ȡ��Դ�Ĵ�С
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

void LuaEngine::initResourceLoader()
{
	lua_register(luaState_, "resource_loader", LuaResourceLoader);

	std::string     str;

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
	loadScript("main.lua");
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
	text = loadResource(fileName, tag);
	

	if (luaL_dostring(luaState_, text.c_str()) != LUA_OK)
	{
		printf("Error: %s\n", lua_tostring(luaState_, -1));
		lua_pop(luaState_, 1); // pop error message
	}
}

