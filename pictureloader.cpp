#include "pictureloader.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>

PictureLoader::PictureLoader(QUrl url, QObject *parent) :
    QObject(parent)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(loadPictureData(QNetworkReply*)));

    QNetworkRequest request(url);
    qDebug("Download " + url.toString().toUtf8());
    manager->get(request);
}

void PictureLoader::loadPictureData(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug("Erro!!");
    }

    const QByteArray data(reply->readAll());

    if (data.isEmpty()) {
        qDebug("Sem dados!");
    }

    QPixmap pixmap;
    pixmap.loadFromData(data);
    emit pictureReady(pixmap);
}
