#pragma once

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QBoxLayout>
#include <QMessageBox>

#include "indicator_subwidget.h"

class workspace_menu : public QWidget
{
    Q_OBJECT
private:

    quint16 count_of_indicators_on_line;

    QVector<QPointer<indicator_subwidget>> subwidgets;
    QVector<QPointer<QHBoxLayout>>indicators_layouts;

    QPointer<QPushButton> exit_button;

    QPointer<QGridLayout>main_layout;

private slots:

    void exit_slot();
    void error_message_slot(QString info);
    void send_forward_data_slot(quint16 index, quint16 vailable, quint16 serial,quint16 type,
                                quint16 power,quint16 color,quint16 i,quint16 error);

public slots:



signals:

    void exit_signal();
    void send_forward_data_signal(quint16, quint16, quint16,quint16,quint16,quint16,quint16,quint16);

public:
    workspace_menu(QWidget * parrent = 0);
};
