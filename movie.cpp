#include "movie.h"

Movie::Movie(int id, QString name) {
    this->id = id;
    this->name = name;
}

int Movie::getId() {
   return id;
}

QString Movie::getImdbId() {
    return imdbId;
}

void Movie::setImdbId(QString imdbId) {
    this->imdbId = imdbId;
}

QString Movie::getName() {
    return name;
}

void Movie::setName(QString name) {
    this->name = name;
}

QString Movie::getOverview() {
    return overview;
}

void Movie::setOverview(QString overView) {
    this->overview = overView;
}

QPixmap Movie::getThumbnail() {
    return thumbnail;
}

void Movie::setThumbnail(QPixmap poster) {
    this->thumbnail = poster;
}

QUrl Movie::getThumbnailUrl() {
    return thumbnailUrl;
}

void Movie::setThumbnailUrl(QUrl thumbnailUrl) {
    this->thumbnailUrl = thumbnailUrl;
}

QPixmap Movie::getPoster() {
    return poster;
}

void Movie::setPoster(QPixmap poster) {
    this->poster = poster;
}

QUrl Movie::getPosterUrl() {
    return posterUrl;
}

void Movie::setPosterUrl(QUrl posterUrl) {
    this->posterUrl = posterUrl;
}

int Movie::getYear() {
    return year;
}

void Movie::setYear(int year) {
    this->year = year;
}
