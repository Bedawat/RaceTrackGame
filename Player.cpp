//
// Created by Peter Wätzel on 01.06.25.
//

#include "Player.h"

Player::Player()
{
}

// TODO: add player functionality
Player::Player(Vector2 position, Color color) : m_position(position), m_color(color)
{
    m_path.push_back(position);
}

Player::~Player()
{
}

void Player::move(Vector2 direction)
{
    m_velocity.x += direction.x;
    m_velocity.y += direction.y;

    m_position.x += m_velocity.x;
    m_position.y += m_velocity.y;

    m_path.push_back(m_position);
}

void Player::draw()
{
    DrawCircle( this->m_position.x * m_settings.cellSize + m_settings.cellSize / 2,
            m_settings.cellSize / 2,
            this->m_position.y * m_settings.cellSize + m_settings.cellSize / 2,
            this->m_color);
}
