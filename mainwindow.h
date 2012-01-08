#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "movie.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    // Note that this will only have an effect on Symbian and Fremantle.
    void setOrientation(ScreenOrientation orientation);

    void showExpanded();

private slots:
    void showMovieInfo(Movie *movie);


    void on_submitSearchButton_clicked();

private:
    Ui::MainWindow *ui;
    void populateSearchComboBox();
    void showProgressBar();
    void hideProgressBar();
    void showMoviePoster(Movie *movie);
    void showMovieName(Movie *movie);
    void fetchInformationAboutTheLastMovie();
};

#endif // MAINWINDOW_H
