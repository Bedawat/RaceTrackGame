//
// Created by Peter Wätzel on 01.06.25.
//

#include "Player.h"

Player::Player() : m_position(3, 8), m_color(BLACK)
{
}

// TODO: add player functionality
Player::Player(Color color, Vector2 position) : m_color(color), m_position(position)
{
}

Player::~Player()
= default;

Vector2 Player::getPosition() const
{
    return m_position;
}

void Player::setPosition(Vector2 position)
{
    m_position = position;
    m_path.push_back(position);
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
    // Draw the player as a circle at its position
    // Center the circle on the grid cell
    // bei der Rechnung: - cellSize / 2,
    // damit der Kreis in der Mitte des Feldes ist (Position x = 1 ist bei Array x = 0)
    DrawCircle( m_position.x * m_settings.cellSize - m_settings.cellSize / 2,
            m_position.y * m_settings.cellSize - m_settings.cellSize / 2,
             m_settings.cellSize / 2,
            m_color);
}
