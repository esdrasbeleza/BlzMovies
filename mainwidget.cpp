#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "searchmovie.h"
#include "windowwithsearchresults.h"

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

    /*
     * The widget that will contain the results
     */
    WindowWithSearchResults *windowWithSearchResults = new WindowWithSearchResults(this);

    /*
     * Call the class that looks for the movie
     */
    SearchMovie *searchMovie = new SearchMovie(termsToSearch);
    searchMovie->search();

    /*
     * When we get the results, show them in the widget created above
     */
    connect(searchMovie, SIGNAL(hasResults(QList<Movie>)), windowWithSearchResults, SLOT(setResults(QList<Movie>)));
    connect(searchMovie, SIGNAL(noResults()), windowWithSearchResults, SLOT(showNoResultsFound()));

    /*
     * Shows the widget that will show the results
     */
    windowWithSearchResults->setMaximumSize(window()->width(), window()->height());
    windowWithSearchResults->showMaximized();
    windowWithSearchResults->activateWindow();
    windowWithSearchResults->raise();
    windowWithSearchResults->setAutoFillBackground(true);
}

