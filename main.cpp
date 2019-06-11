#include "xansible.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication XAnsible(argc, argv);
    xansible app;
    app.show();

    return XAnsible.exec();
}
