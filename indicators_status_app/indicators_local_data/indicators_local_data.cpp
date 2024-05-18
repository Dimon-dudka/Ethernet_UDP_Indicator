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
}
