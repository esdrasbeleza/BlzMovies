#ifndef WINDOWWITHSEARCHRESULTS_H
#define WINDOWWITHSEARCHRESULTS_H

#include <QWidget>
#include <QPixmap>
#include <QListWidget>
#include <QListWidgetItem>

#include "movie.h"

namespace Ui {
class SearchWindow;
}

class WindowWithSearchResults : public QWidget
{
    Q_OBJECT
    
public:
    explicit WindowWithSearchResults(QWidget *parent);
    ~WindowWithSearchResults();
    void showExpanded();

public slots:
    void setResults(QList<Movie> movies);
    void showNoResultsFound();
    void showNetworkErrorLabel();
    
private slots:
    void on_listWidget_itemActivated(QListWidgetItem *item);
    void showDetailsAboutTheCurrentItem();
    void removeWidget();

private:
    Ui::SearchWindow *ui;
    void setWidgetsInitialState();
    void addSelectResultAction();
    QList<Movie> results;

};

#endif // WINDOWWITHSEARCHRESULTS_H
