cmake_minimum_required(VERSION 3.29)
project(HW2_Reversi_OOP)

set(CMAKE_CXX_STANDARD 20)

add_executable(HW2_Reversi_OOP main.cpp
        Board.cpp
        Board.h
        Player.cpp
        Player.h
        Game.cpp
        Game.h
        StringUtils.cpp
        StringUtils.h
)
