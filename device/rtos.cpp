//
// Created by Joseph Rubin on 4/24/22.
//

#include "rtos.h"

#include "delay_task.h"
#include "task_manager.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <vector>

#include <sys/wait.h>
#include <unistd.h>

void print_int_vec(std::vector<int> &v) {
    std::cout << "[" << v.size() << "] results: ";
    for (auto r : v) {
        std::cout << r << " ";
    }
    std::cout << std::endl;
}

void rtos::start(int periodsOfTaskOne) {
    const auto totalTimeOfTaskOne = this->periods.at(0) * periodsOfTaskOne;

    std::cout << "Running for " << totalTimeOfTaskOne << "ms." << std::endl;

    // We'll start by launching all task manager threads.
    auto task_manager_threads = std::vector<std::thread>();
    auto task_manager_results = std::vector<std::vector<int>>{};
    for (auto &period : this->periods) {
        task_manager_results.emplace_back(std::vector<int>{});
    }
    for (auto &period : this->periods) {
        long index = &period - &periods[0];
        std::vector<int> *results_ptr = &task_manager_results.at(index);
        std::thread task_manager_thread([index, period, totalTimeOfTaskOne, results_ptr](){
            // std::cout << "launching thread " << index << " with period " << period << " and period count " << totalTimeOfTaskOne / period << std::endl;
            task_manager tm {static_cast<int>(index), period, totalTimeOfTaskOne / period, results_ptr};
            tm.start();
        });
        task_manager_threads.emplace_back(std::move(task_manager_thread));
    }

    // Now we'll wait for the task manager threads to finish.
    for (int i = 0; i < task_manager_threads.size(); i++) {
        auto &task_manager_thread = task_manager_threads.at(i);
        std::vector<int> &task_results = task_manager_results.at(i);
        auto period = periods.at(i);
        task_manager_thread.join();
        std::cout << "Thread of period " << period << " finished, results are ";
        print_int_vec(task_results);
    }

    task_manager_threads.clear();
}
