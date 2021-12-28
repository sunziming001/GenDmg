#include "CharacterBriefDelegate.h"
#include "CharacterBriefModel.h"
#include <QComboBox>
#include <QLineEdit>
#include <QAbstractItemView>

CharacterBriefDelegate::CharacterBriefDelegate(QObject* parent)
	:QStyledItemDelegate(parent)
{

}

CharacterBriefDelegate::~CharacterBriefDelegate()
{

}


QSize CharacterBriefDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QSize ret = QStyledItemDelegate::sizeHint(option, index);

	return ret;
}

QWidget* CharacterBriefDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QWidget* ret = nullptr;
	if (CharacterBriefModel::isDamageTypeIndex(index))
	{
		ret = createDmgTypeCombo(parent, index);
	}
	else if(CharacterBriefModel::isImgPathIndex(index)
		|| CharacterBriefModel::isNameIndex(index))
	{
		ret = createPlainLineEdit(parent, index);
	}
	else {
		ret = QStyledItemDelegate::createEditor(parent, option, index);
	}
	return ret;
}

void CharacterBriefDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	if (CharacterBriefModel::isDamageTypeIndex(index))
	{
		QComboBox* cb = dynamic_cast<QComboBox*>(editor);
		if (cb)
		{
			model->setData(index, cb->currentIndex(), Qt::EditRole);
		}
		
	}
	else if (CharacterBriefModel::isImgPathIndex(index)
		|| CharacterBriefModel::isNameIndex(index))
	{
		QLineEdit *le = dynamic_cast<QLineEdit*>(editor);
		if (le && !le->text().isEmpty())
		{
			model->setData(index, le->text(), Qt::EditRole);
		}
	}
}

void CharacterBriefDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	if (CharacterBriefModel::isImgPathIndex(index)
		|| CharacterBriefModel::isNameIndex(index)
		|| CharacterBriefModel::isDamageTypeIndex(index))
	{

	}
	else {
		QStyledItemDelegate::setEditorData(editor, index);
	}
}

QWidget* CharacterBriefDelegate::createDmgTypeCombo(QWidget* parent, const QModelIndex& index)const
{
	QComboBox* w = new QComboBox(parent);
	int cnt =static_cast<int>(DamageType::Count);
	for (int i = 0; i < cnt; i++)
	{
		QString txt = CharacterBriefModel::damageTypeToString(static_cast<DamageType>(i));
		w->addItem(txt, i);
	}
	w->setCurrentIndex(getEditData(index).toInt());
	return w;
}

QWidget* CharacterBriefDelegate::createPlainLineEdit(QWidget* parent, const QModelIndex& index)const
{
	QLineEdit* le = new QLineEdit(parent);
	le->setText(getEditData(index).toString());
	return le;
}

QVariant CharacterBriefDelegate::getEditData(const QModelIndex& index) const
{
	QVariant ret;
	QAbstractItemView* v = dynamic_cast<QAbstractItemView*>(parent());

	if (v && v->model())
	{
		ret = v->model()->data(index, Qt::EditRole);
	}


	return ret;
}

