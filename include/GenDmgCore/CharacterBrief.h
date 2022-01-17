#ifndef CHARACTER_BRIEF_H
#define CHARACTER_BRIEF_H

#include "CoreDefine.h"
#include <string>
#include <set>
#include "DamageCell.h"



class CharacterBrief
{
public:
	DLL_EXPORT CharacterBrief();
	DLL_EXPORT ~CharacterBrief();
	DLL_EXPORT int getId() const;
	DLL_EXPORT void setId(int val);
	DLL_EXPORT std::string getName() const;
	DLL_EXPORT void setName(const std::string& val);
	DLL_EXPORT std::string getImgPath() const;
	DLL_EXPORT void setImgPath(const std::string& val);
	DLL_EXPORT DamageType getDmgType() const;
	DLL_EXPORT void setDmgType(DamageType val);
	DLL_EXPORT std::string getLuaPath() const; 
	DLL_EXPORT void setLuaPath(std::string val);
private:
	int id_;
	std::string name_;
	std::string imgPath_;
	std::string luaPath_;
	DamageType dmgType_;
};


#endif