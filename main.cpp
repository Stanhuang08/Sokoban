#include <QApplication>
#include "ui.h"
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ui* U = new ui(new game());
    U -> show();

    return a.exec();
}
