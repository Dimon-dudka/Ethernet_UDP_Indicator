#include "widget_manager.h"

widget_manager::widget_manager(QStackedWidget *parrent):QStackedWidget(parrent) {

    //resize(400,400);

    network_API = new network_data;

    start_menu_wgt = new start_menu;
    new_ip_menu_wgt = new new_ip_menu;

    addWidget(start_menu_wgt);
    addWidget(new_ip_menu_wgt);

    setCurrentWidget(start_menu_wgt);

    //  network_data connections
    connect(network_API,SIGNAL(error_signal(QString)),this,SLOT(open_error_box_slot(QString)));

    //  start_menu_wgt connections
    connect(start_menu_wgt,SIGNAL(exit_signal()),this,SLOT(close()));
    connect(start_menu_wgt,SIGNAL(new_ip_signal()),this,SLOT(set_current_new_ip_menu()));
    connect(start_menu_wgt,SIGNAL(basic_ip_signal())
            ,network_API,SLOT(change_device_ip_port()));
    connect(start_menu_wgt,SIGNAL(basic_ip_signal()),network_API,SLOT(initial_indicators()));

    //  new_ip_menu_wgt connections
    connect(new_ip_menu_wgt,SIGNAL(back_signal()),this,SLOT(set_current_start_menu()));
    connect(new_ip_menu_wgt,SIGNAL(new_ip_port_info_signal(QHostAddress,quintptr)),
            network_API,SLOT(change_device_ip_port(QHostAddress,quintptr)));
    connect(new_ip_menu_wgt,SIGNAL(new_ip_port_info_signal(QHostAddress,quintptr))
            ,network_API,SLOT(initial_indicators()));
}

void widget_manager::open_error_box_slot(const QString& info){
    QMessageBox::warning(0,"Warning",std::move(info), QMessageBox::Ok);
}

void widget_manager::set_current_start_menu(){
    setCurrentWidget(start_menu_wgt);
}

void widget_manager::set_current_new_ip_menu(){
    setCurrentWidget(new_ip_menu_wgt);
}
