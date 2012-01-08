#include "searchresult.h"

SearchResult::SearchResult(Movie *movie, QListWidget *listWidget, QObject *parent) : QObject(parent)
{
    defaultIcon = QPixmap(":/icons/movie");

    this->listWidget = listWidget;
    this->movie = movie;

    listItem = new QListWidgetItem(listWidget);
}

QListWidgetItem* SearchResult::getListItem() {
    /*
     * Set the item data only when they are needed.
     */
    QString text = movie->getName() + " (" + QString::number(movie->getYear()) + ")";
    listItem->setText(text);
    listItem->setIcon(defaultIcon);
    return listItem;
}

void SearchResult::fetchIcon() {
    if (movie->getPosterUrl().isValid()) {
        pictureLoader = new PictureLoader(movie->getPosterUrl());
        connect(pictureLoader, SIGNAL(pictureReady(QPixmap)), SLOT(setIconForItem(QPixmap)));
    }
}

void SearchResult::setIconForItem(QPixmap pixmap) {
    QIcon icon(pixmap);
    listItem->setIcon(icon);
    pictureLoader->deleteLater();
}
