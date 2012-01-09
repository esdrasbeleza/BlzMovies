#include "moviedetailswidget.h"
#include "ui_moviedetailswidget.h"
#include "pictureloader.h"

#include <QAction>
#include <QStackedWidget>

MovieDetailsWidget::MovieDetailsWidget(Movie *movie, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MovieDetailsWidget)
{
    ui->setupUi(this);
    ui->scrollArea->setFocus();

    this->movie = movie;

    /*
     * Good function names are better than comments.
     */
    populateData();
    tryToFetchPoster();
    addMenuActions();
}

MovieDetailsWidget::~MovieDetailsWidget()
{
    delete ui;
}

void MovieDetailsWidget::tryToFetchPoster() {
    QPixmap defaultIcon(":/icons/movie");
    ui->moviePoster->setPixmap(defaultIcon);

    PictureLoader *pictureLoader = new PictureLoader(movie->getPosterUrl());
    connect(pictureLoader, SIGNAL(pictureReady(QPixmap)), SLOT(setPosterImage(QPixmap)));
}

void MovieDetailsWidget::setPosterImage(QPixmap pixmap) {
    ui->moviePoster->setPixmap(pixmap);
}

void MovieDetailsWidget::addMenuActions() {
    QAction *backToPreviousScreenAction = new QAction("Back", this);
    backToPreviousScreenAction->setSoftKeyRole(QAction::NegativeSoftKey);
    connect(backToPreviousScreenAction, SIGNAL(triggered()), SLOT(removeWidget()));
    addAction(backToPreviousScreenAction);
}

void MovieDetailsWidget::populateData() {
    ui->title->setText(movie->getName());
    ui->year->setText(QString::number(movie->getYear()));
    ui->plot->setText(movie->getOverview());
}

void MovieDetailsWidget::removeWidget() {
    QStackedWidget *stackedWidget = (QStackedWidget*) parent();
    stackedWidget->removeWidget(this);
    this->deleteLater();
}

