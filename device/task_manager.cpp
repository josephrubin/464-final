//
// Created by Joseph Rubin on 5/2/22.
//

#include "task_manager.h"
#include "delay_task.h"
#include "md5.h"

#include <iostream>
#include <utility>

bool validate_challenge(int challenge_size, std::string possible_solution) {
    std::string hash = md5(possible_solution);
    for (int i = 0; i < challenge_size; i++) {
        if (hash.at(i) != '0') {
            return false;
        }
    }
    // std::cout << "Woah, you got it with str " << possible_solution << " and hash " << hash << std::endl;
    return true;
}

// from https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
std::string random_string(const int len) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

uint64_t get_time_ms() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void run_periods(int thread_id, int period_ms, int period_count, int period_index, uint64_t starting_time_ms, std::vector<int> *results) {
    if (period_count <= 0) {
        return;
    }

    // Do the task.
    if (period_ms == 1000) {
        int i = 0;
        std::string nonce = random_string(8);
        while (!validate_challenge(2, nonce + std::to_string(i))) {
            i++;
        }
    }
    else {
        int i = 0;
        std::string nonce = random_string(8);
        while (!validate_challenge(5, nonce + std::to_string(i))) {
            i++;
        }
    }

    // Check how long it took to do the task.
    unsigned long long next_period_ms = (period_index + 1) * period_ms;
    auto current_ms = get_time_ms() - starting_time_ms;
    auto period_remainder_ms = current_ms % period_ms;
    const auto delay_ms = period_ms - period_remainder_ms;
    // std::cout << "Finished at time " << current_ms << std::endl;

    // Store the results of the task.
    if (current_ms <= next_period_ms) {
        // std::cout << "Finished on time, period is " << period_ms << " remainder is " << period_remainder_ms << " delaying for " << delay_ms << std::endl;
        results->push_back(0);
    }
    else {
        // std::cout << "Finished late, period is " << period_ms << " remainder is " << period_remainder_ms << " delaying for " << delay_ms << std::endl;
        results->push_back(static_cast<int>(current_ms - next_period_ms));
    }

    if (period_count <= 1) {
        return;
    }

    // Recursively do a new task after the givven delay.
    delay_task t(static_cast<int>(delay_ms), [thread_id, period_ms, period_count, period_index, starting_time_ms, &results](){
        run_periods(thread_id, period_ms, period_count - 1, period_index + 1, starting_time_ms, results);
    });

    t.task_thread.join();
}

void task_manager::start() {
    run_periods(id, period_ms, period_count, 0, get_time_ms(), results);
}
