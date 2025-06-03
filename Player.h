//
// Created by Peter Wätzel on 01.06.25.
//

#pragma once
#include <raylib.h>
#include <vector>


class Player {
public:
    Player();
    explicit Player(Vector2 position);
    ~Player();

private:
    Vector2 m_position;
    Vector2 m_velocity;
    std::vector<Vector2> m_positions;

};
