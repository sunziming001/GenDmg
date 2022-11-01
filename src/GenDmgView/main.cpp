#include <QApplication>
#include "MainFrame.h"
#include "GenDmgCore.h"
#include "ViewLogger.h"
#include "GenDmgApp.h"
#include <QTimer>
#include "CharacterConfig.h"

float dmg(float atk, float rate, float enhance, int lvSource, int lvTarget, float reDef=0.0f)
{
	float defRate = 0.1f;
	float reDefRate = 1.0f;
	if (defRate - reDef > 0.0f)
	{
		reDefRate -= defRate - reDef;
	}
	else {

	}
	float ret = atk * rate * enhance * (100 + lvSource) / (200 + lvSource + lvTarget) * 1.025;
	return ret;
}

int main(int argc, char** argv)
{

	GenDmgApp a(argc, argv);
	MainFrame mainFrame;
	mainFrame.show();



	a.exec();

	return 0;
}