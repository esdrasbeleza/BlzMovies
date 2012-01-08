#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QWidget>
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
    void addResultItems(QList<Movie> movies);
    void showNoResultsFound();
    
private:
    Ui::SearchWindow *ui;
};

#endif // SEARCHWINDOW_H
