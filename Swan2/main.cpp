#include "worldwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WorldWidget w;
    w.show();

    return a.exec();
}
