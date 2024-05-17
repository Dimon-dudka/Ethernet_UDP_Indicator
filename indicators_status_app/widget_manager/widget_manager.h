#pragma once

#include <QApplication>
#include <QStackedWidget>
#include <QPointer>
#include <QUdpSocket>

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

    void open_error_box_slot(const QString& info);

public:
    widget_manager(QStackedWidget *parrent = 0);
};
