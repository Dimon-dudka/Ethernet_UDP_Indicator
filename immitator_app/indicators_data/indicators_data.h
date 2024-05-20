#pragma once

#include <QObject>
#include <QVector>
#include <QHash>

#include "Basic_Types.h"

class indicators_data : public QObject
{
    Q_OBJECT
private:
    uint32_t indicators_count,indicators_active_count,current_getting_index;

    QHash<uint32_t,bool> indicators_work_map;
    QVector<sOneIndicatorStats> indicators_info;

public slots:

    void change_settings_slot(QVector<uint32_t>new_data);

    void get_indicators_count_slot();
    void get_indicator_info_slot(uint32_t index);
    void switch_indicator_mode(uint32_t index,bool flag);

signals:

    void update_ui(QVector<uint32_t>);

    void return_indicators_count_signal(uint32_t);
    void return_indicator_info_signal(uint32_t,sOneIndicatorStats);

public:

    indicators_data(QObject * parrent = 0);
};
