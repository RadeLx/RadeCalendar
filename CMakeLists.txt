cmake_minimum_required(VERSION 3.25)
project(RadeCalendar)

set(CMAKE_CXX_STANDARD 20)

add_executable(RadeCalendar main.cpp src/calendar.cpp src/ansi2unicode.cpp)
