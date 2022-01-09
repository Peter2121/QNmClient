#include "nmsocketwindow.h"

#include <QApplication>

const QString NMD_SOCKET="/var/run/nmd.socket";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NmSocketWindow nmw(NMD_SOCKET);
    nmw.show();
    return a.exec();
}
