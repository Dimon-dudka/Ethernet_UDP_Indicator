#pragma once

#include <QApplication>
#include <QStackedWidget>
#include <QPointer>
#include <QUdpSocket>

#include "Basic_Types.h"

//  Network data tool
#include "network_data.h"

//  Widgets
#include "start_menu.h"
#include "new_ip_menu.h"

class widget_manager : public QStackedWidget
{
    Q_OBJECT

private:

    QPointer<network_data> network_API;

    QPointer<start_menu> start_menu_wgt;
    QPointer<new_ip_menu> new_ip_menu_wgt;

private slots:

    void set_current_start_menu();
    void set_current_new_ip_menu();

public:
    widget_manager(QStackedWidget *parrent = 0);
    void tmp(){qDebug()<<"Ok";}
};
