//
// Created by Peter Wätzel on 01.06.25.
//

#include "Track.h"


Track::Track(const Settings& settings) : m_settings(settings)
{
    // Grid erstellen
    m_grid = new int*[m_settings.gridWidth];
    for (int x = 0; x < m_settings.gridWidth; x++)
    {
        m_grid[x] = new int[m_settings.gridHeight]();
    }
    standardGrid();
}

Track::~Track()
{
    for (int x = 0; x < m_settings.gridWidth; x++)
    {
        delete[] m_grid[x];
    }
    delete[] m_grid;
}

/**
 * @brief zeichnet das Spielfeld
 */
void Track::draw()
{
    for (int x = 0; x < m_settings.gridWidth; x++)
    {
        for (int y = 0; y < m_settings.gridHeight; y++)
        {
            Color color;

            switch (m_grid[x][y])
            {
            case CHECKPOINT:
            case STREET: color = LIGHTGRAY;
                break;
            case GRASS: color = DARKGREEN;
                break;
            case WALL: color = GRAY;
                break;
            case START:
                break;
            case FINISH:
                if ((x + y) % 2 == 0)
                {
                    color = WHITE;
                }
                else
                {
                    color = BLACK;
                }
                break;
            default: color = LIGHTGRAY;
                break;
            }

            DrawRectangle(x * m_settings.cellSize, y * m_settings.cellSize, m_settings.cellSize, m_settings.cellSize,
                          color);
            DrawRectangleLines(x * m_settings.cellSize, y * m_settings.cellSize, m_settings.cellSize,
                               m_settings.cellSize, DARKGRAY); // Raster wie auf Papier
        }
    }
}

/**
 * @brief Initialisiert die Strecke basierend auf der Track-Nummer
 *        und setzt das Grid entsprechend.
 */
void Track::init() const
{
    switch (m_settings.TrackNumber)
    {
    case 1:
        {
            // Gras in der Mitte
            for (int x = 6; x < m_settings.gridWidth - 6; x++)
            {
                for (int y = 6; y < m_settings.gridHeight - 6; y++)
                {
                    m_grid[x][y] = GRASS;
                }
            }
            // Start- und Ziellinie
            for (int x = 1; x < 6; x++)
            {
                m_grid[x][7] = FINISH;
                m_grid[x][8] = FINISH;
            }
            break;
        }
    case 2:
        {
            // Checkpoint rechts oben
            for (int x = 32; x < 38; x++)
            {
                for (int y = 1; y < 9; y++)
                {
                    m_grid[x][y] = CHECKPOINT;
                }
            }

            for (int x = 6; x < 10; x++)
            {
                for (int y = 6; y < m_settings.gridHeight - 8; y++)
                {
                    m_grid[x][y] = GRASS;
                }
            }

            for (int x = 6; x < 38; x++)
            {
                for (int y = m_settings.gridHeight - 8; y < m_settings.gridHeight - 6; y++)
                {
                    m_grid[x][y] = GRASS;
                }
            }

            for (int x = 15; x < 17; x++)
            {
                for (int y = 0; y < 18; y++)
                {
                    m_grid[x][y] = WALL;
                }
            }

            for (int x = 24; x < 34; x++)
            {
                for (int y = 6; y < m_settings.gridHeight - 8; y++)
                {
                    m_grid[x][y] = GRASS;
                }
            }

            for (int x = 38; x < m_settings.gridWidth - 1; x++)
            {
                for (int y = 1; y < 19; y++)
                {
                    m_grid[x][y] = GRASS;
                }
            }
            // Start- und Ziellinie
            for (int x = 1; x < 6; x++)
            {
                m_grid[x][7] = FINISH;
                m_grid[x][8] = FINISH;
            }
            break;
        }

    default:
        {
            break;
        }
    }
}

/**
 * @brief Setzt das Spielfeld auf den Standardzustand zurück.
 *        Das bedeutet, dass alle Felder auf "Street" gesetzt werden
 *        und die Checkpoints und Wände entsprechend platziert werden.
 */
void Track::reset() const
{
    standardGrid();
}

/** * @brief Setzt das Grid auf den Standardzustand zurück.
 *        Das bedeutet, dass alle Felder auf "Street" gesetzt werden
 *        und die Checkpoints und Wände entsprechend platziert werden.
 */
void Track::standardGrid() const
{
    // Ganzes Grid auf "Street" setzen
    for (int x = 0; x < m_settings.gridWidth; x++)
    {
        for (int y = 0; y < m_settings.gridHeight; y++)
        {
            m_grid[x][y] = STREET;
        }
    }
    // Checkpoint links oben (1,1 bis 6,6)
    for (int x = 1; x <= 8; x++)
    {
        for (int y = 1; y <= 6; y++)
        {
            m_grid[x][y] = CHECKPOINT;
        }
    }
    // Checkpoint rechts oben
    for (int x = m_settings.gridWidth - 9; x < m_settings.gridWidth; x++)
    {
        for (int y = 1; y <= 8; y++)
        {
            m_grid[x][y] = CHECKPOINT;
        }
    }
    // Checkpoint links unten
    for (int x = 1; x <= 8; x++)
    {
        for (int y = m_settings.gridHeight - 9; y < m_settings.gridHeight - 1; y++)
        {
            m_grid[x][y] = CHECKPOINT;
        }
    }
    // Checkpoint rechts unten
    for (int x = m_settings.gridWidth - 9; x < m_settings.gridWidth - 1; x++)
    {
        for (int y = m_settings.gridHeight - 9; y < m_settings.gridHeight; y++)
        {
            m_grid[x][y] = CHECKPOINT;
        }
    }
    // Aussenwände
    for (int x = 0; x < m_settings.gridWidth; x++)
    {
        m_grid[x][0] = WALL;
        m_grid[x][m_settings.gridHeight - 1] = WALL;
    }
    for (int y = 0; y < m_settings.gridHeight; y++)
    {
        m_grid[0][y] = WALL;
        m_grid[m_settings.gridWidth - 1][y] = WALL;
    }
}

/**
 * @brief Gibt den Tile-Typ an der angegebenen Position zurück.
 *        Die Position wird als Vector2 angegeben, wobei x und y
 *        die Koordinaten im Grid repräsentieren.
 *
 * @param pos Die Position im Grid.
 * @return Der Tile-Typ an der angegebenen Position.
 */
int Track::getTile(const Vector2 pos) const
{
    return m_grid[static_cast<int>(pos.x) - 1][static_cast<int>(pos.y) - 1];
}
