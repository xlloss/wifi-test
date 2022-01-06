#include "wifi_test.h"
#include "ui_wifi_test.h"
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>
WiFi_Test::WiFi_Test(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WiFi_Test)
{
    ui->setupUi(this);
    ui->secure_wpa2->click();
}

WiFi_Test::~WiFi_Test()
{
    delete ui;
}


void WiFi_Test::on_wifi_enable_clicked()
{
    QString ssid, passwd;
    QProcess process;
    QStringList arguments;
    QString cmd("/usr/bin/wifi_set.sh");
    QString wpatool_cmd("systemctl");
    QString wpatool_cmd_atgs1("restart");
    QString wpatool_cmd_atgs2("wpa_supplicant-nl80211@wlan0");
    QString udhcpc_cmd("udhcpc");
    QString udhcpc_cmd_atgs1("-i");
    QString udhcpc_cmd_atgs2("wlan0");

    if (ui->ssid_edit->toPlainText().isEmpty() == true) {
        qDebug() << "SSID Error";
        QMessageBox::warning(this, "SSID Error", "Please input SSID");
        return;
    }

    if (ui->secure_none->isChecked() == true) {
        if (ui->ssid_edit->toPlainText().isEmpty() == true) {
            passwd.append("");
        }
    }

    arguments.removeAll(udhcpc_cmd_atgs1);
    arguments.removeAll(udhcpc_cmd_atgs2);

    ssid.append(ui->ssid_edit->toPlainText());
    passwd.append(ui->passwd_edit->toPlainText());
    arguments << ssid << passwd;
    process.start(cmd, arguments);
    process.waitForFinished();
    if(process.exitCode() != 0)
        qDebug () << "wifi_set error" << process.exitCode() << process.readAllStandardError();
    else
        qDebug () << " Ok " << process.readAllStandardOutput();

    arguments.removeAll(ssid);
    arguments.removeAll(passwd);

    arguments << wpatool_cmd_atgs1 << wpatool_cmd_atgs2;
    process.start(wpatool_cmd, arguments);
    process.waitForFinished();
    if(process.exitCode() != 0)
        qDebug () << "wpatool_cmd error" << process.exitCode() << process.readAllStandardError();
    else
        qDebug () << " Ok " << process.readAllStandardOutput();

    arguments.removeAll(wpatool_cmd_atgs1);
    arguments.removeAll(wpatool_cmd_atgs2);

    arguments << udhcpc_cmd_atgs1 << udhcpc_cmd_atgs2;
    process.start(udhcpc_cmd, arguments);
    process.waitForFinished();
    if(process.exitCode() != 0)
        qDebug () << "udhcpc_cmd error" << process.exitCode() << process.readAllStandardError();
    else
        qDebug () << " Ok " << process.readAllStandardOutput();
}

void WiFi_Test::on_secure_none_clicked()
{
    ui->ssid_edit->setEnabled(true);
    ui->passwd_edit->setEnabled(false);
}

void WiFi_Test::on_secure_wpa2_clicked()
{
    ui->ssid_edit->setEnabled(true);
    ui->passwd_edit->setEnabled(true);
}

void WiFi_Test::on_wifi_stop_clicked()
{
    QProcess process;
    QString wpatool_cmd("systemctl");
    QString wpatool_cmd_atgs1("stop");
    QString wpatool_cmd_atgs2("wpa_supplicant-nl80211@wlan0");
    QStringList arguments;

    arguments << wpatool_cmd_atgs1 << wpatool_cmd_atgs2;
    process.start(wpatool_cmd, arguments);
    process.waitForFinished();
    if(process.exitCode() != 0)
        qDebug () << "wpatool_cmd error" << process.exitCode() << process.readAllStandardError();
    else
        qDebug () << " Ok " << process.readAllStandardOutput();

}
