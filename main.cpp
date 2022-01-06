#include "wifi_test.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WiFi_Test w;
    w.show();
    return a.exec();
}
