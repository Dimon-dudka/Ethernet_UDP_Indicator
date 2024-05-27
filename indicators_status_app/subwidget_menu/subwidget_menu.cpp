#include "subwidget_menu.h"

subwidget_menu::subwidget_menu(QWidget * parrent,uint32_t new_index)
    :QWidget(parrent), index(new_index){

    color_choise[0]="Yellow";
    color_choise[1]="Green";
    color_choise[2]="Red";
    color_choise[3]="Reserve";

    serial_label = new QLabel("None");
    serial_label->setAlignment(Qt::AlignCenter);

    type_label =new QLabel("None");
    type_label->setAlignment(Qt::AlignCenter);

    power_label = new QLabel("None");
    power_label->setAlignment(Qt::AlignCenter);

    power_box = new QComboBox;
    QStringList tmp_lst;
    tmp_lst<<"Off"<<"On";
    power_box->addItems(tmp_lst);
    power_box->setCurrentIndex(0);
    connect(power_box,SIGNAL(currentIndexChanged(int)),this,SLOT(apply_slot()));

    color_label = new QLabel("None");
    color_label->setAlignment(Qt::AlignCenter);

    i_label = new QLabel("None");
    i_label->setAlignment(Qt::AlignCenter);

    error_label = new QLabel("None");
    error_label->setAlignment(Qt::AlignCenter);

    error_label->setStyleSheet(" QLabel { font-weight: bold; color : red; }");

    main_layout = new QVBoxLayout;

    main_layout->addWidget(serial_label);
    main_layout->addWidget(power_label);
    main_layout->addWidget(type_label);
    main_layout->addWidget(color_label);
    main_layout->addWidget(i_label);
    main_layout->addWidget(error_label);
    main_layout->addWidget(power_box);

    setLayout(main_layout);
}

void subwidget_menu::update_data_slot(QVector<uint32_t>new_data){

    if(new_data[0]!=index)return;
    //  0       1       2       3    4    5    6
    // Index; Serial; Type; Power; Color; I; Error
    serial_label->setText("Serial: "+QString::number(new_data[1]));

    if(new_data[2]==0)type_label->setText("Type: Lamp");
    else type_label->setText("Type: LED");

    power_label->setText(new_data[3]?"Power: On":"Power: Off");

    color_label->setText("Color: "+color_choise[new_data[4]]);

    i_label->setText("I = "+QString::number(new_data[5])+" mA");

    if(new_data[6]==0){
        power_box->setEnabled(true);
        error_label->setText("");
    }

    if((new_data[5]>1000&&new_data[3])||(new_data[5]>0&&!new_data[3])){
        error_label->setText("Faulty");
    }
}

void subwidget_menu::apply_slot(){
    emit update_power_mode_signal(index,(bool)power_box->currentIndex());
}
