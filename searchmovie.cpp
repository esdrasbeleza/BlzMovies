#include "searchmovie.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
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
        QString thumbnailUrlXml;
        QString released;
        QUrl thumbnailUrl;
        QUrl posterUrl;

        query.setQuery(elementQuery + "/name/text()");
        query.evaluateTo(&name);

        query.setQuery(elementQuery + "/id/text()");
        query.evaluateTo(&theMdbId);

        query.setQuery(elementQuery + "/imdb_id/text()");
        query.evaluateTo(&imdbId);

        query.setQuery(elementQuery + "/overview/text()");
        query.evaluateTo(&overview);

        query.setQuery(elementQuery + "/released/text()");
        query.evaluateTo(&released);

        query.setQuery(elementQuery + "/images/image[@type=\"poster\" and @size=\"thumb\"]");
        query.evaluateTo(&thumbnailUrlXml);
        thumbnailUrl = obtainUrlFromImageTag(thumbnailUrlXml);

        query.setQuery(elementQuery + "/images/image[@type=\"poster\" and @size=\"w154\"]");
        query.evaluateTo(&posterUrlXml);
        posterUrl = obtainUrlFromImageTag(posterUrlXml);

        Movie newMovie(theMdbId.toInt(), name.trimmed());
        newMovie.setImdbId(imdbId.trimmed());
        newMovie.setOverview(overview.trimmed());
        newMovie.setYear(released.split("-").at(0).toInt());

        if (thumbnailUrl.isValid()) {
            newMovie.setThumbnailUrl(thumbnailUrl);
        }

        if (posterUrl.isValid()) {
            newMovie.setPosterUrl(posterUrl);
        }

        movieList.append(newMovie);
    }

    emit hasResults(movieList);
}

QUrl SearchMovie::obtainUrlFromImageTag(QString imageTag) {
    QDomDocument doc;
    doc.setContent(imageTag);
    QDomNode node = doc.elementsByTagName("image").at(0);
    return QUrl(node.toElement().attribute("url").trimmed());
}
