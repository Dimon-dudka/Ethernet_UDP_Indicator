#include "new_ip_menu.h"

new_ip_menu::new_ip_menu(QWidget *parrent) : QWidget(parrent) {

    info_label = new QLabel("Ente new device IP and port");

    back_button = new QPushButton("Back");
    connect_button = new QPushButton("Connect");

    //  Buttons setup
    connect(back_button,SIGNAL(clicked()),this,SLOT(send_back_slot()));
    connect(connect_button,SIGNAL(clicked()),this,SLOT(send_new_ip_port_info_slot()));

    ip_line_edit = new QLineEdit("Enter new IP");
    port_line_edit = new QLineEdit("Enter new port");

    buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(back_button);
    buttons_layout->addWidget(connect_button);

    main_layout = new QVBoxLayout;
    main_layout->addWidget(info_label);
    main_layout->addWidget(ip_line_edit);
    main_layout->addWidget(port_line_edit);
    main_layout->addLayout(buttons_layout);

    setLayout(main_layout);
}

void new_ip_menu::send_back_slot(){
    emit back_signal();
}

void new_ip_menu::send_new_ip_port_info_slot(){
    QString new_ip{ip_line_edit->text()}, new_port{port_line_edit->text()};

    QHostAddress tmp_ip;
    if(!tmp_ip.setAddress(new_ip)){
        QMessageBox::warning(0,"Warning","Incorrect IP adress!", QMessageBox::Ok);
        return;
    }

    bool port_chek;
    quintptr tmp_port{new_port.toUShort(&port_chek)};
    if(!port_chek){
        QMessageBox::warning(0,"Warning","Incorrect port number!", QMessageBox::Ok);
        return;
    }

    emit new_ip_port_info_signal(tmp_ip,tmp_port);
}
