#pragma once

#include <QWidget>
#include <QHostAddress>
#include <QPointer>
#include <QLabel>
#include <QBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>

class new_ip_menu : public QWidget
{
    Q_OBJECT
private:

    QPointer<QVBoxLayout> main_layout;
    QPointer<QHBoxLayout> buttons_layout;

    QPointer<QPushButton> back_button,connect_button;
    QPointer<QLineEdit> ip_line_edit, port_line_edit;
    QPointer<QLabel> info_label;

private slots:

    void send_back_slot();
    void send_new_ip_port_info_slot();

signals:

    void new_ip_port_info_signal(QHostAddress,quintptr);
    void back_signal();

public:
    new_ip_menu(QWidget *parrent = 0);
};
