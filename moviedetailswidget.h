#ifndef MOVIEDETAILSWIDGET_H
#define MOVIEDETAILSWIDGET_H

#include <QWidget>
#include "movie.h"

namespace Ui {
class MovieDetailsWidget;
}

class MovieDetailsWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MovieDetailsWidget(Movie *movie, QWidget *parent = 0);
    ~MovieDetailsWidget();
    
private:
    Ui::MovieDetailsWidget *ui;
    Movie *movie;
    void populateData();
    void createMenuOptions();
    void makeButtonsWork();
};

#endif // MOVIEDETAILSWIDGET_H