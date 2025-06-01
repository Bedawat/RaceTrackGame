//
// Created by Peter Wätzel on 01.06.25.
//

#pragma once
#include "GameLogic.h"
#include "Settings.h"


class GameEngine {
public:
    GameEngine();
    ~GameEngine();

    void run();


private:
    Settings settings;
    GameLogic game;

    void update();
    void draw();
    void drawMenu();
    void drawGame();
    void drawGameOver();

};
