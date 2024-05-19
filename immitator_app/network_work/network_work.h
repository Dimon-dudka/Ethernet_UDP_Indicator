#pragma once

#include <QObject>
#include <QPointer>
#include <QtNetwork>
#include <QUdpSocket>
#include <QByteArray>
#include <QHostAddress>
#include <array>

#include "Basic_Types.h"

class network_work : public QObject
{
    Q_OBJECT
private:
    QPointer<QUdpSocket> udp_socket;

    QHostAddress controll_app_ip;
    uint32_t controll_app_port;

    const uint32_t Polynomial = 0x04C11DB7;
    std::array<uint32_t, 256> crc32Table;
    uint32_t CalculateCrc32(const QByteArray &data);

    void change_ip_port(QHostAddress new_ip,uint32_t new_port);

private slots:

    void read_data_from_socket();

public slots:

    void send_count_indicators_slot(uint32_t count);
    void send_indicator_info_slot(uint32_t index,sOneIndicatorStats stats);

signals:

    void error_message_signal(QString);

    //  Manage signals
    void get_count_indicators_signal();
    void get_stat_indicator_signal(uint32_t);
    void set_indicator_active(uint32_t,bool);    //  0 - OFF, 1 - ON

public:
    network_work(QObject * parrent = 0);
};
