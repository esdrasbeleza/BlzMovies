#ifndef SEARCHRESULTLISTITEM_H
#define SEARCHRESULTLISTITEM_H

#include <QListWidgetItem>
#include "ui_result_item.h"

namespace Ui {
    class SearchResultListItem;
}

class SearchResultListItem : public QListWidgetItem
{
public:
    explicit SearchResultListItem(QListWidget *parent = 0);
    virtual ~SearchResultListItem();
    void setName(QString name);
    void setDetails(QString details);
    void setPixmap(QPixmap pixmap);

private:
    Ui::SearchResultListItem *ui;
    
    
};

#endif // SEARCHRESULTLISTITEM_H
