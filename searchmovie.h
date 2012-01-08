#ifndef SEARCHMOVIE_H
#define SEARCHMOVIE_H

#include <QObject>
#include <QList>

#include "movie.h"

class SearchMovie : public QObject
{
    Q_OBJECT
public:
    explicit SearchMovie(QString movieToSearch, QObject *parent = 0);
    void search();
    
signals:
    void noResults();
    void hasResults(QList<Movie>);

private:
    QUrl url;
    QString replyString;
    int resultNumber;
    QList<Movie> movieList;

    void parseReply();

private slots:
    void readReply(QNetworkReply* reply);
    
};

#endif // SEARCHMOVIE_H
