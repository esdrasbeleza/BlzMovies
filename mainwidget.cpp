#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "searchmovie.h"
#include "searchwindow.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    populateSearchComboBox();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::populateSearchComboBox() {
    ui->searchOptionsCombobox->addItem("Movie", 1);
    ui->searchOptionsCombobox->addItem("Person", 2); // TODO: use constants of a Search class
    ui->searchOptionsCombobox->setCurrentIndex(0);
}


void MainWidget::on_submitSearchButton_clicked() {
    QString termsToSearch = ui->searchTextBox->text();

    SearchWindow *searchWindow = new SearchWindow(this);

    if (ui->searchOptionsCombobox->currentIndex() == 0) {
        SearchMovie *searchMovie = new SearchMovie(termsToSearch);
        searchMovie->search();

        connect(searchMovie, SIGNAL(hasResults(QList<Movie>)), searchWindow, SLOT(setResults(QList<Movie>)));
        connect(searchMovie, SIGNAL(noResults()), searchWindow, SLOT(showNoResultsFound()));
    }
    else {
        // TODO: person search
    }

    emit createWidget(searchWindow);
}

