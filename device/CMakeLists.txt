cmake_minimum_required(VERSION 3.21)
project(device)

set(CMAKE_CXX_STANDARD 14)

add_executable(device main.cpp rtos.cpp rtos.h delay_task.cpp delay_task.h task_manager.cpp task_manager.h md5.cpp md5.h)
