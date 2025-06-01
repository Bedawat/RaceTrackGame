//
// Created by Peter Wätzel on 01.06.25.
//

#include "GameLogic.h"

GameLogic::GameLogic(): state(MENU)
{
}

GameLogic::~GameLogic()
{
}

GameState& GameLogic::getState()
{
    return state;
}

void GameLogic::update()
{
}
