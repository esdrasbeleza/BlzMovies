#include "pictureloader.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>

PictureLoader::PictureLoader(QUrl url, QObject *parent) :
    QObject(parent)
{
    qDebug("Downloading " + url.toString().toUtf8());
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(loadPictureData(QNetworkReply*)));

    QNetworkRequest request(url);
    manager->get(request);
}

void PictureLoader::loadPictureData(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug("Network error; show some feedback");
        // TODO
        return;
    }

    const QByteArray data(reply->readAll());

    if (data.isEmpty()) {
        qDebug("No data!");
        return;
    }

    QPixmap pixmap;
    pixmap.loadFromData(data);
    emit pictureReady(pixmap);
}
