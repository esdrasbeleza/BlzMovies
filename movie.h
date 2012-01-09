#ifndef MOVIE_H
#define MOVIE_H

#include <QString>
#include <QUrl>
#include <QPixmap>

class Movie
{

public:
    explicit Movie(int id, QString name);
    void fetchInformation();

    int getId();
    QString getImdbId();
    int getYear();
    QString getName();
    QString getOverview();
    QUrl getThumbnailUrl();
    QPixmap getThumbnail();
    QUrl getPosterUrl();
    QPixmap getPoster();

    void setId(int id);
    void setImdbId(QString imdbId);
    void setYear(int year);
    void setName(QString name);
    void setOverview(QString overview);
    void setThumbnailUrl(QUrl thumbnailUrl);
    void setThumbnail(QPixmap thumbnail);
    void setPosterUrl(QUrl posterUrl);
    void setPoster(QPixmap poster);

private:
    int id;
    int year;
    QString imdbId;
    QString name;
    QString overview;
    QUrl thumbnailUrl;
    QPixmap thumbnail;
    QUrl posterUrl;
    QPixmap poster;
    
};

#endif // MOVIE_H
