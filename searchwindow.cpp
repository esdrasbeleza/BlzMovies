#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "searchresult.h"

#include <QListWidgetItem>

SearchWindow::SearchWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
    setWidgetsInitialState();
}

SearchWindow::~SearchWindow()
{
    delete ui;
}

void SearchWindow::setWidgetsInitialState() {
    ui->listWidget->setVisible(false);
    ui->noResultsLabel->setVisible(false);
}

void SearchWindow::setResults(QList<Movie> movies) {
    foreach (Movie movie, movies) {
        SearchResult *searchResult = new SearchResult(&movie, ui->listWidget, this);
        ui->listWidget->addItem(searchResult->getListItem());
        searchResult->fetchIcon();
    }

    ui->listWidget->setVisible(true);
    ui->noResultsLabel->setVisible(false);
    ui->progressContainer->setVisible(false);
}

void SearchWindow::showNoResultsFound() {
    ui->progressContainer->setVisible(false);
    ui->listWidget->setVisible(false);
    ui->noResultsLabel->setVisible(true);
}

void SearchWindow::on_listWidget_clicked(const QModelIndex &index)
{
    qDebug("Clicked!");
}
