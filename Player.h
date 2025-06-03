//
// Created by Peter Wätzel on 01.06.25.
//

#pragma once
#include <raylib.h>


class Player {
public:
    explicit Player(Vector2 position);
    ~Player();

private:
    Vector2 m_position;
    // TODO: Array, Vector, Liste für bereits gefahrene Strecke

};
