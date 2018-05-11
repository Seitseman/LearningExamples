#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include "themewidget.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    ThemeWidget *widget = new ThemeWidget();
    QMainWindow w;
    w.setCentralWidget(widget);
    w.resize(900, 600);
    w.show();

    return a.exec();
}
