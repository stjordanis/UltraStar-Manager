#ifndef QUDETAILITEM_H_
#define QUDETAILITEM_H_

#include <QString>
#include <QTableWidgetItem>
#include <QList>
#include "QUSongItem.h"

/*!
 * This class encapsulates a pointer to a QUSongFile object for a QTableWidget
 * instance which is used to present details of a song file to the user.
 */
class QUDetailItem: public QTableWidgetItem {
public:
	QUDetailItem(const QString &tag);
	QUDetailItem(const QString &tag, const QList<QUSongItem*> &songItems);

	QString tag() const {return _tag;}

	void setSongItems(const QList<QUSongItem*> &songItems);

private:
	QString            _tag;
	QList<QUSongItem*> _songItems;
	Qt::ItemFlags      _flagsForSingleSong;
	Qt::ItemFlags      _flagsForMultipleSongs;
	QString            _textMask;
	bool               _hasDynamicDefaultData;

	void reset();

	void updateDefaultData();
	void updateText(const QString &tag, QUSongFile *song);

	void updateItemForMultipleSongs();
	void updateDefaultDataForMultipleSongs();

	const QList<QUSongItem*>& songItems() const {return _songItems;}
	QStringList defaultData(QUSongFile *song);
};

#endif /*QUDETAILITEM_H_*/
