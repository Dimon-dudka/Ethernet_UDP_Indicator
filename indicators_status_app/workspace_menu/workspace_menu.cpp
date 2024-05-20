#include "workspace_menu.h"

workspace_menu::workspace_menu(QWidget * parrent):QWidget(parrent) {

    back_button = new QPushButton("Back");
    connect(back_button,SIGNAL(clicked()),this,SLOT(back_button_slot()));

    main_layout = new QGridLayout;

    total_indicators_count = 10;

    uint32_t index{0},i{0};
    for(;i<2;++i){
        for(uint32_t j = 0;j<5;++j,++index){
            QPointer<subwidget_menu> tmp_widget = new subwidget_menu(0,index);
            subwidgets[index]=tmp_widget;
            main_layout->addWidget(tmp_widget,i,j);
            connect(tmp_widget,SIGNAL(update_power_mode_signal(uint32_t,bool))
                    ,this,SLOT(apply_power_subwidget_slot(uint32_t,bool)));
        }
    }

    main_layout->addWidget(back_button,i,0);

    network_status_wgt = new exchange_status_widget;
    main_layout->addWidget(network_status_wgt,i,4);

    setLayout(main_layout);
}

void workspace_menu::update_status_network_slot(){
    network_status_wgt->set_exchange_slot(true);
}
void workspace_menu::back_button_slot(){
    emit back_signal();
}

void workspace_menu::get_indicator_info_slot(QVector<uint32_t> data){
    if (data[6] == 1) {
        subwidgets[data[0]]->hide();
    } else {
        subwidgets[data[0]]->show();
    }

    int index = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 5; ++j) {
            while (index < total_indicators_count && !subwidgets[index]->isVisible()) {
                ++index;
            }
            if (index < total_indicators_count) {
                main_layout->addWidget(subwidgets[index], i, j);
                ++index;
            }
        }
    }

    main_layout->addWidget(back_button, 2, 0);
    main_layout->addWidget(network_status_wgt, 2, 4);

    subwidgets[data[0]]->update_data_slot(data);
}

void workspace_menu::apply_power_subwidget_slot(uint32_t index,bool choise){
    emit apply_power_subwidget_signal(index,choise);
}
