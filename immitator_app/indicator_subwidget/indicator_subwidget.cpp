#include "indicator_subwidget.h"

indicator_subwidget::indicator_subwidget(QWidget *parrent,uint32_t index)
    :QWidget(parrent),indicator_index(index) {

    number_of_indicator_label = new QLabel(QString::number(index));
    number_of_indicator_label->setAlignment(Qt::AlignCenter);

    is_available_box = new QComboBox;
    color_box = new QComboBox;
    power_box = new QComboBox;
    type_box = new QComboBox;

    QStringList tmp_box_values;

    tmp_box_values<<"Unavailable"<<"Available";
    is_available_box->addItems(tmp_box_values);
    is_available_box->setCurrentIndex(1);
    tmp_box_values.clear();

    tmp_box_values<<"Yellow"<<"Green"<<"Red"<<"Reserve";
    color_box->addItems(tmp_box_values);
    color_box->setCurrentIndex(0);
    tmp_box_values.clear();

    tmp_box_values<<"Off"<<"On";
    power_box->addItems(tmp_box_values);
    power_box->setCurrentIndex(0);
    tmp_box_values.clear();

    tmp_box_values<<"Lamp"<<"LED";
    type_box->addItems(tmp_box_values);
    type_box->setCurrentIndex(0);
    tmp_box_values.clear();

    serial_num_line_edit = new QLineEdit("Serial num");
    i_line_edit = new QLineEdit("I mA");
    error_line_edit = new QLineEdit("Error num");

    apply_button = new QPushButton("Apply");
    connect(apply_button,SIGNAL(clicked()),this,SLOT(apply_slot()));

    main_layout = new QVBoxLayout;

    //  Backend params
    main_layout->addWidget(number_of_indicator_label);
    main_layout->addWidget(is_available_box);

    //  Structure params
    main_layout->addWidget(serial_num_line_edit);
    main_layout->addWidget(type_box);
    main_layout->addWidget(power_box);
    main_layout->addWidget(color_box);
    main_layout->addWidget(i_line_edit);
    main_layout->addWidget(error_line_edit);

    //  Button
    main_layout->addWidget(apply_button);

    setLayout(main_layout);
}

void indicator_subwidget::update_info_slot(QVector<uint32_t>new_data){
    if(new_data[0]!=indicator_index)return;

    //  0       1           2       3   4       5    6  7
    // Index; Available; Serial; Type; Power; Color; I; Error
    is_available_box->setCurrentIndex(new_data[1]);
    serial_num_line_edit->setText(QString::number(new_data[2]));
    type_box->setCurrentIndex(new_data[3]);
    power_box->setCurrentIndex(new_data[4]);
    color_box->setCurrentIndex(new_data[5]);
    i_line_edit->setText(QString::number(new_data[6]));
    error_line_edit->setText(QString::number(new_data[7]));
}

void indicator_subwidget::apply_slot(){
    bool chek;

    //  serial_num check
    uint32_t tmp_serial{serial_num_line_edit->text().toUShort(&chek)};
    if(!chek){
        emit error_message_signal("Serial is not valid number!");
        return;
    }

    //   I num check
    uint32_t tmp_i = i_line_edit->text().toUShort(&chek);
    if(!chek){
        emit error_message_signal("I is not valid number!");
        return;
    }

    //   Error num check
    uint32_t tmp_error = error_line_edit->text().toUShort(&chek);
    if(!chek){
        emit error_message_signal("Error is not valid number!");
        return;
    }

    emit changes_signal({indicator_index,(uint32_t)is_available_box->currentIndex(),tmp_serial
        ,(uint32_t)type_box->currentIndex(),(uint32_t)power_box->currentIndex()
        ,(uint32_t)color_box->currentIndex(),tmp_i,tmp_error});
}

void indicator_subwidget::update_power_slot(bool mode){
    power_box->setCurrentIndex(mode);
}
