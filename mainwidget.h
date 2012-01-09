#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWidget(QWidget *parent);
    ~MainWidget();
    
signals:
    void createWidget(QWidget*);

private slots:
    void on_submitSearchButton_clicked();

private:
    Ui::MainWidget *ui;
    void populateSearchComboBox();
};

#endif // MAINWIDGET_H
