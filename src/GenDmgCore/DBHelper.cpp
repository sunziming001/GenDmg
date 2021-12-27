#include "DBHelper.h"
#include "sqlite3.h"
#include <string>
#include "CoreLogger.h"


DBHelper* DBHelper::getInstance()
{
	if (nullptr == instance)
		instance = new DBHelper;

	return instance;
}

void DBHelper::init()
{
	initCharacterTable();


}

void DBHelper::uninit()
{

}

DBHelper::~DBHelper()
{

}

void DBHelper::insertCharacterBrief(CharacterBrief& bref)
{
	sqlite3* db = nullptr;
	sqlite3_stmt* pstmt = nullptr;
	sqlite3_stmt* pstmtId = nullptr;
	const char* zErrMsg = nullptr;
	const char* pTail = nullptr;
	int rc = 0;
	rc = sqlite3_open(DB_FILE_PATH, &db);
	if (rc) {
		std::string errLog = std::string("open error: ") + sqlite3_errmsg(db);
		LOG_ERROR("DBHelper", errLog.c_str());
		return;
	}

	std::string sqlBrief = "insert into tb_char_brief (name, img_path, dmg_type) values (?,?,?);";
	rc = sqlite3_prepare_v2(db, sqlBrief.c_str(), sqlBrief.length()+1,&pstmt, nullptr);
	if (rc != SQLITE_OK) {
		sqlite3_close(db);
		LOG_ERROR("DBHelper", "sqlBrief prepare error");
		return ;
	}
	std::string name = bref.getName();
	std::string imgPath = bref.getImgPath();
	int dmgType = static_cast<int>(bref.getDmgType());
	sqlite3_bind_text(pstmt, 1, name.c_str(), name.length()+1, nullptr);
	sqlite3_bind_text(pstmt, 2, imgPath.c_str(), imgPath.length() + 1, nullptr);
	sqlite3_bind_int(pstmt, 3, dmgType);
	rc = sqlite3_step(pstmt);
	if (SQLITE_DONE != rc)
	{
		zErrMsg = sqlite3_errmsg(db);
		std::string errLog = std::string("insert tb_char_brief error: ") + sqlite3_errmsg(db);
		LOG_ERROR("DBHelper", errLog.c_str());
	}
	sqlite3_reset(pstmt);
	sqlite3_finalize(pstmt);
	pstmt = nullptr;

	int id =static_cast<int>(sqlite3_last_insert_rowid(db));
	bref.setId(id);

	sqlite3_close(db);
}

std::vector<CharacterBrief> DBHelper::selectAllCharacterBrief()
{
	std::vector<CharacterBrief> ret;

	sqlite3* db = nullptr;
	sqlite3_stmt* pstmt = nullptr;
	const char* zErrMsg = nullptr;
	const char* pTail = nullptr;
	int rc = 0;
	std::string sqlSelectBrief = "select id, name, dmg_type, img_path from tb_char_brief;";

	rc = sqlite3_open(DB_FILE_PATH, &db);
	if (rc) {
		std::string errLog = std::string("open error: ") + sqlite3_errmsg(db);
		LOG_ERROR("DBHelper", errLog.c_str());
		return ret;
	}

	//query briefs
	rc = sqlite3_prepare_v2(db, sqlSelectBrief.c_str(), -1, &pstmt, NULL);
	if (rc != SQLITE_OK)
	{
		std::string errLog = std::string("prepare sqlSelectBrief error: ") + sqlite3_errmsg(db);
		LOG_ERROR("DBHelper", errLog.c_str());
		sqlite3_close(db);
		return ret;
	}
	else {
		while (sqlite3_step(pstmt) == SQLITE_ROW) {
			CharacterBrief brief;
			brief.setId(sqlite3_column_int(pstmt, 0));
			brief.setName((const char*)(sqlite3_column_text(pstmt, 1)));
			brief.setDmgType(static_cast<DamageType>(sqlite3_column_int(pstmt, 2)));
			brief.setImgPath((const char*)(sqlite3_column_text(pstmt, 3)));
			ret.push_back(brief);
		}
	}
	sqlite3_reset(pstmt);
	sqlite3_finalize(pstmt);
	pstmt = nullptr;

	
	sqlite3_close(db);
	return ret;
}

void DBHelper::insertLvProps(int charId, const std::set<CharacterLvProp>& lvProps)
{
	sqlite3* db = nullptr;
	sqlite3_stmt* pstmt = nullptr;
	sqlite3_stmt* pstmtId = nullptr;
	const char* zErrMsg = nullptr;
	const char* pTail = nullptr;
	int rc = 0;
	rc = sqlite3_open(DB_FILE_PATH, &db);
	std::string sqlLv = "insert into tb_char_lv_detail(char_id,is_break,lv,atk,def,hp,sp_prop_type,sp_prop)values(?,?,?,?,?,?,?,?);";

	rc = sqlite3_prepare_v2(db, sqlLv.c_str(), sqlLv.length() + 1, &pstmt, nullptr);
	if (rc != SQLITE_OK) {
		zErrMsg = sqlite3_errmsg(db);
		std::string errLog = std::string("prepare tb_char_brief error: ") + sqlite3_errmsg(db);
		LOG_ERROR("DBHelper", errLog.c_str());
		sqlite3_close(db);
		return;
	}

	for (auto iter = lvProps.begin();
		iter != lvProps.end();
		iter++)
	{
		sqlite3_bind_int(pstmt, 1, charId);
		sqlite3_bind_int(pstmt, 2, iter->getIsBreak()?1:0);
		sqlite3_bind_int(pstmt, 3, iter->getLv());
		sqlite3_bind_int(pstmt, 4, iter->getAtk());
		sqlite3_bind_int(pstmt, 5, iter->getDef());
		sqlite3_bind_int(pstmt, 6, iter->getHp());
		sqlite3_bind_int(pstmt, 7, static_cast<int>(iter->getSpPropType()));
		sqlite3_bind_double(pstmt, 8, iter->getSpPropValue());

		rc = sqlite3_step(pstmt);
		if (SQLITE_DONE != rc)
		{
			zErrMsg = sqlite3_errmsg(db);
			std::string errLog = std::string("insert tb_char_lv_detail error: ") + sqlite3_errmsg(db);
			LOG_ERROR("DBHelper", errLog.c_str());
		}
		sqlite3_reset(pstmt);
	}
	sqlite3_finalize(pstmt);
	pstmt = nullptr;


	sqlite3_close(db);
}

std::set<CharacterLvProp> DBHelper::selectLvProps(int charId)
{
	std::set<CharacterLvProp> ret;

	sqlite3* db = nullptr;
	sqlite3_stmt* pstmt = nullptr;
	const char* zErrMsg = nullptr;
	const char* pTail = nullptr;
	int rc = 0;
	std::string sqlSelectLvProp = "select is_break, lv, atk, def, hp, sp_prop_type, sp_prop from tb_char_lv_detail where char_id= ? ";

	rc = sqlite3_open(DB_FILE_PATH, &db);
	if (rc) {
		std::string errLog = std::string("open error: ") + sqlite3_errmsg(db);
		LOG_ERROR("DBHelper", errLog.c_str());
		return ret;
	}

	rc = sqlite3_prepare_v2(db, sqlSelectLvProp.c_str(), -1, &pstmt, NULL);
	if (rc != SQLITE_OK)
	{
		std::string errLog = std::string("prepare sqlSelectLvProp error: ") + sqlite3_errmsg(db);
		LOG_ERROR("DBHelper", errLog.c_str());
		sqlite3_close(db);
		return ret;
	}
	else {
		sqlite3_bind_int(pstmt, 1, charId);
		while (sqlite3_step(pstmt) == SQLITE_ROW) {
			//is_break, lv, atk, def, hp, sp_prop_type, sp_prop
			CharacterLvProp prop;
			prop.setIsBreak(sqlite3_column_int(pstmt, 0)==1);
			prop.setLv(sqlite3_column_int(pstmt, 1));
			prop.setAtk(sqlite3_column_int(pstmt, 2));
			prop.setDef(sqlite3_column_int(pstmt, 3));
			prop.setHp(sqlite3_column_int(pstmt, 4));
			prop.setSpPropType(static_cast<SpecialPropType>(sqlite3_column_int(pstmt, 5)));
			prop.setSpPropValue(sqlite3_column_double(pstmt, 6));

			ret.insert(prop);
		}
	}

	sqlite3_close(db);
	return ret;
}

bool DBHelper::updateLvProps(int charId, const std::set<CharacterLvProp>& lvProps)
{
	bool ret = true;
	sqlite3* db = nullptr;
	sqlite3_stmt* pstmt = nullptr;
	const char* zErrMsg = nullptr;
	const char* pTail = nullptr;
	int rc = 0;
	std::string sql = "update tb_char_lv_detail set "
		"atk = ?,"
		"def = ?,"
		"hp = ?,"
		"sp_prop_type = ?,"
		"sp_prop = ?"
		" where char_id = ? and is_break = ? and lv = ?";

	rc = sqlite3_open(DB_FILE_PATH, &db);
	if (rc) {
		std::string errLog = std::string("open error: ") + sqlite3_errmsg(db);
		LOG_ERROR("DBHelper", errLog.c_str());
		return false;
	}

	rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &pstmt, NULL);
	if (rc != SQLITE_OK)
	{
		std::string errLog = std::string("prepare updateLvProps error: ") + sqlite3_errmsg(db);
		LOG_ERROR("DBHelper", errLog.c_str());
		sqlite3_close(db);
		ret = false;
	}
	else {
		for (auto iter = lvProps.begin();
			iter != lvProps.end();
			iter++)
		{
			sqlite3_bind_int(pstmt, 1, iter->getAtk());
			sqlite3_bind_int(pstmt, 2, iter->getDef());
			sqlite3_bind_int(pstmt, 3, iter->getHp());
			sqlite3_bind_int(pstmt, 4, static_cast<int>(iter->getSpPropType()));
			sqlite3_bind_double(pstmt, 5, iter->getSpPropValue());

			sqlite3_bind_int(pstmt, 6, charId);
			sqlite3_bind_int(pstmt, 7, iter->getIsBreak() ? 1 : 0);
			sqlite3_bind_int(pstmt, 8, iter->getLv());

			rc = sqlite3_step(pstmt);
			if (SQLITE_DONE != rc)
			{
				zErrMsg = sqlite3_errmsg(db);
				std::string errLog = std::string("update tb_char_lv_detail error: ") + sqlite3_errmsg(db);
				LOG_ERROR("DBHelper", errLog.c_str());
				ret = false;
				break;
			}
			sqlite3_reset(pstmt);
		}
		sqlite3_finalize(pstmt);
		pstmt = nullptr;
	}

	sqlite3_close(db);
	return ret;
}

DBHelper::DBHelper()
{

}

void DBHelper::initCharacterTable()
{
	sqlite3* db = nullptr;
	char* zErrMsg = nullptr;
	int rc = 0;

	rc = sqlite3_open(DB_FILE_PATH, &db);
	if (rc) {
		std::string errLog = std::string("open error: ")+sqlite3_errmsg(db);
		LOG_ERROR("DBHelper", errLog.c_str());
		return;
	}

	std::string sql_char_brief = "create table IF NOT EXISTS "
		"tb_char_brief(id integer primary key autoincrement, "
		"name text not null,"
		"dmg_type integer not null,"
		"img_path text not null);";

	std::string sql_char_lv_detail = "create table IF NOT EXISTS "
		"tb_char_lv_detail("
		"char_id integer not null,"
		"is_break integer not null,"
		"lv integer not null, "
		"atk integer not null,"
		"def integer not null,"
		"hp integer not null,"
		"sp_prop_type integer not null,"
		"sp_prop real not null,"
		" PRIMARY KEY (char_id, is_break, lv)"
		");";


	rc = sqlite3_exec(db, sql_char_brief.c_str(), 0, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		std::string errLog = std::string("create tb_char_brief failed: ") + zErrMsg;
		LOG_ERROR("DBHelper", errLog.c_str());
	}

	rc = sqlite3_exec(db, sql_char_lv_detail.c_str(), 0, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		std::string errLog = std::string("create tb_char_lv_detail failed: ") + zErrMsg;
		LOG_ERROR("DBHelper", errLog.c_str());
	}

	sqlite3_close(db);
}

DBHelper* DBHelper::instance;
