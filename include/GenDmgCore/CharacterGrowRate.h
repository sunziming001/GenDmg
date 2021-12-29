#ifndef _CHARACTER_GROW_RATE_H
#define _CHARACTER_GROW_RATE_H

#include "CoreDefine.h"
#include <map>
#include <string>

class CharacterGrowRate
{
public:
	DLL_EXPORT CharacterGrowRate();
	DLL_EXPORT ~CharacterGrowRate();
	DLL_EXPORT bool operator<(const CharacterGrowRate& prop) const;

	DLL_EXPORT int getId() const;
	DLL_EXPORT void setId(int val);
	DLL_EXPORT std::string getName() const;
	DLL_EXPORT void setName(std::string val);

	DLL_EXPORT void setLvRate(int lv, double rate);
	DLL_EXPORT double getLvRate(int lv, bool* isOk = nullptr)const;
private:
	int id_ = 0;
	std::string name_;
	std::map<int,double> mapLv2Rate_;
};

#endif