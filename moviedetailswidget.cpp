#include "moviedetailswidget.h"
#include "ui_moviedetailswidget.h"

#include <QAction>

MovieDetailsWidget::MovieDetailsWidget(Movie *movie, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MovieDetailsWidget)
{
    ui->setupUi(this);
    this->movie = movie;

    createMenuOptions();
    populateData();
    makeButtonsWork();
}

MovieDetailsWidget::~MovieDetailsWidget()
{
    delete ui;
}

void MovieDetailsWidget::makeButtonsWork() {
    // TODO
}

void MovieDetailsWidget::populateData() {
    ui->title->setText(movie->getName());
    ui->moviePoster->setPixmap(movie->getPoster());
    ui->plot->setText(movie->getOverview());
    ui->year->setText(QString::number(movie->getYear()));
}

void MovieDetailsWidget::createMenuOptions() {
    QAction *backAction = new QAction("Close", this);
    backAction->setSoftKeyRole(QAction::NegativeSoftKey);
    connect(backAction, SIGNAL(triggered()), SLOT(close()));
    addAction(backAction);
}

