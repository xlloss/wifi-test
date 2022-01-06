#ifndef WIFI_TEST_H
#define WIFI_TEST_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class WiFi_Test; }
QT_END_NAMESPACE

class WiFi_Test : public QMainWindow
{
    Q_OBJECT

public:
    WiFi_Test(QWidget *parent = nullptr);
    ~WiFi_Test();

private slots:
    void on_wifi_enable_clicked();

    void on_secure_none_clicked();

    void on_secure_wpa2_clicked();

    void on_wifi_stop_clicked();

private:
    Ui::WiFi_Test *ui;
};
#endif // WIFI_TEST_H
