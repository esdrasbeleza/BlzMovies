#include "randommovie.h"

#include <QDomDocument>


RandomMovie::RandomMovie(QObject *parent) :
    QObject(parent)
{
}

void RandomMovie::fetchARandomMovie() {
    QUrl url("http://api.themoviedb.org/2.1/Movie.getLatest/en/xml/" + QString(THEMOVIEDB_KEY));
    networkAccessManager = new QNetworkAccessManager(this);
    QNetworkRequest netRequest;
    netRequest.setUrl(url);
    requestReply = networkAccessManager->get(netRequest);

    connect(requestReply, SIGNAL(finished()), this, SLOT(readReplyForLastRegisteredMovie()));
}

void RandomMovie::readReplyForLastRegisteredMovie() {
    QString replyString = requestReply->readAll();

    // Parse the XML response
    QDomDocument xmlContent;
    xmlContent.setContent(replyString);

    QDomNodeList resultNumberList = xmlContent.elementsByTagName("opensearch:totalResults");
    int resultNumber = resultNumberList.at(0).toElement().text().toInt(); // TODO: what if we don't get results?

    if (resultNumber > 0) {
        QDomNode lastMovieNode = xmlContent.elementsByTagName("movie").at(0);
        int lastMovieId = lastMovieNode.toElement().elementsByTagName("id").at(0).toElement().text().toInt();
        int movieId = qrand() % (lastMovieId - 5000); // Use older movie IDs, so it's more sure we can have a poster!
    }
}
