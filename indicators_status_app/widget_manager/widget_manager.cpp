#include "widget_manager.h"

widget_manager::widget_manager(QStackedWidget *parrent):QStackedWidget(parrent) {

    network_API = new network_data;
    indicators_data = new indicators_local_data;

    start_menu_wgt = new start_menu;
    new_ip_menu_wgt = new new_ip_menu;
    workspace_menu_wgt = new workspace_menu;

    addWidget(start_menu_wgt);
    addWidget(new_ip_menu_wgt);
    addWidget(workspace_menu_wgt);

    setCurrentWidget(start_menu_wgt);

    //  network_data connections
    connect(network_API,SIGNAL(error_signal(QString)),this,SLOT(open_error_box_slot(QString)));
    connect(network_API,SIGNAL(new_indicators_count_signal(uint32_t))
            ,indicators_data,SLOT(set_indicators_count_slot(uint32_t)));
    connect(network_API,SIGNAL(indicator_info_signal(uint32_t,sOneIndicatorStats))
            ,indicators_data,SLOT(set_indicator_info_slot(uint32_t,sOneIndicatorStats)));

    //  indicators_data connections
    connect(indicators_data,SIGNAL(get_all_info_signal(uint32_t))
            ,network_API,SLOT(get_all_indicators_data_slot(uint32_t)));
    connect(indicators_data,SIGNAL(return_indicator_info_signal(QVector<uint32_t>))
            ,workspace_menu_wgt,SLOT(get_indicator_info_slot(QVector<uint32_t>)));

    //  start_menu_wgt connections
    connect(start_menu_wgt,SIGNAL(exit_signal()),this,SLOT(close()));
    connect(start_menu_wgt,SIGNAL(new_ip_signal()),this,SLOT(set_current_new_ip_menu()));
    //connect(start_menu_wgt,SIGNAL(basic_ip_signal())
      //      ,network_API,SLOT(change_device_ip_port()));

    connect(start_menu_wgt,SIGNAL(basic_ip_signal()),network_API,SLOT(initial_indicators_slot()));
    connect(start_menu_wgt,SIGNAL(basic_ip_signal()),this,SLOT(set_current_workspace_menu()));

    //  new_ip_menu_wgt connections
    connect(new_ip_menu_wgt,SIGNAL(back_signal()),this,SLOT(set_current_start_menu()));
    connect(new_ip_menu_wgt,SIGNAL(new_ip_port_info_signal(QHostAddress,quintptr)),
            network_API,SLOT(change_device_ip_port(QHostAddress,quintptr)));
    connect(new_ip_menu_wgt,SIGNAL(new_ip_port_info_signal(QHostAddress,quintptr))
            ,network_API,SLOT(initial_indicators_slot()));

    //  workspace_menu connections
    connect(workspace_menu_wgt,SIGNAL(back_signal()),this,SLOT(set_current_start_menu()));
    connect(workspace_menu_wgt,SIGNAL(back_signal()),network_API,SLOT(stop_timer_slot()));
    connect(workspace_menu_wgt,SIGNAL(apply_power_subwidget_signal(uint32_t,bool))
            ,network_API,SLOT(turn_indicator_power(uint32_t,bool)));
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

void widget_manager::set_current_workspace_menu(){
    setCurrentWidget(workspace_menu_wgt);
}
