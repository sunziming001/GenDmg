#ifndef _DB_HELPER_H
#define _DB_HELPER_H

#include"CharacterBrief.h"
#include"CharacterLvProp.h"
#include <vector>

#define DB_FILE_PATH "./genshin.db"


class DBHelper
{
public:
	static DBHelper* getInstance();
	void init();
	void uninit();
	~DBHelper();

	void insertCharacterBrief(CharacterBrief& bref);
	std::vector<CharacterBrief> selectAllCharacterBrief();

	void insertLvProps(int charId, const std::set<CharacterLvProp>& lvProps);
	std::set<CharacterLvProp> selectLvProps(int charId);
	bool updateLvProps(int charId, const std::set<CharacterLvProp>& lvProps);
private:
	DBHelper();
	void initCharacterTable();

private:
	static DBHelper* instance;
};


#endif