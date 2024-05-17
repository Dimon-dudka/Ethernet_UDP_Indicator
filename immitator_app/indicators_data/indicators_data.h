#pragma once

#include <QObject>
#include <QVector>
#include <QHash>

#include "Basic_Types.h"

class indicators_data : public QObject
{
    Q_OBJECT
private:
    quint16 indicators_count,indicators_active_count;

    QHash<quint16,bool> indicators_work_map;
    QVector<sOneIndicatorStats> indicators_info;

public slots:

    void change_settings_slot(QVector<quint16>new_data);

    void get_indicators_count_slot();

signals:

    void update_ui(QVector<quint16>);

    void return_indicators_count_signal(uint32_t);

public:

    indicators_data(QObject * parrent = 0);
};
