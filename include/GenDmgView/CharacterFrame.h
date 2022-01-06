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
#include <QPushButton>

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
	QFrame* createLvPropTable();
	QFrame* createBriefTable();
	void onCharacterSearcherIndexChaged(int indx);
	void refreshCharacterImage();

	void addEmptyCharacter();
private:
	QVBoxLayout* mainLayout_ =nullptr;


	QWidget* configView_ = nullptr;
	QLabel* lbCharacterImg_ = nullptr;

	QComboBox* cbCharacterSeacher_ = nullptr;
	CharacterListModel* cbCharacterListModel_ = nullptr;

	QTableView* tvBrief_ = nullptr;
	CharacterBriefModel* tvBriefModel_ = nullptr;

	QTableView* tvLvProps_ = nullptr;
	CharacterLvPropModel* tvLvPropsModel_ = nullptr;

	std::vector<CharacterBrief> allCharacterBrief_;
	
};



#endif