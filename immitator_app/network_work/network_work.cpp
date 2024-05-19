#include "network_work.h"

network_work::network_work(QObject * parrent) : QObject(parrent) {
    controll_app_ip = QHostAddress::LocalHost;
    controll_app_port = 5001;

    udp_socket = new QUdpSocket;
    if(!udp_socket->bind(controll_app_ip,controll_app_port)){
        qDebug()<<"network_work failed bind";
    }
    connect(udp_socket,SIGNAL(readyRead()),this,SLOT(read_data_from_socket()));
}

void network_work::change_ip_port(QHostAddress new_ip,uint32_t new_port){
    if(new_ip==controll_app_ip&&new_port==controll_app_port)return;

    controll_app_ip = new_ip;
    controll_app_port = new_port;

}

void network_work::read_data_from_socket(){

    do{
        QByteArray datagram;
        datagram.resize(udp_socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        if(udp_socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort)==-1){
            emit error_message_signal("readDatagram - fail!");
            return;
        }

        change_ip_port(sender,senderPort);

        if (datagram.size() < sizeof(uint32_t)){
            emit error_message_signal("Incorrect package!");
            return;
        }

        uint32_t command,index;
        QDataStream dataStream(datagram);
        dataStream >> command >> index;

        switch(command){
        case COMMAND_GET_INDICATORS_COUNT:
            emit get_count_indicators_signal();
            break;

        case COMMAND_GET_STAT:
            emit get_stat_indicator_signal(index);
            break;

        case COMMAND_INDIC_ACTION_ON:
            emit set_indicator_active(index,true);
            break;

        case COMMAND_INDIC_ACTION_OFF:
            emit set_indicator_active(index,false);
            break;
        }
    }
    while(udp_socket->hasPendingDatagrams());
}

void network_work::send_count_indicators_slot(uint32_t count){

    QByteArray sending_data;
    QDataStream out(&sending_data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);
    out << COMMAND_GET_INDICATORS_COUNT << count << sizeof(sIndicatorCommand);

    if(udp_socket->writeDatagram(sending_data,controll_app_ip,controll_app_port) == -1){
        qDebug()<<"Failed to write socket in send_count_indicators_slot";
    }
}

void network_work::send_indicator_info_slot(uint32_t index,sOneIndicatorStats stats){
    QByteArray sending_data;
    QDataStream out(&sending_data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);

    out << COMMAND_GET_STAT;
    out << index;

    out << stats.SerialNum;

    // Объединяем битовые поля в один 32-битный целочисленный тип
    uint32_t combinedFields = (stats.Type & 0xF) |
                              ((stats.Power & 0x1)<< 4) |
                              ((stats.Color & 0x3)<< 5) |
                              ((stats.Current_mA & 0x1FFFFFF)<< 7);
    out<< combinedFields;

    out<< stats.ErrorCode;

    out<< sizeof(sIndicatorStatisticsPack);

    if (udp_socket->writeDatagram(sending_data, controll_app_ip, controll_app_port) == -1) {
        qDebug()<< "Failed to write socket in send_indicator_info_slot";
    }
    /*
    QByteArray sending_data;

    QDataStream out(&sending_data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);

    out << COMMAND_GET_STAT;
    out << index;

    out << stats.SerialNum;
    out << stats.Type;
    out << stats.Power;
    out << stats.Color;
    out << stats.Current_mA;
    out << stats.ErrorCode;

    out << sizeof(sIndicatorStatisticsPack);

    if(udp_socket->writeDatagram(sending_data,controll_app_ip,controll_app_port) == -1){
        qDebug()<<"Failed to write socket in send_indicator_info_slot";
    }
*/
}
