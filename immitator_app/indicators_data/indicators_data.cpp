#include "indicators_data.h"

indicators_data::indicators_data(QObject * parrent) : QObject(parrent) {
    indicators_count = 10;

    for(quint16 i = 0;i<indicators_count;++i){
        indicators_work_map[i]=true;

        sOneIndicatorStats tmp_status{i,0,0,0,0,0};

        indicators_info.push_back(std::move(tmp_status));
    }
}
