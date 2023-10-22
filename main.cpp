#include "mainwindow.h"
#include <QtWidgets>
#include <QApplication>
#include "mainmenu.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    MainWindow mainWindow;
    MainMenu mainMenu;
    mainWindow.setGeometry(0,0,w,h);
    mainWindow.move(0,0);
    mainWindow.show();
    return a.exec();
}
