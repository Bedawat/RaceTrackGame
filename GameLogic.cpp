//
// Created by Peter Wätzel on 01.06.25.
//

#include "GameLogic.h"

GameLogic::GameLogic(const Settings& settings) : m_state(START_MENU), m_settings(settings),
                                           m_track(m_settings), m_currentPlayer(0)
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
    case 4:
        {
            m_players.emplace_back(BLACK, Vector2(3, 8));
        }
    case 3:
        {
            m_players.emplace_back(DARKBLUE, Vector2(4, 8));
        }
    case 2:
        {
            m_players.emplace_back(LIME, Vector2(5, 8));
        }
    case 1:
        {
            m_players.emplace_back(ORANGE, Vector2(6, 8));
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
