#include "moviedetailswidget.h"
#include "ui_moviedetailswidget.h"
#include "pictureloader.h"

#include <QAction>

MovieDetailsWidget::MovieDetailsWidget(Movie *movie, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MovieDetailsWidget)
{
    ui->setupUi(this);
    this->movie = movie;

    createMenuOptions();
    populateData();
    tryToFetchPoster();
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
    QAction *backToPreviousScreenAction = new QAction("Results", this);
    backToPreviousScreenAction->setSoftKeyRole(QAction::NegativeSoftKey);
    connect(backToPreviousScreenAction, SIGNAL(triggered()), SLOT(deleteLater()));
    addAction(backToPreviousScreenAction);
}

void MovieDetailsWidget::populateData() {
    ui->title->setText(movie->getName());
    ui->year->setText(QString::number(movie->getYear()));
    ui->plot->setText(movie->getOverview());
}

void MovieDetailsWidget::createMenuOptions() {
    QAction *backAction = new QAction("Close", this);
    backAction->setSoftKeyRole(QAction::NegativeSoftKey);
    connect(backAction, SIGNAL(triggered()), SLOT(close()));
    addAction(backAction);
}

