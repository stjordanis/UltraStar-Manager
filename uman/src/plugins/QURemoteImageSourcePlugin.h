#ifndef QUREMOTEIMAGESOURCEPLUGIN_H
#define QUREMOTEIMAGESOURCEPLUGIN_H

#define REMOTE_IMAGE_SOURCE_PLUGIN_API_VERSION 1

#include <QtPlugin>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QFileInfoList>
#include <QDir>

class QWidget;
class QTranslator;
class QURemoteImageCollector;
class QUSongInterface;
class QUCommunicatorInterface;

/*!
 * Defines an interface for an arbitrary remote image source that
 * uses the HTTP protocol. Only the host is needed - no port.
 */
class QURemoteImageSource {
public:
	virtual ~QURemoteImageSource() {}

	// for compatibility reasons
	virtual int pluginApiVersion() const = 0;

	// multi-language support
	virtual QMap<QString, QTranslator*> translations() const = 0;

	// A list of named data where a corresponding song tag must be set.
	// E.g, 'Artist' -> #ARTIST, 'Title' -> #TITLE
	virtual QStringList songDataFields() const = 0;
	virtual void setSongDataField(const QString &field, const QString &songProperty) = 0; // field -> tag/property

	// A list of custom data fields needed to download the files
	// E.g., secret key or access key id from Amazon Product Advertising API
	virtual QStringList customDataFields() const = 0;
	virtual void setCustomDataField(const QString &field, const QString &value) = 0;
	virtual void showHelpDialog(const QString &field, QWidget *parent) const = 0;

	// a name for this image source, e.g., "Amazon Product Advertising API"
	virtual QString name() const = 0;

	// A host is needed to request the image from the internet.
	virtual QStringList hosts() const = 0;
	virtual void setHost(const QString &) = 0;

	// limit the number of downloads
	virtual int limit() const = 0;
	virtual void setLimit(int) = 0;

	// allow the user to keep previous downloads
	virtual bool keepDownloads() const = 0;
	virtual void setKeepDownloads(bool) = 0;

	// collecting images
	virtual QList<QURemoteImageCollector*> imageCollectors(QList<QUSongInterface*>) = 0;
	virtual QDir imageFolder(QUSongInterface*) const = 0;
};

/*!
 * Download images for one song.
 */
class QURemoteImageCollector {
public:
	virtual ~QURemoteImageCollector() {}

	// feedback, logging, error handling -> communicator due to lack of signals here
	virtual void setCommunicator(QUCommunicatorInterface*) = 0;

	// start collecting/downloading remote images
	// !! You need to set a communicator before calling this function !!
	virtual void collect() = 0;

	// results -> a list of local files -> ready to load/view
	virtual QFileInfoList results() const = 0;
};

Q_DECLARE_INTERFACE(QURemoteImageSource, "net.sf.uman.QURemoteImageSource/1.0");
Q_DECLARE_INTERFACE(QURemoteImageCollector, "net.sf.uman.QURemoteImageCollector/1.0");

#endif // QUREMOTEIMAGESOURCEPLUGIN_H
