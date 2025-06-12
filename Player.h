//
// Created by Peter Wätzel on 01.06.25.
//

#pragma once
#include <raylib.h>
#include <vector>

#include "Settings.h"


class Player {
public:
    Player();
    Player(Color color, Vector2 position);
    ~Player();

    Vector2 getPosition() const;
    void setPosition(Vector2 position);

    void move(Vector2 direction);
    void draw();

private:
    Vector2 m_position{};
    Vector2 m_velocity = Vector2(0,0);
    Color m_color;
    Settings m_settings;
    std::vector<Vector2> m_path;

};
