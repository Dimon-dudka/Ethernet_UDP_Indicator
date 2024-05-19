#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QHash>

#include "subwidget_menu.h"

class workspace_menu : public QWidget
{
    Q_OBJECT
private:

    uint32_t total_indicators_count;

    QHash<uint32_t,QPointer<subwidget_menu>>subwidgets;

    QPointer<QGridLayout>main_layout;
    QPointer<QPushButton> back_button;

private slots:

    void back_button_slot();

public slots:

    void get_indicator_info_slot(QVector<uint32_t> data);

signals:

    void back_signal();

public:
    workspace_menu(QWidget * parrent = 0);
};
