#include "moviedetailswidget.h"
#include "ui_moviedetailswidget.h"

#include <QAction>

MovieDetailsWidget::MovieDetailsWidget(Movie *movie, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MovieDetailsWidget)
{
    qDebug("Details!");
    ui->setupUi(this);
    this->movie = movie;

    createMenuOptions();
    populateData();
    makeButtonsWork();
    qDebug("Details end");

}

MovieDetailsWidget::~MovieDetailsWidget()
{
    delete ui;
}

void MovieDetailsWidget::addMenuActions() {
    // TODO
}

void MovieDetailsWidget::makeButtonsWork() {
    // TODO
}

void MovieDetailsWidget::populateData() {
    qDebug("Overview: " + movie->getOverview().toUtf8());

    ui->title->setText(movie->getName());
    ui->moviePoster->setPixmap(movie->getPoster());
    ui->year->setText(QString::number(movie->getYear()));
}

void MovieDetailsWidget::createMenuOptions() {
    QAction *backAction = new QAction("Close", this);
    backAction->setSoftKeyRole(QAction::NegativeSoftKey);
    connect(backAction, SIGNAL(triggered()), SLOT(close()));
    addAction(backAction);
}

