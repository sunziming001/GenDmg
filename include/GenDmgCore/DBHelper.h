#ifndef _DB_HELPER_H
#define _DB_HELPER_H

#include"CharacterBrief.h"
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
private:
	DBHelper();
	void initCharacterTable();

private:
	static DBHelper* instance;
};


#endif