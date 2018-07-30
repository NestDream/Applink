#include "applink.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    applink g;
    return a.exec();
}
