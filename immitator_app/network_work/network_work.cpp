#include "network_work.h"

network_work::network_work(QObject * parrent) : QObject(parrent) {
    controll_app_ip = QHostAddress::LocalHost;
    controll_app_port = 5001;
}
