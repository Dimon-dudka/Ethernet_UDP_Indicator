#include "indicators_data.h"

indicators_data::indicators_data(QObject * parrent) : QObject(parrent) {
    indicators_count = 10;
    indicators_active_count = 0;
    current_getting_index = 0;

    for(uint32_t i = 0;i<indicators_count;++i){
        indicators_work_map[i]=true;

        indicators_active_count+=1;
        sOneIndicatorStats tmp_status{i,0,0,0,0,0};

        indicators_info.push_back(std::move(tmp_status));
    }
}

void indicators_data::get_indicators_count_slot(){
    current_getting_index = 0;
    //emit return_indicators_count_signal(indicators_active_count);
    emit return_indicators_count_signal(indicators_count);
}

void indicators_data::change_settings_slot(QVector<uint32_t>new_data){

    //  0       1           2       3   4       5    6  7
    // Index; Available; Serial; Type; Power; Color; I; Error
    indicators_work_map[new_data[0]]=(bool)new_data[1];

    indicators_active_count=0;
    for(uint32_t i = 0;i<indicators_count;++i){
        if(indicators_work_map[i])indicators_active_count+=1;
    }

    indicators_info[new_data[0]].SerialNum = new_data[2];
    indicators_info[new_data[0]].Type = new_data[3];
    indicators_info[new_data[0]].Power = new_data[4];
    indicators_info[new_data[0]].Color = new_data[5];
    indicators_info[new_data[0]].Current_mA = new_data[6];
    indicators_info[new_data[0]].ErrorCode = new_data[7];

    emit update_ui(new_data);
}

void indicators_data::get_indicator_info_slot(uint32_t index){

    if(!indicators_work_map[index])indicators_info[index].ErrorCode = 1;    //  error not avaible
    emit return_indicator_info_signal(index,indicators_info[index]);
}

void indicators_data::switch_indicator_mode(uint32_t index,bool flag){
    indicators_info[index].Power = (uint32_t)flag;

    emit update_ui({index, indicators_work_map[index],indicators_info[index].SerialNum,
        indicators_info[index].Type,indicators_info[index].Power,indicators_info[index].Color,
        indicators_info[index].Current_mA,indicators_info[index].ErrorCode});
}
