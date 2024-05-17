#include "network_data.h"

network_data::network_data(QObject *parrent):QObject(parrent) {

    udp_socket = new QUdpSocket(this);
    if(!udp_socket){
        qDebug()<<"Failed to create socket";
    }

    change_device_ip_port();

    indicators_count = 0;
}

void network_data::change_device_ip_port(QHostAddress new_ip, quintptr new_port){
    if(new_ip==device_ip&&new_port==device_port)return;
    //if(udp_socket->isValid()||udp_socket->isOpen())udp_socket->close();

    device_ip = new_ip;
    device_port = new_port;

    //if(!udp_socket->bind(device_ip,device_port)){
      //  qDebug()<<"Failed to bind socket in change_device_ip_port";
    //}
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
    QDataStream out(&sending_data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);
    out << indicators_count_request.Command << indicators_count_request.IndicatorIndex << indicators_count_request.crc32;

    qDebug()<<sending_data.size()<<" "<<QString::number(COMMAND_GET_INDICATORS_COUNT);

    if(udp_socket->writeDatagram(sending_data,device_ip,device_port) == -1){
        qDebug()<<"Failed to write socket in get_indicators_count";
    }

    if(udp_socket->waitForReadyRead(1000)){
        while(udp_socket->hasPendingDatagrams()){
            QByteArray datagram;
            datagram.resize(udp_socket->pendingDatagramSize());
            udp_socket->readDatagram(datagram.data(),datagram.size());
            qDebug()<<"Readed";
        }
    }

}

void network_data::get_all_indicators_data(){

}

void network_data::get_index_indicator_data(const quint16& index){
    qDebug()<<"time";
}

