//
// Created by Peter Wätzel on 01.06.25.
//

#include "GameLogic.h"

GameLogic::GameLogic(const Settings& settings) : m_state(START_MENU), m_track(m_settings)
{
}

GameLogic::~GameLogic()
{
    m_players.clear();
}

GameState GameLogic::getGameState() const
{
    return m_state;
}

void GameLogic::setGameState(GameState state)
{
    m_state = state;
}

void GameLogic::init()
{
    for (int i = 1; i <= m_settings.playerCount; i++)
    {
        m_players.emplace_back();
    }
    m_track.init();
}

void GameLogic::update()
{
}

void GameLogic::draw()
{
    m_track.draw();
}
