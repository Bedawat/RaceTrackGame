//
// Created by Peter Wätzel on 01.06.25.
//

#pragma once
#include <vector>

#include "Player.h"
#include "Settings.h"
#include "Track.h"


class GameLogic {
public:
    explicit GameLogic(const Settings& settings);
    ~GameLogic();

    [[nodiscard]] GameState getGameState() const;
    [[nodiscard]] int getWinner() const;
    [[nodiscard]] const std::vector<Player>& getPlayers() const;
    void setGameState(GameState state);
    void init();
    void reset();
    void update();
    void draw();
    void nextTurn();

private:
    GameState m_state;
    const Settings& m_settings;
    std::vector<Player> m_players;
    Track m_track;
    int m_currentPlayer = 1;
    int m_winner = -1; // -1 = no winner yet
    Vector2 m_direction;
    void handleInput();
    void checkCollisions();

};
