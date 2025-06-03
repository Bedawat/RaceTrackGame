//
// Created by Peter Wätzel on 01.06.25.
//

#pragma once
#include "Settings.h"

typedef enum Tile
{
    STREET,
    WALL,
    GRASS
} Tile;


class Track {
public:
    explicit Track(const Settings& settings);
    ~Track();

    void draw();
    void init();

    bool checkCollision(int x, int y);

private:
    Settings m_settings;
    int** m_grid;
    int m_startX, m_startY;
    int m_finishX, m_finishY;

};
