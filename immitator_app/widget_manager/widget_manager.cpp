#include "widget_manager.h"

widget_manager::widget_manager(QStackedWidget *parrent):QStackedWidget(parrent) {

    network_API = new network_work;
    indicators_API = new indicators_data;

    workspace_menu_wgt = new workspace_menu;

    addWidget(workspace_menu_wgt);

    setCurrentWidget(workspace_menu_wgt);


    //Workspace connections
    connect(workspace_menu_wgt,SIGNAL(exit_signal()),this,SLOT(close()));
    connect(workspace_menu_wgt,SIGNAL(send_forward_data_signal(QVector<quint16>)),
            indicators_API,SLOT(change_settings_slot(QVector<quint16>)));

    //  Indicators data connections
    connect(indicators_API,SIGNAL(update_ui(QVector<quint16>))
            ,workspace_menu_wgt,SLOT(update_widgets_info_slot(QVector<quint16>)));
}
