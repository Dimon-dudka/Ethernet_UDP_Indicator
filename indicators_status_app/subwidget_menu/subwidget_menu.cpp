#include "subwidget_menu.h"

subwidget_menu::subwidget_menu(QWidget * parrent,uint32_t new_index)
    :QWidget(parrent), index(new_index){

    serial_label = new QLabel("None");
    serial_label->setAlignment(Qt::AlignCenter);

    type_label =new QLabel("None");
    type_label->setAlignment(Qt::AlignCenter);

    power_box = new QComboBox;
    QStringList tmp_lst;
    tmp_lst<<"On"<<"Off";
    power_box->addItems(tmp_lst);
    power_box->setCurrentIndex(0);

    color_label = new QLabel("None");
    color_label->setAlignment(Qt::AlignCenter);

    i_label = new QLabel("None");
    i_label->setAlignment(Qt::AlignCenter);

    error_label = new QLabel("None");
    error_label->setAlignment(Qt::AlignCenter);

    apply_button = new QPushButton("Apply");
    connect(apply_button,SIGNAL(clicked()),this,SLOT(apply_slot()));

    main_layout = new QVBoxLayout;

    main_layout->addWidget(serial_label);
    main_layout->addWidget(type_label);
    main_layout->addWidget(power_box);
    main_layout->addWidget(color_label);
    main_layout->addWidget(i_label);
    main_layout->addWidget(error_label);
    main_layout->addWidget(apply_button);

    setLayout(main_layout);
}

void subwidget_menu::update_data_slot(QVector<uint32_t>new_data){
    //  0       1       2       3    4    5    6
    // Index; Serial; Type; Power; Color; I; Error
    index = new_data[0];
    serial_label->setText(QString::number(new_data[1]));
    type_label->setText(QString::number(new_data[2]));
    power_box->setCurrentIndex(new_data[3]);
    color_label->setText(QString::number(new_data[4]));
    i_label->setText(QString::number(new_data[5]));
    error_label->setText(QString::number(new_data[6]));
}

void subwidget_menu::apply_slot(){
    emit update_power_mode_signal(index,power_box->currentIndex());
}
