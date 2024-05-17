#pragma once

#include <QObject>
#include <QPointer>
#include <QString>
#include <QtNetwork>
#include <QByteArray>
#include <QHostAddress>
#include <QUdpSocket>
#include <QTimer>

#include "Basic_Types.h"

class network_data : public QObject
{
    Q_OBJECT

private:

    QPointer<QTimer> time_view;

    QPointer<QUdpSocket> udp_socket;

    quint16 indicators_count;

    quintptr current_app_port, device_port;
    QHostAddress current_ip, device_ip;

    void get_indicators_count();

    void get_index_indicator_data(const quint16& index);

private slots:
    void get_all_indicators_data();

signals:

    void error_signal(QString);

public slots:

    //  public API
    void change_device_ip_port(QHostAddress new_ip = QHostAddress::LocalHost, //  Later change to 192.168.100.167
                               quintptr new_port = 5001);

    void initial_indicators();

public:
    network_data(QObject *parrent = 0);
};

