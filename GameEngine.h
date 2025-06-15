//
// Created by Peter Wätzel on 01.06.25.
//

#pragma once
#include "GameLogic.h"
#include "Settings.h"


class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    void run();

private:
    Settings m_settings;
    GameLogic game;
    bool m_isRunning = true;

    void update();
    void draw();
    void drawStartMenu();
    void drawGameMenu();
    void drawGame();
    void drawGameOver();
    void drawTutorial();
};
