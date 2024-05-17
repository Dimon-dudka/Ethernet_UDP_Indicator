#pragma once

#include <QObject>
#include <QPointer>
#include <QtNetwork>
#include <QUdpSocket>
#include <QByteArray>
#include <QHostAddress>

class network_work : public QObject
{
    Q_OBJECT
private:
    QPointer<QUdpSocket> udp_socket;

    QHostAddress controll_app_ip;
    quint16 controll_app_port;

public:
    network_work(QObject * parrent = 0);
};
