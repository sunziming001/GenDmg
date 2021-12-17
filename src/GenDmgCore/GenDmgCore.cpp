#include "GenDmgCore.h"
#include "CoreLogger.h"

GenDmgCore* GenDmgCore::getInstance()
{
	if (instance == nullptr)
		instance = new GenDmgCore;

	return instance;
}

void GenDmgCore::init()
{
	LOG_INIT(0);
	LOG_INFO("GenDmgCore", "init.");
}

void GenDmgCore::uninit()
{
	LOG_INFO("GenDmgCore", "uninit.");
}

GenDmgCore::~GenDmgCore()
{

}

GenDmgCore::GenDmgCore()
{

}

GenDmgCore* GenDmgCore::instance=nullptr;

