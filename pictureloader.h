#ifndef PICTURELOADER_H
#define PICTURELOADER_H

#include <QObject>
#include <QUrl>
#include <QNetworkReply>
#include <QPixmap>

class PictureLoader : public QObject
{
    Q_OBJECT
public:
    explicit PictureLoader(QUrl url, QObject *parent = 0);
    
signals:
    void pictureReady(QPixmap pixmap);
    
private slots:
    void loadPictureData(QNetworkReply *reply);
    
};

#endif // PICTURELOADER_H
