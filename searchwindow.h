#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QWidget>
#include <QPixmap>
#include <QListWidgetItem>

#include "movie.h"

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit SearchWindow(QWidget *parent = 0);
    ~SearchWindow();
    void showExpanded();

public slots:
    void setResults(QList<Movie> movies);
    void showNoResultsFound();
    
private slots:
    void on_listWidget_itemActivated(QListWidgetItem *item);

private:
    Ui::SearchWindow *ui;
    void setWidgetsInitialState();
    QList<Movie> results;

};

#endif // SEARCHWINDOW_H
