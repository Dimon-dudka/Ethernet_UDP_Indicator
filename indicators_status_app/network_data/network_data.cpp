#include "network_data.h"

network_data::network_data(QObject *parrent):QObject(parrent) {

    change_device_ip_port();
}

void network_data::change_device_ip_port(QHostAddress new_ip, quintptr new_port){
    device_ip = new_ip;
    device_port = new_port;
}
