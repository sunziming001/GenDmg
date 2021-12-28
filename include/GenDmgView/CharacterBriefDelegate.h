#ifndef _CHARACTER_BRIEF_DELEGATE_H
#define _CHARACTER_BRIEF_DELEGATE_H

#include <QStyledItemDelegate>

class CharacterBriefDelegate :public QStyledItemDelegate
{
	Q_OBJECT
public:
	CharacterBriefDelegate(QObject* parent);
	~CharacterBriefDelegate();

	virtual QSize sizeHint(const QStyleOptionViewItem& option, 
		const QModelIndex& index) const override;

	virtual QWidget* createEditor(QWidget* parent,
		const QStyleOptionViewItem& option,
		const QModelIndex& index)const override;

	virtual void setModelData(QWidget* editor,
		QAbstractItemModel* model,
		const QModelIndex& index)const override;

	virtual void setEditorData(QWidget* editor, const QModelIndex& index)const override;
private:
	QWidget* createDmgTypeCombo(QWidget* parent, const QModelIndex& index)const;
	QWidget* createPlainLineEdit(QWidget* parent, const QModelIndex& index)const;
	QVariant getEditData(const QModelIndex& index)const;
};


#endif