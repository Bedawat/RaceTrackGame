//
// Created by Peter Wätzel on 01.06.25.
//

#include "Player.h"

Player::Player() : m_position(3, 8), m_color(BLACK)
{
}

Player::Player(Color color, Vector2 position) : m_color(color), m_position(position)
{
    m_path.push_back(m_position);
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

Vector2 Player::getVelocity() const
{
    return m_velocity;
}

Color Player::getColor() const
{
    return m_color;
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
    // Draw the path as lines
    for (size_t i = 1; i < m_path.size(); ++i)
    {
        DrawLineEx(
    Vector2{m_path[i - 1].x * m_settings.cellSize - m_settings.cellSize / 2,
            m_path[i - 1].y * m_settings.cellSize - m_settings.cellSize / 2},
    Vector2{m_path[i].x * m_settings.cellSize - m_settings.cellSize / 2,
            m_path[i].y * m_settings.cellSize - m_settings.cellSize / 2},
            4.0f, // Dicke der Linie in Pixeln
    Fade(m_color, 0.8f)
        );
    }
}
