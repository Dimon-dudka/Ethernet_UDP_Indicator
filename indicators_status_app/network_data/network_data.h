#pragma once

#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>

class network_data : public QObject
{
    Q_OBJECT

private:

    quintptr current_app_port, device_port;
    QHostAddress current_ip, device_ip;


public slots:

    void change_device_ip_port(QHostAddress new_ip = QHostAddress::LocalHost, //  Later change to 192.168.100.167
                               quintptr new_port = 5001);

public:
    network_data(QObject *parrent = 0);
};

