#include "searchwindow.h"
#include "ui_searchwindow.h"

#include <QListWidgetItem>

SearchWindow::SearchWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
    ui->listWidget->setVisible(false);
    ui->noResultsLabel->setVisible(false);
}


SearchWindow::~SearchWindow()
{
    delete ui;
}

void SearchWindow::addResultItems(QList<Movie> movies) {
    qDebug("addResultItems!");
    foreach (Movie movie, movies) {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        item->setText(movie.getName() + " (" + QString::number(movie.getYear()) + ")");

        // TODO: fetch image
        ui->listWidget->addItem(item);
    }

    ui->listWidget->setVisible(true);
    ui->noResultsLabel->setVisible(false);
    ui->progressBar->setVisible(false);
}

void SearchWindow::showNoResultsFound() {
    ui->progressBar->setVisible(false);
    ui->listWidget->setVisible(false);
    ui->noResultsLabel->setVisible(true);
}
