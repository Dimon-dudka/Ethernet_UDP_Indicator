#pragma once

#include <QObject>
#include <QVector>
#include <QHash>

#include "Basic_Types.h"

class indicators_local_data : public QObject
{
    Q_OBJECT
private:

    uint32_t indicators_count;
    //QVector<sOneIndicatorStats>indicators_data;
    QHash<uint32_t,sOneIndicatorStats>indicators_data;

public slots:

    void set_indicators_count_slot(uint32_t count);
    void set_indicator_info_slot(uint32_t index,sOneIndicatorStats stats);

signals:

    void get_all_info_signal(uint32_t);

public:
    indicators_local_data(QObject * parrent = 0);
};
