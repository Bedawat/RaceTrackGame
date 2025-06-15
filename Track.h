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
    GRASS,
    START,
    FINISH,
    CHECKPOINT
} Tile;


class Track {
public:
    explicit Track(const Settings& settings);
    ~Track();

    void draw();
    void init() const;
    void reset() const;


    int getTile(Vector2 pos) const;

private:
    const Settings& m_settings;
    int** m_grid;

    void standardGrid() const;

};
