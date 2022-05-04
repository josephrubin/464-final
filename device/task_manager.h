//
// Created by Joseph Rubin on 5/2/22.
//

#ifndef DEVICE_TASK_MANAGER_H
#define DEVICE_TASK_MANAGER_H

#include <chrono>
#include <vector>


class task_manager {
private:
    int id;
    int period_count;
    std::vector<int> *results;
public:
    int period_ms;
    /** Run tasks of period period_ms until after the period_count periods have ellapsed. */
    task_manager(int id, int period_ms, int period_count, std::vector<int> *results) : id(id), period_ms(period_ms), period_count(period_count), results(results) {}
    /** Repeatedly launch tasks at their specified time and wait for them to finish, recording results. */
    void start();
};


#endif //DEVICE_TASK_MANAGER_H
