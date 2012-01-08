#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QObject>
#include <QListWidgetItem>
#include <QUrl>
#include <QPixmap>
#include <QListWidget>

#include "movie.h"
#include "pictureloader.h"

class SearchResult : public QObject , public QListWidgetItem
{
    Q_OBJECT

public:
    SearchResult(Movie *movie, QListWidget *listWidget = 0, QObject *parent = 0);
    QListWidgetItem* getListItem();
    void fetchIcon();
    void setIconUrl(QUrl url);

private:
    QListWidget *listWidget;
    PictureLoader *pictureLoader;
    QListWidgetItem *resultItem;
    QPixmap defaultIcon;
    Movie *movie;
    QListWidgetItem *listItem;

private slots:
    void setIconForItem(QPixmap pixmap);
};

#endif // SEARCHRESULT_H
