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
    switch (m_settings.playerCount)
    {
    case 1:
        {
            m_players.emplace_back(BLACK);
            break;
        }
    case 2:
        {
            m_players.emplace_back(BLACK);
            m_players.emplace_back(DARKBLUE);
            break;
        }
    case 3:
        {
            m_players.emplace_back(BLACK);
            m_players.emplace_back(DARKBLUE);
            m_players.emplace_back(LIME);
            break;
        }
    case 4:
        {
            m_players.emplace_back(BLACK);
            m_players.emplace_back(DARKBLUE);
            m_players.emplace_back(LIME);
            m_players.emplace_back(ORANGE);
            break;
        }
    default: break;
    }

    m_track.init();
}

void GameLogic::update()
{

}

void GameLogic::draw()
{
    m_track.draw();

    for (Player player : m_players)
    {
        player.draw();
    }
}
