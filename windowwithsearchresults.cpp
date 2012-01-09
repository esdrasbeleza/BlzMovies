#include "windowwithsearchresults.h"
#include "ui_searchwindow.h"
#include "searchresult.h"
#include "moviedetailswidget.h"

#include <QAction>

WindowWithSearchResults::WindowWithSearchResults(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
    setWidgetsInitialState();

    QAction *backToMainScreenAction = new QAction("Back", this);
    backToMainScreenAction->setSoftKeyRole(QAction::NegativeSoftKey);
    connect(backToMainScreenAction, SIGNAL(triggered()), SLOT(deleteLater()));
    addAction(backToMainScreenAction);
}

void WindowWithSearchResults::addSelectResultAction() {
    QAction *selectResultAction = new QAction("Details", this);
    selectResultAction->setSoftKeyRole(QAction::PositiveSoftKey);
    connect(selectResultAction, SIGNAL(triggered()), SLOT(showDetailsAboutTheCurrentItem()));
    addAction(selectResultAction);
}

WindowWithSearchResults::~WindowWithSearchResults()
{
    delete ui;
}

void WindowWithSearchResults::setWidgetsInitialState() {
    ui->listWidget->setVisible(false);
    ui->noResultsLabel->setVisible(false);
}

void WindowWithSearchResults::setResults(QList<Movie> movies) {
    this->results = movies;

    foreach (Movie movie, movies) {
        SearchResult *searchResult = new SearchResult(&movie, ui->listWidget, this);
        ui->listWidget->addItem(searchResult->getListItem());
        searchResult->fetchIcon();
    }

    ui->listWidget->setVisible(true);
    ui->noResultsLabel->setVisible(false);
    ui->progressContainer->setVisible(false);

    if (movies.size() > 0) {
        addSelectResultAction();
    }
}

void WindowWithSearchResults::showNoResultsFound() {
    ui->progressContainer->setVisible(false);
    ui->listWidget->setVisible(false);
    ui->noResultsLabel->setVisible(true);
}


void WindowWithSearchResults::on_listWidget_itemActivated(QListWidgetItem *item)
{
    showDetailsAboutTheCurrentItem();
}

void WindowWithSearchResults::showDetailsAboutTheCurrentItem() {
    Movie movie = results.at(ui->listWidget->currentRow());
    MovieDetailsWidget *movieDetailsWidget = new MovieDetailsWidget(&movie, this);

    movieDetailsWidget->setMaximumSize(window()->width(), window()->height());
    movieDetailsWidget->setAutoFillBackground(true);
    movieDetailsWidget->showMaximized();
    movieDetailsWidget->activateWindow();
    movieDetailsWidget->raise();
    movieDetailsWidget->setFocus(Qt::OtherFocusReason);

}
