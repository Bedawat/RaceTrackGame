//
// Created by Peter Wätzel on 01.06.25.
//

#pragma once
#include <algorithm>

typedef enum GameState {
    START_MENU,
    GAME_MENU,
    PLAYING,
    GAME_OVER
} GameState;

struct Settings {
    // maybe not static? -> GameEngine member variable and give it to every other class through const ref
    // Grid dimensions
    const int gridWidth = 42;
    const int gridHeight = 30;


    const int windowWidth = gridWidth * 25;
    const int windowHeight = gridHeight * 25;

    const int cellSize = std::min(windowWidth / gridWidth, windowHeight / gridHeight);

    int playerCount = 1;
    int TrackNumber = 1;

};
