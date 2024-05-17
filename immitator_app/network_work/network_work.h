#pragma once

#include <QObject>
#include <QPointer>
#include <QtNetwork>
#include <QUdpSocket>
#include <QByteArray>
#include <QHostAddress>

#include "Basic_Types.h"

class network_work : public QObject
{
    Q_OBJECT
private:
    QPointer<QUdpSocket> udp_socket;

    QHostAddress controll_app_ip;
    quint16 controll_app_port;

    void change_ip_port(QHostAddress new_ip,quint16 new_port);

private slots:

    void read_data_from_socket();

public slots:

    void send_count_indicators_slot(uint32_t count);

signals:

    void error_message_signal(QString);

    //  Manage signals
    void get_count_indicators_signal();
    void get_stat_indicator_signal(quint16);
    void set_indicator_active(quint16,bool);    //  0 - OFF, 1 - ON

public:
    network_work(QObject * parrent = 0);
};
