#ifndef _CHARACTER_LV_PROP_DELEGATE_H
#define _CHARACTER_LV_PROP_DELEGATE_H

#include <QStyledItemDelegate>

class CharacterLvPropDelegate:public QStyledItemDelegate {
	Q_OBJECT
public:
	CharacterLvPropDelegate(QObject* parent);
	virtual QWidget* createEditor(QWidget* parent,
		const QStyleOptionViewItem& option, 
		const QModelIndex& index)const override;
	virtual void setModelData(QWidget* editor, 
		QAbstractItemModel* model, 
		const QModelIndex& index)const override;
private:
	QWidget* createLvPropComboBox(QWidget* parent)const;
	QWidget* createIntLineEdit(QWidget* parent) const;
	QWidget* createDoubleLineEdit(QWidget* parent) const;
};


#endif