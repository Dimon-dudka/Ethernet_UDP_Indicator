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

    setLayout(main_layout);
}

void workspace_menu::back_button_slot(){
    emit back_signal();
}

void workspace_menu::get_indicator_info_slot(QVector<uint32_t> data){
    subwidgets[data[0]]->update_data_slot(data);
}

void workspace_menu::apply_power_subwidget_slot(uint32_t index,bool choise){
    emit apply_power_subwidget_signal(index,choise);
}
