#pragma once

#include <QObject>
#include <QPointer>
#include <QString>
#include <QtNetwork>
#include <QByteArray>
#include <QHostAddress>
#include <QUdpSocket>
#include <QTimer>
#include <array>

#include "Basic_Types.h"

class network_data : public QObject
{
    Q_OBJECT

private:

    QPointer<QTimer> time_view;

    QPointer<QUdpSocket> udp_socket;

    quintptr current_app_port, device_port;
    QHostAddress current_ip, device_ip;

    void get_indicator_info(uint32_t index);

    void write_request(sIndicatorCommand request_to_device);
    void read_answer();

    const uint32_t Polynomial = 0x04C11DB7;
    std::array<uint32_t, 256> crc32Table;
    uint32_t CalculateCrc32(const QByteArray &data);

private slots:

    void get_indicators_count_slot();

signals:

    void error_signal(QString);

    void new_indicators_count_signal(uint32_t);
    void indicator_info_signal(uint32_t,sOneIndicatorStats);
    void network_status_work_signal();

public slots:

    //  public API
    void change_device_ip_port(QHostAddress new_ip = QHostAddress::LocalHost, //  Later change to 192.168.100.167
                               quintptr new_port = 5001);

    void stop_timer_slot();

    void initial_indicators_slot();
    void get_all_indicators_data_slot(uint32_t indicators_count);
    void turn_indicator_power(uint32_t index,bool is_on);

public:
    network_data(QObject *parrent = 0);
};

