#include "indicators_data.h"

indicators_data::indicators_data(QObject * parrent) : QObject(parrent) {
    indicators_count = 10;

    for(quint16 i = 0;i<indicators_count;++i){
        indicators_work_map[i]=true;

        sOneIndicatorStats tmp_status{i,0,0,0,0,0};

        indicators_info.push_back(std::move(tmp_status));
    }
}

void indicators_data::change_settings_slot(QVector<quint16>new_data){

    //  0       1           2       3   4       5    6  7
    // Index; Available; Serial; Type; Power; Color; I; Error
    indicators_work_map[new_data[0]]=(bool)new_data[1];

    indicators_info[new_data[0]].SerialNum = new_data[2];
    indicators_info[new_data[0]].Type = new_data[3];
    indicators_info[new_data[0]].Power = new_data[4];
    indicators_info[new_data[0]].Color = new_data[5];
    indicators_info[new_data[0]].Current_mA = new_data[6];
    indicators_info[new_data[0]].ErrorCode = new_data[7];

    emit update_ui(new_data);
}
