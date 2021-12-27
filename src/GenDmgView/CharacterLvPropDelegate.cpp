#include "CharacterLvPropDelegate.h"
#include <QComboBox>
#include "GenDmgCore.h"
#include "CharacterLvPropModel.h"
#include <QMetaProperty>
#include <QLineEdit>
#include <QAbstractItemView>

CharacterLvPropDelegate::CharacterLvPropDelegate(QObject* parent)
	:QStyledItemDelegate(parent)
{

}

QWidget* CharacterLvPropDelegate::createEditor(
	QWidget* parent,
	const QStyleOptionViewItem& option,
	const QModelIndex& index)const
{
	if (CharacterLvPropModel::isSpecialPropIndex(index))
	{
		return createLvPropComboBox(parent, index);
	}
	else if (CharacterLvPropModel::isIntIndex(index))
	{
		return createIntLineEdit(parent, index);
	}
	else if (CharacterLvPropModel::isDoubleIndex(index))
	{
		return createDoubleLineEdit(parent, index);
	}
	else {
		return QStyledItemDelegate::createEditor(parent, option, index);
	}
}

void CharacterLvPropDelegate::setModelData(
	QWidget* editor, 
	QAbstractItemModel* model, 
	const QModelIndex& index) const
{
	if (CharacterLvPropModel::isSpecialPropIndex(index))
	{
		QComboBox* cb = dynamic_cast<QComboBox*>(editor);
		if(cb){
			int idx = cb->currentIndex();
			int v = cb->itemData(idx, Qt::UserRole).toInt();
			model->setData(index, v, Qt::EditRole);
		}
	}
	else if (CharacterLvPropModel::isIntIndex(index))
	{
		QLineEdit *le = dynamic_cast<QLineEdit*>(editor);
		if (le)
		{
			int v = le->text().toInt();
			model->setData(index, v, Qt::EditRole);
		}
	}
	else if (CharacterLvPropModel::isDoubleIndex(index))
	{
		QLineEdit* le = dynamic_cast<QLineEdit*>(editor);
		if (le)
		{
			double v = le->text().toDouble();
			model->setData(index, v, Qt::EditRole);
		}
	}
	else {
		QStyledItemDelegate::setModelData(editor, model, index);
	}
}

void CharacterLvPropDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	if (CharacterLvPropModel::isSpecialPropIndex(index))
	{
		
	}
	else if (CharacterLvPropModel::isIntIndex(index))
	{

	}
	else if (CharacterLvPropModel::isDoubleIndex(index))
	{

	}
	else {
		QStyledItemDelegate::setEditorData(editor, index);
	}
}

QWidget* CharacterLvPropDelegate::createLvPropComboBox(QWidget* parent, const QModelIndex& index)const
{
	QComboBox* ret = new QComboBox(parent);
	
	int cnt =static_cast<int>(SpecialPropType::Count);
	for (int i = 1; i < cnt; i++)
	{
		SpecialPropType type = static_cast<SpecialPropType>(i);
		QString text = CharacterLvPropModel::specialPropTypeToString(type);
		ret->insertItem(i, text,i);
	}
	ret->setCurrentIndex(getVarient(index,Qt::EditRole).toInt());
	return ret;
}

QWidget* CharacterLvPropDelegate::createIntLineEdit(QWidget* parent, const QModelIndex& index) const
{
	QLineEdit* le = new QLineEdit(parent);
	le->setValidator(new QIntValidator(0,INT_MAX,le));
	QString txt =QString::number(getVarient(index, Qt::EditRole).toInt());
	le->setText(txt);
	return le;
}

QWidget* CharacterLvPropDelegate::createDoubleLineEdit(QWidget* parent, const QModelIndex& index) const
{
	QLineEdit* le = new QLineEdit(parent);
	le->setValidator(new QDoubleValidator(le));
	le->setText(QString::number(getVarient(index, Qt::EditRole).toDouble()));
	return le;
}

QVariant CharacterLvPropDelegate::getVarient(const QModelIndex& index, int role) const
{
	QVariant ret;
	QAbstractItemView* v = dynamic_cast<QAbstractItemView*>(parent());
	if(v){
		auto m = v->model();
		if (m)
		{
			ret = m->data(index, role);
		}
	}
	return ret;
}
