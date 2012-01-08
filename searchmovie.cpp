#include "searchmovie.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QXmlQuery>
#include <QDomDocument>

SearchMovie::SearchMovie(QString movieToSearch, QObject *parent) :
    QObject(parent)
{
    url = QUrl("http://api.themoviedb.org/2.1/Movie.search/en/xml/" + QString(THEMOVIEDB_KEY) + "/" + QUrl::toPercentEncoding(movieToSearch.trimmed()));
}

void SearchMovie::search() {
    qDebug("Looking for " + url.toString().toUtf8());

    QNetworkAccessManager *networkAccessManager = new QNetworkAccessManager(this);
    QNetworkRequest netRequest;
    netRequest.setUrl(url);
    networkAccessManager->get(netRequest);

    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), SLOT(readReply(QNetworkReply*)));
}

void SearchMovie::readReply(QNetworkReply *reply) {
    replyString = reply->readAll();

    QString resultNumberFormattedAsString;

    QXmlQuery query;
    query.setFocus(replyString);
    query.setQuery("/OpenSearchDescription/opensearch:totalResults/text()");
    query.evaluateTo(&resultNumberFormattedAsString);

    resultNumber = resultNumberFormattedAsString.toInt();

    if (resultNumber == 0) {
        emit noResults();
    }
    else {
        parseReply();
    }
}

void SearchMovie::parseReply() {
    QXmlQuery query;
    query.setFocus(replyString);

    QList<Movie*> movieList;

    for (int i = 1; i <= resultNumber; i++) {
        QString elementQuery = "/OpenSearchDescription/movies/movie[" + QString::number(i) + "]";

        QString name;
        QString theMdbId;
        QString imdbId;
        QString overview;
        QString posterUrlXml;
        QString year;
        QUrl posterUrl;

        query.setQuery(elementQuery + "/name/text()");
        query.evaluateTo(&name);

        query.setQuery(elementQuery + "/id/text()");
        query.evaluateTo(&theMdbId);

        query.setQuery(elementQuery + "/imdb_id/text()");
        query.evaluateTo(&imdbId);

        query.setQuery(elementQuery + "/overview/text()");
        query.evaluateTo(&overview);

        query.setQuery(elementQuery + "/year/text()");
        query.evaluateTo(&year);

        query.setQuery(elementQuery + "/images/image[@type=\"poster\" and @size=\"thumb\" and position() = 1]");
        query.evaluateTo(&posterUrlXml);
        QDomDocument xmlDom;
        xmlDom.setContent(posterUrlXml);
        posterUrl = QUrl(xmlDom.toElement().attribute("url"));

        Movie *newMovie = new Movie(theMdbId.toInt(), name);
        newMovie->setImdbId(imdbId);
        newMovie->setOverview(overview);
        newMovie->setYear(year.toInt());
        newMovie->setPosterUrl(posterUrl);

        movieList.append(newMovie);
    }

    emit hasResults(movieList);
}
