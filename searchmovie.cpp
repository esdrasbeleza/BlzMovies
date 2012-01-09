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

    QDomDocument xmlDom;
    xmlDom.setContent(replyString);
    resultNumber = xmlDom.elementsByTagName("movies").at(0).toElement().elementsByTagName("movie").size();

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

    QList<Movie> movieList;

    for (int i = 1; i <= resultNumber; i++) {
        QString elementQuery = "/OpenSearchDescription/movies/movie[" + QString::number(i) + "]";

        QString name;
        QString theMdbId;
        QString imdbId;
        QString overview;
        QString posterUrlXml;
        QString released;
        QUrl posterUrl;

        query.setQuery(elementQuery + "/name/text()");
        query.evaluateTo(&name);

        query.setQuery(elementQuery + "/id/text()");
        query.evaluateTo(&theMdbId);

        query.setQuery(elementQuery + "/imdb_id/text()");
        query.evaluateTo(&imdbId);

        query.setQuery(elementQuery + "/overview/text()");
        query.evaluateTo(&overview);
        qDebug("overview: " + overview.trimmed().toUtf8());

        query.setQuery(elementQuery + "/released/text()");
        query.evaluateTo(&released);

        query.setQuery(elementQuery + "/images/image[@type=\"poster\" and @size=\"thumb\" and position() = 1]");
        query.evaluateTo(&posterUrlXml);

        QDomDocument doc;
        doc.setContent(posterUrlXml);
        QDomNode node = doc.elementsByTagName("image").at(0);
        posterUrl = QUrl(node.toElement().attribute("url").trimmed());

        Movie newMovie(theMdbId.toInt(), name.trimmed());
        newMovie.setImdbId(imdbId.trimmed());
        newMovie.setOverview(overview.trimmed());

        qDebug("overview 2: " + newMovie.getOverview().toUtf8());

        newMovie.setYear(released.split("-").at(0).toInt());
        if (posterUrl.isValid()) {
            newMovie.setPosterUrl(posterUrl);
        }

        movieList.append(newMovie);
    }
    qDebug("Finished parsing movie list");

    emit hasResults(movieList);
}
