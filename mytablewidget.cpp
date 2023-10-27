#include "mytablewidget.h"

MyTableWidget::MyTableWidget(QWidget* parent):QTableWidget(parent) {
    connect(this, &MyTableWidget::itemDoubleClicked, this, &MyTableWidget::handleCellDoubleClicked);
}
void MyTableWidget::handleCellDoubleClicked(QTableWidgetItem* item) {
    if (item) {
        int column = item->column();
        if (column == 0) {
        // Handle the double-click event for the cell widget
            QWidget* cellWidget = new QWidget;
            if (cellWidget) {
                QString folderPath = QFileDialog::getExistingDirectory(nullptr, "Chọn thư mục ảnh", QDir::homePath());
                    if (!folderPath.isEmpty()) {
                        qDebug() << "Thư mục được chọn: " << folderPath;

                                    QDir directory(folderPath);

                        // Liệt kê các tệp và thư mục trong thư mục đã chọn
                        QStringList filesAndFolders = directory.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
                        for (const QString &item : filesAndFolders) {
                            qDebug() << "Item: " << item;
                        }
                    }
            }
        }
    }
}
