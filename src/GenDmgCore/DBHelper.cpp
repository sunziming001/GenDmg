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
	sqlite3_bind_string(pstmt, 1, name);
	sqlite3_bind_string(pstmt, 2, imgPath);
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

CharacterBrief DBHelper::selectCharacterBrief(int charId, bool& isOk)
{
	isOk = false;

	CharacterBrief ret;
	sqlite3* db = nullptr;
	sqlite3_stmt* pstmt = nullptr;
	const char* zErrMsg = nullptr;
	const char* pTail = nullptr;
	int rc = 0;
	std::string sql = "select id, name, dmg_type, img_path from tb_char_brief where id = ?;";

	rc = sqlite3_open(DB_FILE_PATH, &db);
	if (rc) {
		std::string errLog = std::string("open error: ") + sqlite3_errmsg(db);
		LOG_ERROR("DBHelper", errLog.c_str());
		return ret;
	}


	rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length() + 1, &pstmt, nullptr);
	if (rc != SQLITE_OK) {
		zErrMsg = sqlite3_errmsg(db);
		std::string errLog = std::string("prepare tb_char_brief error: ") + sqlite3_errmsg(db);
		LOG_ERROR("DBHelper", errLog.c_str());
		sqlite3_close(db);
		return ret;
	}
	else {
		sqlite3_bind_int(pstmt, 1, charId);

		if (sqlite3_step(pstmt) == SQLITE_ROW) {
			ret.setId(charId);
			ret.setName((const char*)sqlite3_column_text(pstmt, 1));
			ret.setDmgType(static_cast<DamageType>(sqlite3_column_int(pstmt, 2)));
			ret.setImgPath((const char*)sqlite3_column_text(pstmt, 3));
			isOk = true;
		}

		sqlite3_reset(pstmt);
		sqlite3_finalize(pstmt);
	}

	sqlite3_close(db);
	return ret;
}

void DBHelper::updateCharacterBrief(const CharacterBrief& brief)
{
	CharacterBrief ret;
	sqlite3* db = nullptr;
	sqlite3_stmt* pstmt = nullptr;
	const char* zErrMsg = nullptr;
	const char* pTail = nullptr;
	int rc = 0;
	std::string sql = "update tb_char_brief set name=?,img_path=?,dmg_type=? where id = ?;";
	
	rc = sqlite3_open(DB_FILE_PATH, &db);
	if (rc != SQLITE_OK) {
		zErrMsg = sqlite3_errmsg(db);
		std::string errLog = std::string("open db error: ") + sqlite3_errmsg(db);
		LOG_ERROR("DBHelper", errLog.c_str());
		sqlite3_close(db);
		return;
	}

	rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length() + 1, &pstmt, nullptr);
	if (rc != SQLITE_OK) {
		zErrMsg = sqlite3_errmsg(db);
		std::string errLog = std::string("prepare updateCharacterBrief error: ") + sqlite3_errmsg(db);
		LOG_ERROR("DBHelper", errLog.c_str());
		sqlite3_close(db);
		return;
	}
	std::string name = brief.getName();
	std::string imgPath = brief.getImgPath();
	int dmgType = static_cast<int>(brief.getDmgType());
	int charId = brief.getId();
	sqlite3_bind_string(pstmt, 1, name);
	sqlite3_bind_string(pstmt, 2, imgPath);
	sqlite3_bind_int(pstmt, 3, dmgType);
	sqlite3_bind_int(pstmt, 4, charId);
	rc = sqlite3_step(pstmt);
	if (SQLITE_DONE != rc)
	{
		zErrMsg = sqlite3_errmsg(db);
		std::string errLog = std::string("update tb_char_brief error: ") + sqlite3_errmsg(db);
		LOG_ERROR("DBHelper", errLog.c_str());
	}
	sqlite3_reset(pstmt);
	sqlite3_finalize(pstmt);
	sqlite3_close(db);
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
		std::string errLog = std::string("prepare sqlLv error: ") + sqlite3_errmsg(db);
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

void DBHelper::insertCharacterGrowRate(CharacterGrowRate& rate)
{
	sqlite3* db = nullptr;
	bool ret = false;
	ret = openDB(&db);
	std::string sql = "insert into tb_char_grow_rate(name";
	for (int i = 1; i <= DBHelper::SkillLvCnt; i++)
	{
		sql += ",lv_" + std::to_string(i);
	}
	sql += ")values(?";
	for (int i = 1; i <= DBHelper::SkillLvCnt; i++)
	{
		sql += ",?";
	}
	sql += ");";

	SqlPrepareCallback prepareCb = [&](sqlite3_stmt* pstmt) {
		sqlite3_bind_string(pstmt, 1, rate.getName());
		for (int i = 1; i <= DBHelper::SkillLvCnt; i++)
		{
			sqlite3_bind_double(pstmt, i + 1, rate.getLvRate(i));
		}
	};

	if (ret)
	{
		execSql(db, sql, prepareCb);
	}

	int id = static_cast<int>(sqlite3_last_insert_rowid(db));
	rate.setId(id);

	closeDB(db);
}

CharacterGrowRate DBHelper::selectCharacterGrowRate(int id)
{
	CharacterGrowRate ret;
	return ret;
}

void DBHelper::updateCharacterGrowRate(CharacterGrowRate& rate)
{
	sqlite3* db = nullptr;
	bool ret = false;
	ret = openDB(&db);
	std::string sql = "update tb_char_grow_rate set name=?";
	for (int i = 1; i <= DBHelper::SkillLvCnt; i++)
	{
		sql += ",lv_" + std::to_string(i) +"=?";
	}
	sql += " where id=?;";

	SqlPrepareCallback prepareCb = [&](sqlite3_stmt* pstmt) {
		sqlite3_bind_string(pstmt, 1, rate.getName());
		for (int i = 1; i <= DBHelper::SkillLvCnt; i++)
		{
			sqlite3_bind_double(pstmt, i + 1, rate.getLvRate(i));
		}
		sqlite3_bind_int(pstmt, DBHelper::SkillLvCnt + 2, rate.getId());
	};

	if (ret)
	{
		ret = execSql(db, sql, prepareCb);
	}

	closeDB(db);
}

std::set<CharacterGrowRate> DBHelper::selectAllCharacterGrowRate()
{
	sqlite3* db = nullptr;
	bool ret = false;
	ret = openDB(&db);
	std::set<CharacterGrowRate> growRateSet;
	std::string sql = "select id,name";
	for (int i = 1; i <= DBHelper::SkillLvCnt; i++)
	{
		sql += ",lv_" + std::to_string(i);
	}
	sql += " from tb_char_grow_rate";
	SqlStepCallback stepCb = [&](int rc, sqlite3_stmt* pstmt) {
		if (rc == SQLITE_ROW)
		{
			CharacterGrowRate rate;
			const char* str = (const char*)sqlite3_column_text(pstmt, 1);
			rate.setId(sqlite3_column_int(pstmt, 0));
			rate.setName(str);
			for (int i = 1; i <= DBHelper::SkillLvCnt; i++)
			{
				int colIndx = i + 1;
				rate.setLvRate(i, sqlite3_column_double(pstmt, colIndx));
			}
			growRateSet.insert(rate);
		}
	};

	execSql(db, sql,nullptr, stepCb);

	return growRateSet;
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

	std::string sql_char_grow_rate = "create table IF NOT EXISTS "
		"tb_char_grow_rate("
		"id integer primary key autoincrement,"
		"name text not null,"
		"lv_1 real not null,"
		"lv_2 real not null,"
		"lv_3 real not null,"
		"lv_4 real not null,"
		"lv_5 real not null,"
		"lv_6 real not null,"
		"lv_7 real not null,"
		"lv_8 real not null,"
		"lv_9 real not null,"
		"lv_10 real not null,"
		"lv_11 real not null,"
		"lv_12 real not null,"
		"lv_13 real not null"
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

	rc = sqlite3_exec(db, sql_char_grow_rate.c_str(), 0, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		std::string errLog = std::string("create tb_char_grow_rate failed: ") + zErrMsg;
		LOG_ERROR("DBHelper", errLog.c_str());
	}

	sqlite3_close(db);
}

bool DBHelper::openDB(sqlite3** dbPtr)
{
	char* zErrMsg = nullptr;
	int rc = 0;
	bool ret = false;
	rc = sqlite3_open(DB_FILE_PATH, dbPtr);
	if (rc) {
		std::string errLog = std::string("open error: ") + sqlite3_errmsg(*dbPtr);
		LOG_ERROR("DBHelper", errLog.c_str());
		ret= false;
	}
	else {
		ret= true;
	}
	return ret;
}

bool DBHelper::closeDB(sqlite3* db)
{
	sqlite3_close(db);
	return true;
}

bool DBHelper::execSql(sqlite3* db, const std::string& sql, SqlPrepareCallback prepCb /*=nullptr*/, SqlStepCallback stepCb/*=nullptr*/)
{
	bool ret = false;
	sqlite3_stmt* pstmt = nullptr;
	const char* zErrMsg = nullptr;
	const char* pTail = nullptr;
	int rc = 0;

	rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &pstmt, NULL);
	if (rc != SQLITE_OK)
	{
		std::string errLog = sql+" error: " + sqlite3_errmsg(db);
		LOG_ERROR("DBHelper", errLog.c_str());
	}
	else 
	{
		if (prepCb)
		{
			prepCb(pstmt);
		}
		rc = sqlite3_step(pstmt);
		while (rc == SQLITE_DONE || rc == SQLITE_ROW)
		{
			if (stepCb)
			{
				stepCb(rc,pstmt);
			}
			if (rc == SQLITE_DONE)
			{
				ret = true;
				break;
			}
			else {
				rc = sqlite3_step(pstmt);
			}
		}
		sqlite3_reset(pstmt);
		sqlite3_finalize(pstmt);
		pstmt = nullptr;
	}


	return ret;
}

void DBHelper::sqlite3_bind_string(sqlite3_stmt* pstmt, int indx, const std::string& text)
{
	size_t buffSize = text.length() + 1;
	char* buff = (char*)calloc(1, buffSize);
	strncpy_s(buff, buffSize, text.c_str(), text.length());
	sqlite3_bind_text(pstmt, indx, buff, -1,[](void* ptr) {
		free(ptr);
	});
}

DBHelper* DBHelper::instance;
