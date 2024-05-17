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


public:

    quint16 indicators_count;

    indicators_data(QObject * parrent = 0);
};
