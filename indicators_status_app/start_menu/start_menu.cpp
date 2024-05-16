#include "start_menu.h"

start_menu::start_menu(QWidget *parrent):QWidget(parrent) {

    basic_ip_button = new QPushButton("Basic IP");
    new_ip_button = new QPushButton("New IP");
    exit_button = new QPushButton("Exit");

    widget_layout = new QVBoxLayout;
    widget_layout->addWidget(basic_ip_button);
    widget_layout->addWidget(new_ip_button);
    widget_layout->addWidget(exit_button);

    setLayout(widget_layout);

    connect(basic_ip_button,SIGNAL(clicked()),this,SLOT(send_basic_ip_slot()));
    connect(new_ip_button,SIGNAL(clicked()),this,SLOT(send_new_ip_slot()));
    connect(exit_button,SIGNAL(clicked()),this,SLOT(send_exit_slot()));
}

void start_menu::send_basic_ip_slot(){
    emit basic_ip_signal();
}

void start_menu::send_new_ip_slot(){
    emit new_ip_signal();
}

void start_menu::send_exit_slot(){
    emit exit_signal();
}
