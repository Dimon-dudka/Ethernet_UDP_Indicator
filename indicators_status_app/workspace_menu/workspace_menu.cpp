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
        }
    }

    main_layout->addWidget(back_button,i,0);

    setLayout(main_layout);
}

void workspace_menu::back_button_slot(){
    emit back_signal();
}
