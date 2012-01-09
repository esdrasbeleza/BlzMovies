#ifndef MOVIEDETAILSWIDGET_H
#define MOVIEDETAILSWIDGET_H

#include <QWidget>
#include <QPixmap>

#include "movie.h"

namespace Ui {
class MovieDetailsWidget;
}

class MovieDetailsWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MovieDetailsWidget(Movie *movie, QWidget *parent);
    ~MovieDetailsWidget();
    
private:
    Ui::MovieDetailsWidget *ui;
    Movie *movie;
    void populateData();
    void addMenuActions();
    void createMenuOptions();
    void tryToFetchPoster();

private slots:
    void setPosterImage(QPixmap pixmap);
};

#endif // MOVIEDETAILSWIDGET_H
