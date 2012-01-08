#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "searchresultitem.h"

SearchWindow::SearchWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
    ui->resultsArea->setVisible(false);
    ui->noResultsLabel->setVisible(false);
}


SearchWindow::~SearchWindow()
{
    delete ui;
}

void SearchWindow::addResultItems(QList<Movie> movies) {
    qDebug("addResultItems!");
    foreach (Movie movie, movies) {
        SearchResultItem *searchResult = new SearchResultItem(this);
        searchResult->setTitle(movie.getName());
        searchResult->setInfo(QString::number(movie.getYear()));

        // TODO: fetch image
        ui->resultsVBox->addWidget(searchResult);
    }

    ui->resultsArea->setVisible(true);
    ui->noResultsLabel->setVisible(false);
    ui->progressBar->setVisible(false);
}

void SearchWindow::showNoResultsFound() {
    ui->progressBar->setVisible(false);
    ui->resultsArea->setVisible(false);
    ui->noResultsLabel->setVisible(true);
}
