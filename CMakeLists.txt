cmake_minimum_required(VERSION 3.31)
project(RaceTrackGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(RaceTrackGame main.cpp
        Settings.h
        GameEngine.cpp
        GameEngine.h
        GameLogic.cpp
        GameLogic.h
        Player.cpp
        Player.h
        Track.cpp
        Track.h)
