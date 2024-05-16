#pragma once

#include <QWidget>
#include <QPointer>
#include <QVBoxLayout>
#include <QPushButton>

class start_menu : public QWidget
{
    Q_OBJECT
private:

    QPointer<QPushButton> basic_ip_button,new_ip_button,exit_button;
    QPointer<QVBoxLayout> widget_layout;

private slots:

    void send_basic_ip_slot();
    void send_new_ip_slot();
    void send_exit_slot();

signals:

    void basic_ip_signal();
    void new_ip_signal();
    void exit_signal();

public:
    start_menu(QWidget *parrent = 0);
};
