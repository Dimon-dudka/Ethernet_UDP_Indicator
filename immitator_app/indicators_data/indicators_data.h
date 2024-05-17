#pragma once

#include <QObject>
#include <QVector>
#include <QHash>

#include "Basic_Types.h"

class indicators_data : public QObject
{
    Q_OBJECT
private:

    QHash<quint16,bool> indicators_work_map;
    QVector<sOneIndicatorStats> indicators_info;

public slots:

    void change_settings_slot(QVector<quint16>new_data);

signals:

    void update_ui(QVector<quint16>);

public:

    quint16 indicators_count;

    indicators_data(QObject * parrent = 0);
};
