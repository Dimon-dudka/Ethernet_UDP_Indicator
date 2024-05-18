#pragma once

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QBoxLayout>
#include <QVector>
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
    void send_forward_data_slot(QVector<uint32_t>data);

public slots:

    void error_message_slot(QString info);
    void update_widgets_info_slot(QVector<uint32_t>data);

signals:

    void exit_signal();
    void send_forward_data_signal(QVector<uint32_t>);

public:
    workspace_menu(QWidget * parrent = 0);
};
