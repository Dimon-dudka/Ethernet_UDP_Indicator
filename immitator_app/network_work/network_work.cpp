#include "network_work.h"

network_work::network_work(QObject * parrent) : QObject(parrent) {
    controll_app_ip = QHostAddress::LocalHost;
    controll_app_port = 5001;

    udp_socket = new QUdpSocket;
    if(!udp_socket->bind(controll_app_ip,controll_app_port)){
        qDebug()<<"network_work failed bind";
    }
    connect(udp_socket,SIGNAL(readyRead()),this,SLOT(read_data_from_socket()));

    for (uint32_t i = 0; i < 256; ++i) {
        uint32_t crc = i<< 24;
        for (uint8_t j = 0; j < 8; ++j) {
            if (crc & 0x80000000) {
                crc = (crc << 1) ^ Polynomial;
            } else {
                crc = crc << 1;
            }
        }
        crc32Table[i] = crc;
    }
}

uint32_t network_work::CalculateCrc32(const QByteArray &data) {
    uint32_t crc = 0xFFFFFFFF;

    for (const auto &byte : data) {
        uint8_t index = (crc>> 24) ^ static_cast<uint8_t>(byte);
        crc = (crc<< 8) ^ crc32Table[index];
    }

    return crc ^ 0xFFFFFFFF;
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

        uint32_t command,index,crc;
        QDataStream dataStream(datagram);
        dataStream >> command >> index>>crc;

        datagram.chop(sizeof(uint32_t));

        if(crc!=CalculateCrc32(datagram)){
            emit error_message_signal("CRC32 mismatch!");
            return;
        }

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
    out << COMMAND_GET_INDICATORS_COUNT << count << CalculateCrc32(sending_data);

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

    uint32_t combinedFields = (stats.Type & 0xF) |
                              ((stats.Power & 0x1)<< 4) |
                              ((stats.Color & 0x3)<< 5) |
                              ((stats.Current_mA & 0x1FFFFFF)<< 7);
    out<< combinedFields;

    out<< stats.ErrorCode;

    out<< CalculateCrc32(sending_data);

    if (udp_socket->writeDatagram(sending_data, controll_app_ip, controll_app_port) == -1) {
        qDebug()<< "Failed to write socket in send_indicator_info_slot";
    }

}
