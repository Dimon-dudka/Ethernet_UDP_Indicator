#pragma once

#include <QApplication>
#include <QStackedWidget>
#include <QPointer>
#include <QUdpSocket>

//  Network data tool
#include "network_data.h"

//  Indicators data
#include "indicators_local_data.h"

//  Widgets
#include "start_menu.h"
#include "new_ip_menu.h"
#include "workspace_menu.h"

class widget_manager : public QStackedWidget
{
    Q_OBJECT

private:

    QPointer<network_data> network_API;

    QPointer<indicators_local_data> indicators_data;

    QPointer<start_menu> start_menu_wgt;
    QPointer<new_ip_menu> new_ip_menu_wgt;
    QPointer<workspace_menu> workspace_menu_wgt;

private slots:

    void set_current_start_menu();
    void set_current_new_ip_menu();
    void set_current_workspace_menu();

    void open_error_box_slot(const QString& info);

public:
    widget_manager(QStackedWidget *parrent = 0);
};
