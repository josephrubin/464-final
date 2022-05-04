//
// Created by Joseph Rubin on 5/2/22.
//

#ifndef DEVICE_DELAY_TASK_H
#define DEVICE_DELAY_TASK_H

#include <chrono>
#include <thread>
#include <utility>

/** Run a task after the specified delay. */
class delay_task {
private:
    int ms;
    std::function<void()> task;
    void run_after();
public:
    std::thread task_thread;
    delay_task(int ms, std::function<void()> f): ms(ms), task(std::move(f)), task_thread([this] { run_after(); }) {};
};


#endif //DEVICE_DELAY_TASK_H
