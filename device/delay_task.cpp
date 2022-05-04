//
// Created by Joseph Rubin on 5/2/22.
//

#include "delay_task.h"

#include <chrono>
#include <thread>

void delay_task::run_after() {
    std::chrono::milliseconds sleep_time(this->ms);
    std::this_thread::sleep_for(sleep_time);
    this->task();
}
