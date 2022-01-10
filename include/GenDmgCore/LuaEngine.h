#ifndef _LUA_ENGINE_H
#define _LUA_ENGINE_H

#include <string>
#include <set>
extern "C"
{
#include "lua.h"  
#include "lualib.h" 
#include "lauxlib.h" 

};

class LuaEngine {
public:
	static LuaEngine* getInstance();
	~LuaEngine();

	void init();
	void uninit();

	void loadScript(const std::string& fileName, const std::string& tag="");
	std::string loadResource(const std::string& fileName, const std::string& tag="");
private:
	LuaEngine();
	
	std::string loadResourceWithouSearch(const std::string& fileName, const std::string& tag);
	void initResourceLoader();
private:
	static LuaEngine* instance;
	lua_State* luaState_;
	std::set<std::string> luaResTag_;
};


#endif