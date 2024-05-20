#include "exchange_status_widget.h"

exchange_status_widget::exchange_status_widget(QWidget * parrent):QWidget(parrent) {
    setFixedSize(100, 100);
    cycle = 0;
    has_exchange = false;

    status_label = new QLabel;
    status_label->setAlignment(Qt::AlignCenter);
    status_label->setFixedSize( 10, 10 );
    status_label->setStyleSheet( "border-radius: 5px; background-color: grey;" );

    time_view = new QTimer;
    connect(time_view, SIGNAL(timeout()), this, SLOT(update_color_slot()));
    time_view->start(1000);

    main_layout = new QVBoxLayout;
    main_layout->addWidget(status_label,0,Qt::AlignCenter);

    setLayout(main_layout);
}

void exchange_status_widget::set_exchange_slot(bool exchange){
    has_exchange = exchange;
}

void exchange_status_widget::update_color_slot(){
    if (has_exchange)
    {
        status_label->setStyleSheet( "border-radius: 5px; background-color: green;" );
        has_exchange = false;
        cycle = 0;
    }
    else
    {
        cycle++;
        if (cycle >= 3)
        {
            status_label->setStyleSheet( "border-radius: 5px; background-color: grey;" );
        }
    }
    show();
}
