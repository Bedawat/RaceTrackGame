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

int GameLogic::getWinner() const
{
    return m_winner;
}

const std::vector<Player>& GameLogic::getPlayers() const
{
    return m_players;
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

void GameLogic::reset()
{
    m_state = START_MENU;
    m_players.clear();
    m_currentPlayer = 0;
    m_winner = -1; // Reset winner
    m_direction = Vector2(0, 0);
}

void GameLogic::update()
{
    handleInput();
    if (IsKeyPressed(KEY_ENTER))
    {
        nextTurn();
    }
}

void GameLogic::draw()
{
    m_track.draw();

    for (Player player : m_players)
    {
        player.draw();
    }
    // Draw the direction Vector where the current player is moving
    DrawCircle((m_players[m_currentPlayer].getPosition().x + m_players[m_currentPlayer].getVelocity().x + m_direction.x) * m_settings.cellSize - m_settings.cellSize / 2,
               (m_players[m_currentPlayer].getPosition().y + m_players[m_currentPlayer].getVelocity().y + m_direction.y) * m_settings.cellSize - m_settings.cellSize / 2,
               m_settings.cellSize / 4, YELLOW); // Highlight current player

}

void GameLogic::nextTurn()
{
    m_players.at(m_currentPlayer).move(m_direction);

    // Win-Condition prüfen (z.B. Ziel auf (x, y) == Zielkoordinate)
    Vector2 pos = m_players.at(m_currentPlayer).getPosition();
    if (m_track.isFinish(pos)) // Implementiere isFinish entsprechend
    {
        m_state = GAME_OVER;
        m_winner = m_currentPlayer;
        return;
    }

    m_currentPlayer = (m_currentPlayer + 1) % m_players.size();
    m_direction = Vector2(0, 0);
}

void GameLogic::handleInput()
{
    if (IsKeyPressed(KEY_UP) && m_direction.y > -1)
    {
        m_direction.y += -1;
    }
    if (IsKeyPressed(KEY_DOWN) && m_direction.y < 1)
    {
        m_direction.y += 1;
    }
    if (IsKeyPressed(KEY_LEFT) && m_direction.x > -1)
    {
        m_direction.x += -1;
    }
    if (IsKeyPressed(KEY_RIGHT) && m_direction.x < 1)
    {
        m_direction.x += 1;
    }
}
