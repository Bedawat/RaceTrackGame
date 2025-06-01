//
// Created by Peter Wätzel on 01.06.25.
//

#pragma once
typedef enum GameState {
    MENU,
    PLAYING,
    GAME_OVER
} GameState;


class GameLogic {
public:
    GameLogic();
    ~GameLogic();

    GameState& getState();
    void update();

private:
    GameState state;

};
