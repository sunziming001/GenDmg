#ifndef _CHARACTER_FRAME_H
#define _CHARACTER_FRAME_H

#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <vector>
#include "CharacterBrief.h"
#include <QComboBox>
#include <QAbstractListModel>
#include <QTableView>

class CharacterLvPropModel;
class CharacterBriefModel;
class CharacterListModel;

class CharacterFrame:public QFrame
{
	Q_OBJECT
public:
	CharacterFrame(QWidget* parent);
	~CharacterFrame();
private:
	QFrame* createConfigView();
	QComboBox* createCharacterSearcher();
	QTableView* createLvPropTable();
	QTableView* createBriefTable();
	void onCharacterSearcherIndexChaged(int indx);
	void refreshCharacterImage();
private:
	QVBoxLayout* mainLayout_ =nullptr;


	QWidget* configView_ = nullptr;
	QHBoxLayout *configLayout_ = nullptr;
	QLabel* lbCharacterImg_ = nullptr;

	QComboBox* cbCharacterSeacher_ = nullptr;
	CharacterListModel* cbCharacterListModel_ = nullptr;

	QVBoxLayout* configSearchLayout_ = nullptr;

	QTableView* tvBrief_ = nullptr;
	CharacterBriefModel* tvBriefModel_ = nullptr;

	QTableView* tvLvProps_ = nullptr;
	CharacterLvPropModel* tvLvPropsModel_ = nullptr;

	std::vector<CharacterBrief> allCharacterBrief_;
	
};



#endif