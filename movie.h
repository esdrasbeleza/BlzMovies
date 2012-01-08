#ifndef MOVIE_H
#define MOVIE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>

class Movie : public QObject
{
    Q_OBJECT
public:
    explicit Movie(int id, QString name, QObject *parent = 0);
    void fetchInformation();

    int getId();
    QString getImdbId();
    int getYear();
    QString getName();
    QString getOverview();
    QUrl getPosterUrl();
    QPixmap getPoster();

    void setId(int id);
    void setImdbId(QString imdbId);
    void setYear(int year);
    void setName(QString name);
    void setOverview(QString overview);
    void setPosterUrl(QUrl url);
    void setPoster(QPixmap poster);

private:
    int id;
    int year;
    QString imdbId;
    QString name;
    QString overview;
    QUrl posterUrl;
    QPixmap poster;


    
};

#endif // MOVIE_H
