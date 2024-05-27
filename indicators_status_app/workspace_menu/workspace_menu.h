#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QHash>
#include <QPair>

//  Subwidgets
#include "subwidget_menu.h"
#include "exchange_status_widget.h"

class workspace_menu : public QWidget
{
    Q_OBJECT
private:

    uint32_t total_indicators_count;

    QHash<uint32_t,QPointer<subwidget_menu>>subwidgets;

    QPointer<QGridLayout>main_layout;
    QPointer<QPushButton> back_button;
    QPointer<QLabel> network_info_label;

    QPointer<exchange_status_widget> network_status_wgt;

private slots:

    void back_button_slot();
    void apply_power_subwidget_slot(uint32_t index,bool choise);

public slots:

    void get_indicator_info_slot(QVector<uint32_t> data);
    void update_status_network_slot();

signals:

    void back_signal();
    void apply_power_subwidget_signal(uint32_t,bool);

public:
    workspace_menu(QWidget * parrent = 0);
};
