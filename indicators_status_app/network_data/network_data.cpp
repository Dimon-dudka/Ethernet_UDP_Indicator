#include "network_data.h"

network_data::network_data(QObject *parrent):QObject(parrent) {

    udp_socket = new QUdpSocket;

    change_device_ip_port();

    indicators_count = 0;
}

void network_data::change_device_ip_port(QHostAddress new_ip, quintptr new_port){
    if(udp_socket->isValid()||udp_socket->isOpen())udp_socket->close();

    device_ip = new_ip;
    device_port = new_port;

    udp_socket->bind(device_ip,device_port);
}

void network_data::initial_indicators(){
    get_indicators_count();

    if(time_view)time_view->~QTimer();

    time_view = new QTimer;

    connect(time_view,SIGNAL(timeout()),this,SLOT(get_all_indicators_data()));

    time_view->start(1000);
}

void network_data::get_indicators_count(){
    sIndicatorCommand indicators_count_request{COMMAND_GET_INDICATORS_COUNT,
                                               0,sizeof(sIndicatorCommand)};

    QByteArray sending_data;
    sending_data.append(reinterpret_cast<const char*>(&indicators_count_request),
                        sizeof(sIndicatorCommand));

    udp_socket->write(sending_data);

    if(udp_socket->waitForReadyRead(1000)){
        while(udp_socket->hasPendingDatagrams()){
            QByteArray datagram;
            datagram.resize(udp_socket->pendingDatagramSize());
            udp_socket->readDatagram(datagram.data(),datagram.size());
        }
    }



}

void network_data::get_all_indicators_data(){

}

void network_data::get_index_indicator_data(const quint16& index){
    qDebug()<<"time";
}

