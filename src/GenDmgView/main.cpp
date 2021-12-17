#include <QApplication>
#include "MainFrame.h"
#include "GenDmgCore.h"
#include "ViewLogger.h"

float dmg(float atk, float rate, float enhance, int lvSource, int lvTarget, float reDef=0.0f,float gRate=0.0f)
{
	float defRate = 0.1f;
	float reDefRate = (1.0f - (defRate - reDef));
	float ret = atk * rate * enhance * (100 + lvSource) / (200 + lvSource + lvTarget) * reDefRate*(1+gRate);
	return ret;
}

int main(int argc, char** argv)
{
	LOG_INIT(0);
	LOG_INFO("Main", "start...");

	float vxl1 = dmg(1285.0f, 1.89f, 1.616f, 81, 92);				//1715
	float vxl2 = dmg(1285.0f, 1.89f+ 0.28f, 1.616f, 81, 92, 0.15); //2292
	float vls1 = dmg(1613.0f, 1.992f, 1.638f, 89, 92);				//2350
	Q_UNUSED(vxl1);
	Q_UNUSED(vxl2);
	GenDmgCore* core = GenDmgCore::getInstance();
	core->init();

	QApplication a(argc, argv);
	MainFrame mainFrame;
	mainFrame.show();
	a.exec();

	core->uninit();

	LOG_INFO("Main", "end");
	return 0;
	// 81 vs 92		48.525
	
	//fir 1715 sec 2292
	//			sec 4401
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