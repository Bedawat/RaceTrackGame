//
// Created by Peter Wätzel on 01.06.25.
//

#pragma once
#include "Settings.h"
#include <raylib.h>

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
    void init() const;

    bool checkCollision(int x, int y);

private:
    const Settings& m_settings;
    int** m_grid;
    int m_startX, m_startY;
    int m_finishX, m_finishY;

};
