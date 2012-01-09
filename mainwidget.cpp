#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "searchmovie.h"
#include "searchwindow.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_submitSearchButton_clicked() {
    QString termsToSearch = ui->searchTextBox->text();

    SearchWindow *searchWindow = new SearchWindow(this);

    SearchMovie *searchMovie = new SearchMovie(termsToSearch);
    searchMovie->search();

    connect(searchMovie, SIGNAL(hasResults(QList<Movie>)), searchWindow, SLOT(setResults(QList<Movie>)));
    connect(searchMovie, SIGNAL(noResults()), searchWindow, SLOT(showNoResultsFound()));

    emit createWidget(searchWindow);
}

