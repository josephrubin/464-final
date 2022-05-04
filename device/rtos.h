//
// Created by Joseph Rubin on 4/24/22.
//

#ifndef DEVICE_RTOS_H
#define DEVICE_RTOS_H

#include <utility>
#include <vector>

class rtos {
private:
    std::vector<int> periods;
public:
    /** Create an rtos with the given task periods in milliseconds. */
    explicit rtos(std::vector<int> in_periods): periods(std::move(in_periods)) {};
    /** Run the rtos for the specified number of hyperperiods. */
    void start(int periodsOfTaskOne);
};


#endif //DEVICE_RTOS_H
