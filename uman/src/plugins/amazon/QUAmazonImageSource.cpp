#include "QUAmazonImageSource.h"
#include "QUAmazonImageCollector.h"
#include "QUStringSupport.h"

#include <QCoreApplication>

QUAmazonImageSource::QUAmazonImageSource(QObject *parent): QObject(parent) {}

QString QUAmazonImageSource::songDataField(const QString &field) const {
	return "foobar";
}

void QUAmazonImageSource::setSongDataField(const QString &field, const QString &songProperty) {
}

QString QUAmazonImageSource::customDataField(const QString &field) const {
	return "foobar";
}

void QUAmazonImageSource::setCustomDataField(const QString &field, const QString &value) {
}

void QUAmazonImageSource::showHelpDialog(const QString &field, QWidget *parent) const {
}

QStringList QUAmazonImageSource::hosts() const {
	return QStringList()
			<< "amazon.de"
			<< "amazon.co.uk"
			<< "amazon.com"
			<< "amazon.jp"
			<< "amazon.fr"
			<< "amazon.ca";
}

QString QUAmazonImageSource::host() const {
	return "foobar";
}

void QUAmazonImageSource::setHost(const QString &) {
}

int QUAmazonImageSource::limit() const {
	return 10;
}

void QUAmazonImageSource::setLimit(int) {
}

bool QUAmazonImageSource::keepDownloads() const {
	return false;
}

void QUAmazonImageSource::setKeepDownloads(bool) {
}

QList<QURemoteImageCollector*> QUAmazonImageSource::imageCollectors(QList<QUSongInterface*>) {
	return QList<QURemoteImageCollector*>();
}

QDir QUAmazonImageSource::imageFolder(QUSongInterface *song) const {
	QString folderName = QUStringSupport::withoutUnsupportedCharacters(
			QString("%1 - %2").arg(song->artist()).arg(song->title())).trimmed();

	if(folderName.isEmpty())
		folderName = "_unknown";

	QDir result(QCoreApplication::applicationDirPath());
	result.mkdir("covers");
	if(result.cd("covers")) {
		result.mkdir(folderName);
		result.cd(folderName);
	}

	return result;
}

Q_EXPORT_PLUGIN2(quamazonimagesource, QUAmazonImageSource);
