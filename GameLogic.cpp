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
    m_previousState = m_state;
    m_state = state;
}

void GameLogic::setPreviousGameState()
{
    m_state = m_previousState;
}

/** * Initializes the game logic by setting up players based on the player count in settings.
 * Each player is initialized with a specific color and starting position.
 * The track is also initialized.
 */
void GameLogic::init()
{
    switch (m_settings.playerCount)
    {
    case 4:
        {
            m_players.emplace_back(RED, Vector2(3, 8));
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

/** Resets the game state to the starting menu.
 * Clears the player list, resets the current player index, winner index,
 * direction vector, and track state.
 */
void GameLogic::reset()
{
    m_state = START_MENU;
    m_players.clear();
    m_currentPlayer = 0;
    m_winner = -1; // Reset winner
    m_direction = Vector2(0, 0);
    m_track.reset();
}

/** * Updates the game logic by handling input and checking for turn changes.
 * If the ENTER key is pressed, it triggers the next turn.
 */
void GameLogic::update()
{
    handleInput();
    if (IsKeyPressed(KEY_ENTER))
    {
        nextTurn();
    }
}

/** Draws the game state, including the track and players.
 * It also highlights the current player's direction of movement.
 */
void GameLogic::draw()
{
    m_track.draw();

    for (Player player : m_players)
    {
        player.draw();
    }

    // Draw the direction Vector where the current player is moving
    // Erst Rand zeichnen (schwarz, etwas größer), dann den eigentlichen Kreis
    DrawCircle(
        (m_players[m_currentPlayer].getPosition().x + m_players[m_currentPlayer].getVelocity().x + m_direction.x) *
        m_settings.cellSize - m_settings.cellSize / 2,
        (m_players[m_currentPlayer].getPosition().y + m_players[m_currentPlayer].getVelocity().y + m_direction.y) *
        m_settings.cellSize - m_settings.cellSize / 2,
        m_settings.cellSize / 4 + 2, // +2 Pixel für den Rand
        BLACK
    );
    DrawCircle(
        (m_players[m_currentPlayer].getPosition().x + m_players[m_currentPlayer].getVelocity().x + m_direction.x) *
        m_settings.cellSize - m_settings.cellSize / 2,
        (m_players[m_currentPlayer].getPosition().y + m_players[m_currentPlayer].getVelocity().y + m_direction.y) *
        m_settings.cellSize - m_settings.cellSize / 2,
        m_settings.cellSize / 4, m_players[m_currentPlayer].getColor());
}

/** Advances to the next player's turn.
 * It checks for collisions, updates the current player index, and resets the direction vector.
 * If the current player reaches the finish line with enough checkpoints, the game state is set to GAME_OVER.
 */
void GameLogic::nextTurn()
{
    checkCollisions();
    m_currentPlayer = (m_currentPlayer + 1) % m_players.size();
    m_direction = Vector2(0, 0);
}

/** * Handles player input for movement direction.
 * Updates the direction vector based on key presses.
 * The player can move up, down, left, or right, but cannot exceed the bounds of -1 to 1 for each axis.
 */
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

/** Checks for collisions and updates the player's position accordingly.
 * It handles boundary conditions, tile types (grass, finish, checkpoint), and player movement.
 * If the player goes out of bounds, it stops their movement and resets the direction.
 */
void GameLogic::checkCollisions()
{
    Player& player = m_players[m_currentPlayer];
    Vector2 nextPos = player.getPosition();
    nextPos.x += player.getVelocity().x + m_direction.x;
    nextPos.y += player.getVelocity().y + m_direction.y;
    // Temporäre Position für Kollisionserkennung
    Vector2 tempPos = player.getPosition();
    tempPos.x += player.getVelocity().x;
    tempPos.y += player.getVelocity().y;


    // Spielfeldgrenzen prüfen und ggf. anpassen
    bool outOfBounds = false;
    int minX = 1, minY = 1;
    int maxX = m_settings.gridWidth - 1;
    int maxY = m_settings.gridHeight - 1;

    if (nextPos.x <= minX)
    {
        nextPos.x = minX;
        outOfBounds = true;
    }
    if (nextPos.x > maxX)
    {
        nextPos.x = maxX;
        outOfBounds = true;
    }
    if (nextPos.y <= minY)
    {
        nextPos.y = minY;
        outOfBounds = true;
    }
    if (nextPos.y > maxY)
    {
        nextPos.y = maxY;
        outOfBounds = true;
    }

    if (outOfBounds)
    {
        player.setVelocity(Vector2(0, 0));
        m_direction = Vector2(0, 0);
        return; // Spieler ist außerhalb des Spielfelds, keine weitere Verarbeitung
    }

    switch (m_track.getTile(nextPos))
    {
    case WALL:

        if (m_track.getTile(tempPos) == STREET || m_track.getTile(tempPos) == GRASS)
        {
            player.setPosition(tempPos);
        }
        player.setVelocity(Vector2(0, 0));
        break;
    case GRASS:
        player.move(m_direction);
        // Geschwindigkeit auf 0
        player.setVelocity(Vector2(0, 0));
        break;
    case FINISH:
        if (player.getCheckpointCount() >= 4)
        {
            m_state = GAME_OVER;
            m_winner = m_currentPlayer;
        }
    case CHECKPOINT:
        player.increaseCheckpointCount();
    default:
        player.move(m_direction);
        break;
    }
}
