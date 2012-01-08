#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "randommovie.h"
#include "searchmovie.h"
#include "searchwindow.h"

#include <QtCore/QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    qDebug("Constructor");
    ui->setupUi(this);
    ui->randomMovieTitleLabel->setVisible(false);
    ui->fetchingRandomMovieInfoProgressBar->setVisible(false);
    ui->randomMovieImage->setVisible(false);

    populateSearchComboBox();
    fetchInformationAboutTheLastMovie();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateSearchComboBox() {
    ui->searchOptionsCombobox->addItem("Movie", 1);
    ui->searchOptionsCombobox->addItem("Person", 2); // TODO: use constants of a Search class
    ui->searchOptionsCombobox->setCurrentIndex(0);
}

void MainWindow::fetchInformationAboutTheLastMovie() {
    RandomMovie *randomMovie = new RandomMovie(this);
    randomMovie->fetchARandomMovie();
    showProgressBar();
    connect(randomMovie, SIGNAL(movieInfoAvailable(Movie*)), SLOT(showMovieInfo(Movie*)));
}

void MainWindow::showProgressBar() {
    ui->fetchingRandomMovieInfoProgressBar->setVisible(true);
}

void MainWindow::hideProgressBar() {
    ui->fetchingRandomMovieInfoProgressBar->setVisible(true);
}

void MainWindow::showMovieInfo(Movie *movie) {
    showMoviePoster(movie);
    showMovieName(movie);
}

void MainWindow::showMoviePoster(Movie *movie) {
    QPixmap *image = new QPixmap();
    ui->randomMovieImage->setPixmap(movie->getPoster());
}

void MainWindow::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void MainWindow::showExpanded()
{
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR)
    showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
#else
    show();
#endif
}

void MainWindow::showMovieName(Movie *movie) {
    ui->randomMovieTitleLabel->setVisible(true);
    ui->randomMovieTitleLabel->setText(movie->getName());
}

void MainWindow::on_submitSearchButton_clicked()
{
    QString termsToSearch = ui->searchTextBox->text();

    SearchWindow *searchWindow = new SearchWindow(this);
    // TODO: show feedback

    if (ui->searchOptionsCombobox->currentIndex() == 1) {
        SearchMovie *searchMovie = new SearchMovie(termsToSearch);
        searchMovie->search();

        connect(searchMovie, SIGNAL(hasResults(QList<Movie*>)), searchWindow, SLOT(addResultItems(QList<Movie*>)));
    }
    else {

    }

    searchWindow->showExpanded();
}
