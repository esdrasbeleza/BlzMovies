#include "searchresultlistitem.h"

SearchResultListItem::SearchResultListItem(QListWidget *parent) :
    QListWidgetItem(parent)
{
    ui->setupUi(parent);
}

SearchResultListItem::~SearchResultListItem() {
    delete ui;
}

void SearchResultListItem::setName(QString name) {
    ui->title->setText(name);
}

void SearchResultListItem::setDetails(QString details) {
    ui->details->setText(details);
}

void SearchResultListItem::setPixmap(QPixmap pixmap) {
    ui->image->setPixmap(pixmap);
}
