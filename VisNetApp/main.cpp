#include "VisNetApp.h"
#include <QtWidgets/QApplication>
  
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    VisNetApp w;
    w.show();
    return a.exec();
}
