#ifndef WINDOWWITHSEARCHRESULTS_H
#define WINDOWWITHSEARCHRESULTS_H

#include <QWidget>
#include <QPixmap>
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
    
private slots:
    void on_listWidget_itemActivated(QListWidgetItem *item);
    void showDetailsAboutTheCurrentItem();

private:
    Ui::SearchWindow *ui;
    void setWidgetsInitialState();
    void addSelectResultAction();
    QList<Movie> results;

};

#endif // WINDOWWITHSEARCHRESULTS_H
