#include "widget_manager.h"

widget_manager::widget_manager(QStackedWidget *parrent):QStackedWidget(parrent) {

    network_API = new network_work;
    indicators_API = new indicators_data;

    workspace_menu_wgt = new workspace_menu;

    addWidget(workspace_menu_wgt);

    setCurrentWidget(workspace_menu_wgt);


    //Workspace connections
    connect(workspace_menu_wgt,SIGNAL(exit_signal()),this,SLOT(close()));
}
