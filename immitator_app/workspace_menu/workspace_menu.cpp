#include "workspace_menu.h"

workspace_menu::workspace_menu(QWidget * parrent):QWidget(parrent) {

    main_layout= new QGridLayout;

    count_of_indicators_on_line = 5;

    int index{0},i{0};

    for(;i<2;++i){
        for(int j=0;j<5;++j,++index){
            QPointer<indicator_subwidget> tmp = new indicator_subwidget(this,index);

            connect(tmp,SIGNAL(error_message_signal(QString)),this,SLOT(error_message_slot(QString)));
            connect(tmp,SIGNAL(changes_signal(QVector<uint32_t>)),
                    this, SLOT(send_forward_data_slot(QVector<uint32_t>)));

            subwidgets.push_back(tmp);
            main_layout->addWidget(tmp,i,j);
        }
    }

    setLayout(main_layout);
}

void workspace_menu::update_widgets_info_slot(QVector<uint32_t>data){
    if(data[0]>=subwidgets.size())return;

    subwidgets[data[0]]->update_info_slot(data);
}

void workspace_menu::send_forward_data_slot(QVector<uint32_t>data){
    emit send_forward_data_signal(data);
}

void workspace_menu::error_message_slot(QString info){
    QMessageBox::warning(0,"Warning",info, QMessageBox::Ok);
}

void workspace_menu::update_widget_indicator_power_slot(uint32_t index,bool mode){
    subwidgets[index]->update_power_slot(mode);
}
