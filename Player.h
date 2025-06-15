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
    Vector2 getVelocity() const;
    void setVelocity(Vector2 velocity);
    Color getColor() const;
    int getCheckpointCount() const;

    void move(Vector2 direction);
    void draw();
    void increaseCheckpointCount();

private:
    Vector2 m_position{};
    Vector2 m_velocity = Vector2(0,0);
    Color m_color;
    Settings m_settings;
    std::vector<Vector2> m_path;
    int m_checkpointCount = 0;

};
