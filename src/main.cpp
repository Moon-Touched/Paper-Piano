#include "piano.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Piano w;
    w.show();
    return a.exec();
}
