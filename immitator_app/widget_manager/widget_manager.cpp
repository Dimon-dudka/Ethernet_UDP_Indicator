#include "widget_manager.h"

widget_manager::widget_manager(QStackedWidget *parrent):QStackedWidget(parrent) {

    network_API = new network_work;
    indicators_API = new indicators_data;

    workspace_menu_wgt = new workspace_menu;

    addWidget(workspace_menu_wgt);

    setCurrentWidget(workspace_menu_wgt);


    //  Workspace connections
    connect(workspace_menu_wgt,SIGNAL(exit_signal()),this,SLOT(close()));
    connect(workspace_menu_wgt,SIGNAL(send_forward_data_signal(QVector<uint32_t>)),
            indicators_API,SLOT(change_settings_slot(QVector<uint32_t>)));

    //  Indicators data connections
    connect(indicators_API,SIGNAL(update_ui(QVector<uint32_t>))
            ,workspace_menu_wgt,SLOT(update_widgets_info_slot(QVector<uint32_t>)));

    //  Network connections
    connect(network_API,SIGNAL(error_message_signal(QString))
            ,workspace_menu_wgt,SLOT(error_message_slot(QString)));
    connect(network_API,SIGNAL(get_count_indicators_signal())
            ,indicators_API,SLOT(get_indicators_count_slot()));
    connect(network_API,SIGNAL(get_stat_indicator_signal(uint32_t))
            ,indicators_API,SLOT(get_indicator_info_slot(uint32_t)));
    connect(network_API,SIGNAL(set_indicator_active(uint32_t,bool))
            ,indicators_API,SLOT(switch_indicator_mode(uint32_t,bool)));

    //  Indicators connections
    connect(indicators_API,SIGNAL(return_indicators_count_signal(uint32_t))
            ,network_API,SLOT(send_count_indicators_slot(uint32_t)));
    connect(indicators_API,SIGNAL(return_indicator_info_signal(uint32_t,sOneIndicatorStats))
            ,network_API,SLOT(send_indicator_info_slot(uint32_t,sOneIndicatorStats)));
}
