#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H
#include <QTableWidget>
#include <QTableWidgetItem>
#include "QFileDialog"
class MyTableWidget:public QTableWidget
{
public:
    MyTableWidget(QWidget* parent);
public slots:
    void handleCellDoubleClicked(QTableWidgetItem* item);
};

#endif // MYTABLEWIDGET_H
