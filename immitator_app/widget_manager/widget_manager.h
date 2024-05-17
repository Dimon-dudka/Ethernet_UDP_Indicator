#pragma once

#include <QApplication>
#include <QStackedWidget>
#include <QPointer>
#include <QUdpSocket>

#include "workspace_menu.h"
#include "indicators_data.h"
#include "network_work.h"

class widget_manager : public QStackedWidget
{
    Q_OBJECT

private:

    QPointer<network_work> network_API;
    QPointer<workspace_menu> workspace_menu_wgt;
    QPointer<indicators_data> indicators_API;


public:
    widget_manager(QStackedWidget *parrent = 0);
};
