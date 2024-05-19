#include "indicators_local_data.h"

indicators_local_data::indicators_local_data(QObject * parrent):QObject(parrent) {
    indicators_count = 0;
}

void indicators_local_data::set_indicators_count_slot(uint32_t count){
    indicators_count = count;
    emit get_all_info_signal(indicators_count);
}

void indicators_local_data::set_indicator_info_slot(uint32_t index,sOneIndicatorStats stats){
    indicators_data[index]=stats;
    //  0       1       2       3    4     5    6
    // Index; Serial; Type; Power; Color; I; Error
    emit return_indicator_info_signal({index,stats.SerialNum,stats.Type,stats.Power
        ,stats.Color,stats.Current_mA,stats.ErrorCode});
}
