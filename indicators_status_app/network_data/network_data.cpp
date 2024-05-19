#include "network_data.h"

network_data::network_data(QObject *parrent):QObject(parrent) {

    udp_socket = new QUdpSocket(this);
    if(!udp_socket){
        emit error_signal("Failed to create socket");
    }

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

    change_device_ip_port();
}

void network_data::change_device_ip_port(QHostAddress new_ip, quintptr new_port){
    if(new_ip==device_ip&&new_port==device_port)return;

    device_ip = new_ip;
    device_port = new_port;
}

void network_data::initial_indicators_slot(){
    change_device_ip_port();
    get_indicators_count_slot();

    if(time_view)time_view->~QTimer();

    time_view = new QTimer;

    connect(time_view,SIGNAL(timeout()),this,SLOT(get_indicators_count_slot()));

    time_view->start(100);
}

void network_data::get_indicators_count_slot(){
    write_request({COMMAND_GET_INDICATORS_COUNT,0,sizeof(sIndicatorCommand)});
}

void network_data::write_request(sIndicatorCommand request_to_device){

    QByteArray sending_data;
    QDataStream out(&sending_data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);
    out << request_to_device.Command << request_to_device.IndicatorIndex << CalculateCrc32(sending_data);

    if(udp_socket->writeDatagram(sending_data,device_ip,device_port) == -1){
        emit error_signal("Fail by send request!");
        return;
    }

    if(request_to_device.Command==COMMAND_INDIC_ACTION_OFF
        ||request_to_device.Command==COMMAND_INDIC_ACTION_ON)return;

    if(udp_socket->waitForReadyRead(1000)){
        read_answer();
    }else{
        emit error_signal("No device answer!");
        udp_socket->close();
        return;
    }
}

uint32_t network_data::CalculateCrc32(const QByteArray &data){
    uint32_t crc = 0xFFFFFFFF;

    for (const auto &byte : data) {
        uint8_t index = (crc>> 24) ^ static_cast<uint8_t>(byte);
        crc = (crc<< 8) ^ crc32Table[index];
    }

    return crc ^ 0xFFFFFFFF;
}

void network_data::read_answer(){
    while(udp_socket->hasPendingDatagrams()){

        QByteArray datagram;
        datagram.resize(udp_socket->pendingDatagramSize());
        udp_socket->readDatagram(datagram.data(),datagram.size());

        uint32_t command,index;
        QDataStream dataStream(datagram);
        dataStream >> command >> index;

        datagram.chop(sizeof(uint32_t));

        switch(command){
        case COMMAND_GET_INDICATORS_COUNT:
            emit new_indicators_count_signal(index);
            break;

        case COMMAND_GET_STAT:

            sOneIndicatorStats tmp_stats;
            uint32_t combinedFields,crc;

            dataStream>> tmp_stats.SerialNum;

            dataStream>> combinedFields;

            tmp_stats.Type = combinedFields & 0xF;
            tmp_stats.Power = (combinedFields>> 4) & 0x1;
            tmp_stats.Color = (combinedFields>> 5) & 0x3;
            tmp_stats.Current_mA = (combinedFields>> 7) & 0x1FFFFFF;

            dataStream >>tmp_stats.ErrorCode>>crc;

            if(crc!=CalculateCrc32(datagram)){
                emit error_signal("CRC Fail!");
                return;
            }

            emit indicator_info_signal(index,tmp_stats);
            break;

        default:
            emit error_signal("Unknown command!");
            return;
            break;
        }
    }
}

void network_data::turn_indicator_power(uint32_t index,bool is_on){
    write_request({is_on?COMMAND_INDIC_ACTION_ON:COMMAND_INDIC_ACTION_OFF,index,sizeof(sIndicatorCommand)});
}

void network_data::get_indicator_info(uint32_t index){
    write_request({COMMAND_GET_STAT,index,sizeof(sIndicatorCommand)});
}

void network_data::get_all_indicators_data_slot(uint32_t indicators_count){
    //  Here can be some signal for progress bar
    for(uint32_t i = 0;i<indicators_count;++i){
        get_indicator_info(i);
    }
}

void network_data::stop_timer_slot(){
    time_view->~QTimer();
}
