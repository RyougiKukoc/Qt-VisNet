#pragma once

#include "layouter_global.h"
#include "data_manager.h"

class LAYOUTER_EXPORT layouter {
private:
    std::vector<double> forcex, forcey;

public:
    void randomCor(data_manager& manager);
    void updateReplusion(data_manager& manager);
    void updateSpring(data_manager& manager);
    void update(data_manager& manager);
    void calc(data_manager& manager, int repeats);
};
