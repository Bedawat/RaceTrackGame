//
// Created by Peter Wätzel on 01.06.25.
//

#pragma once
#include <vector>

#include "Player.h"
#include "Settings.h"


class GameLogic {
public:
    explicit GameLogic(const Settings& settings);
    ~GameLogic();

    GameState& getState();
    void update();

private:
    Settings m_settings;
    std::vector<Player> m_players;

};
