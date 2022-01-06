#ifndef _DB_HELPER_H
#define _DB_HELPER_H

#include"CharacterBrief.h"
#include"CharacterLvProp.h"
#include "CharacterGrowRate.h"
#include <vector>
#include <functional>

#define DB_FILE_PATH "./genshin.db"
enum class DBType
{
	Integer,
	Text,
	Real
};
struct sqlite3_stmt;
struct sqlite3;

typedef std::function<void(sqlite3_stmt* pstmt)> SqlPrepareCallback;
typedef std::function<void(int rc, sqlite3_stmt* pstmt)> SqlStepCallback;

class DBHelper
{
public:
	static DBHelper* getInstance();
	void init();
	void uninit();
	~DBHelper();

	void insertCharacterBrief(CharacterBrief& bref);
	std::vector<CharacterBrief> selectAllCharacterBrief();
	CharacterBrief selectCharacterBrief(int charId, bool& isOk);
	void updateCharacterBrief(const CharacterBrief& brief);

	void insertLvProps(int charId, const std::set<CharacterLvProp>& lvProps);
	std::set<CharacterLvProp> selectLvProps(int charId);
	bool updateLvProps(int charId, const std::set<CharacterLvProp>& lvProps);

	void insertCharacterGrowRate(CharacterGrowRate& rate);
	CharacterGrowRate selectCharacterGrowRate(int id);
	void updateCharacterGrowRate(CharacterGrowRate& rate);
	std::set<CharacterGrowRate> selectAllCharacterGrowRate();
private:
	DBHelper();
	void initCharacterTable();

	bool openDB(sqlite3** db);
	bool closeDB(sqlite3* db);
	bool execSql(sqlite3* db, 
		const std::string& sql, 
		SqlPrepareCallback prepCb =nullptr, 
		SqlStepCallback stepCb=nullptr);

	void sqlite3_bind_string(sqlite3_stmt* pstmt, int indx, const std::string& text);
private:
	static DBHelper* instance;
	static const int SkillLvCnt = 13;
};


#endif