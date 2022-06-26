#include "View/chartmenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChartMenu home;
    home.show();

    return a.exec();
}
