#include "widget_manager.h"

widget_manager::widget_manager(QStackedWidget *parrent):QStackedWidget(parrent) {

    network_API = new network_work;
    indicators_API = new indicators_data;

    workspace_menu_wgt = new workspace_menu;

    addWidget(workspace_menu_wgt);

    setCurrentWidget(workspace_menu_wgt);


    //  Workspace connections
    connect(workspace_menu_wgt,SIGNAL(exit_signal()),this,SLOT(close()));
    connect(workspace_menu_wgt,SIGNAL(send_forward_data_signal(QVector<quint16>)),
            indicators_API,SLOT(change_settings_slot(QVector<quint16>)));

    //  Indicators data connections
    connect(indicators_API,SIGNAL(update_ui(QVector<quint16>))
            ,workspace_menu_wgt,SLOT(update_widgets_info_slot(QVector<quint16>)));

    //  Network connections
    connect(network_API,SIGNAL(error_message_signal(QString))
            ,workspace_menu_wgt,SLOT(error_message_slot(QString)));
    connect(network_API,SIGNAL(get_count_indicators_signal())
            ,indicators_API,SLOT(get_indicators_count_slot()));

    //  Indicators connections
    connect(indicators_API,SIGNAL(return_indicators_count_signal(uint32_t))
            ,network_API,SLOT(send_count_indicators_slot(uint32_t)));
}
