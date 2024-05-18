#include "network_data.h"

network_data::network_data(QObject *parrent):QObject(parrent) {

    udp_socket = new QUdpSocket(this);
    if(!udp_socket){
        emit error_signal("Failed to create socket");
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
    get_indicators_count();

    if(time_view)time_view->~QTimer();

    time_view = new QTimer;

    //connect(time_view,SIGNAL(timeout()),this,SLOT(get_all_indicators_data()));

    time_view->start(1000);
}

void network_data::get_indicators_count(){
    write_request({COMMAND_GET_INDICATORS_COUNT,0,sizeof(sIndicatorCommand)});
}

void network_data::write_request(sIndicatorCommand request_to_device){

    QByteArray sending_data;
    QDataStream out(&sending_data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);
    out << request_to_device.Command << request_to_device.IndicatorIndex << request_to_device.crc32;

    if(udp_socket->writeDatagram(sending_data,device_ip,device_port) == -1){
        emit error_signal("Fail by send request!");
    }

    if(udp_socket->waitForReadyRead(1000)){
        read_answer();
    }else{
        //emit error_signal("No device answer!");
    }
}

void network_data::read_answer(){
    while(udp_socket->hasPendingDatagrams()){

        QByteArray datagram;
        datagram.resize(udp_socket->pendingDatagramSize());
        udp_socket->readDatagram(datagram.data(),datagram.size());

        uint32_t command,index;
        QDataStream dataStream(datagram);
        dataStream >> command >> index;

        switch(command){
        case COMMAND_GET_INDICATORS_COUNT:
            qDebug()<<"OK";
            emit new_indicators_count_signal(index);
            break;

        case COMMAND_GET_STAT:
            sOneIndicatorStats tmp_stats;
            quint32 typeValue;

            dataStream >> tmp_stats.SerialNum;

            dataStream >> typeValue;
            tmp_stats.Type = typeValue & 0b1111;
            tmp_stats.Power = (typeValue >> 4) & 0b1;
            tmp_stats.Color = (typeValue >> 5) & 0b11;

            quint32 current_mA_bits;
            dataStream >> current_mA_bits >> tmp_stats.ErrorCode;

            tmp_stats.Current_mA = static_cast<quint32>(current_mA_bits);

            emit indicator_info_signal(index,tmp_stats);
            break;

        default:
            emit error_signal("Unknown command!");
            break;
        }
    }
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


