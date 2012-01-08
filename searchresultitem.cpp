#include "searchresultitem.h"
#include "ui_searchresultitem.h"

SearchResultItem::SearchResultItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchResultItem)
{
    ui->setupUi(this);
    ui->nameLabel->setMaximumWidth(width()/2);
    ui->imageLabel->setMaximumWidth(width()/2);

}

SearchResultItem::~SearchResultItem()
{
    delete ui;
}

void SearchResultItem::setTitle(QString title) {
    ui->nameLabel->setText(title);
}

void SearchResultItem::setInfo(QString info) {
    ui->infoLabel->setText(info);
}

void SearchResultItem::setPixmap(QPixmap pixmap) {
    ui->imageLabel->setPixmap(pixmap);
}
