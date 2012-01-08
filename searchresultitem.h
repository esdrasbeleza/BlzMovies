#ifndef SEARCHRESULTITEM_H
#define SEARCHRESULTITEM_H

#include <QWidget>

namespace Ui {
class SearchResultItem;
}

class SearchResultItem : public QWidget
{
    Q_OBJECT
    
public:
    explicit SearchResultItem(QWidget *parent = 0);
    ~SearchResultItem();
    void setTitle(QString title);
    void setInfo(QString info);
    void setPixmap(QPixmap pixmap);
    
private:
    Ui::SearchResultItem *ui;
};

#endif // SEARCHRESULTITEM_H
