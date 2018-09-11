#include "application.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Application a(&argc, &argv);

    a.initialize();

    return a.exec();
}
