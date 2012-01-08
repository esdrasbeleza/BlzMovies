#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "searchresultlistitem.h"

SearchWindow::SearchWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
}

SearchWindow::~SearchWindow()
{
    delete ui;
}

void SearchWindow::addResultItems(QList<Movie*> movies) {
    foreach (Movie *movie, movies) {
        SearchResultListItem *listItem = new SearchResultListItem(ui->resultListWidget);
        listItem->setName(movie->getName());
        listItem->setDetails(QString::number(movie->getYear()));

        // TODO: fetch image

        ui->resultListWidget->addItem(listItem);
    }
}

void SearchWindow::showExpanded()
{
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR)
    showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
#else
    show();
#endif
}
