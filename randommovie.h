#ifndef RANDOMMOVIE_H
#define RANDOMMOVIE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "movie.h"

class RandomMovie : public QObject
{
    Q_OBJECT
public:
    explicit RandomMovie(QObject *parent = 0);
    void fetchARandomMovie();

private:
    QNetworkAccessManager *networkAccessManager;
    QNetworkReply *requestReply;
    
signals:
    void movieInfoAvailable(Movie *movie);

private slots:
    void readReplyForLastRegisteredMovie();
    
};

#endif // RANDOMMOVIE_H
