#include <QApplication>
#include "MainFrame.h"
#include "GenDmgCore.h"
#include "ViewLogger.h"
#include "GenDmgApp.h"

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
	// 81 vs 92		48.525
	
	//fir 1715 fir_o 6883 sec 2292  sec_v 5398 sec_o 7842?
	//			sec 4401, 
	//			weapon 28%
	//atk 1285, jt 361, enh 61.6% 
	//189%
	// 
	//3924.6984 -> 1715  43.6976%(10%) uk = 34.299%

	//89 vs 92		49.606%
	//fir 2350
	//	5150
	//atk 1613    enh 63.8%
	//199.2%
	//5263.051248 -> 2350 44.65%
}