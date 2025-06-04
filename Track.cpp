//
// Created by Peter Wätzel on 01.06.25.
//

#include "Track.h"

// TODO: add track functionality
// TODO: add tracks
Track::Track(const Settings& settings)
{
    // Grid erstellen
    m_grid = new int*[m_settings.gridWidth];
    for (int x = 0; x < m_settings.gridWidth; x++)
    {
        m_grid[x] = new int[m_settings.gridHeight]();
    }

    // Ganzes Grid erstmal auf "Street" setzen
    for (int x = 0; x < m_settings.gridWidth; x++)
    {
        for (int y = 0; y < m_settings.gridHeight; y++)
        {
            m_grid[x][y] = STREET;
        }
    }
}

Track::~Track()
{
    for (int x = 0; x < m_settings.gridWidth; x++)
    {
        delete[] m_grid[x];
    }
    delete[] m_grid;
}

void Track::draw()
{
    for (int x = 0; x < m_settings.gridWidth; x++)
    {
        for (int y = 0; y < m_settings.gridHeight; y++)
        {
            Color color;

            switch (m_grid[x][y])
            {
            case STREET: color = LIGHTGRAY; break;
            case GRASS: color = GREEN; break;
            case WALL: color = DARKGRAY; break;
            default: color = LIGHTGRAY; break;
            }

            DrawRectangle(x * m_settings.cellSize, y * m_settings.cellSize, m_settings.cellSize, m_settings.cellSize, color);
            DrawRectangleLines(x * m_settings.cellSize, y * m_settings.cellSize, m_settings.cellSize, m_settings.cellSize, BLACK); // Raster wie auf Papier
        }
    }
}

void Track::init() const
{
    switch (m_settings.TrackNumber)
    {
    case 1:
        {
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
            // Gras in der Mitte
            for (int x = 6; x < m_settings.gridWidth - 6; x++)
            {
                for (int y = 6; y < m_settings.gridHeight - 6; y++)
                {
                    m_grid[x][y] = GRASS;
                }
            }
            break;
        }
    case 2:
        {
            break;
        }
    case 3:
        {
            break;
        }
    default:
        {
            break;
        }
    }
}

bool Track::checkCollision(int x, int y)
{
}
