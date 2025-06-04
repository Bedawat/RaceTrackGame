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
    void setGameState(GameState state);
    void init();
    void update();
    void draw();

private:
    GameState m_state;
    Settings m_settings;
    std::vector<Player> m_players;
    Track m_track;
    int m_currentPlayer = 1;

};
