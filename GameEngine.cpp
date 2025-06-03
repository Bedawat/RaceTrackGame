//
// Created by Peter Wätzel on 01.06.25.
//

#include "GameEngine.h"
#include "raylib.h"


GameEngine::GameEngine() : game(m_settings)
{
    InitWindow(Settings::windowWidth, Settings::windowHeight, "Racetrack Game");
    SetTargetFPS(60);
}

GameEngine::~GameEngine()
{
    CloseWindow();
}

void GameEngine::run()
{
    while (!WindowShouldClose())
    {
        update();
        draw();
    }
}

void GameEngine::update()
{
    game.update();
}

void GameEngine::draw()
{
    switch (game.getState())
    {
    case GameState::START_MENU:
        {
            drawStartMenu();
            break;
        }
    case GameState::GAME_MENU:
        {
            drawGameMenu();
            break;
        }
    case GameState::PLAYING:
        {
            drawGame();
            break;
        }
    case GameState::GAME_OVER:
        {
            drawGameOver();
            break;
        }
    }
}

void GameEngine::drawStartMenu()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Welcome to the Racetrack Game!", 190, 200, 20, DARKGRAY);
    DrawText("Press ENTER to start", 220, 250, 20, DARKGRAY);
    // TODO: maybe buttons 1-4, not + & -, make Buttons more in the middle
    // Spieleranzahl anzeigen und Buttons
    DrawText(TextFormat("Players: %d", m_settings.playerCount), 220, 300, 20, DARKGRAY);
    Rectangle btnMinusPlayers = {350, 300, 30, 30};
    Rectangle btnPlusPlayers = {390, 300, 30, 30};
    DrawRectangleRec(btnMinusPlayers, LIGHTGRAY);
    DrawRectangleRec(btnPlusPlayers, LIGHTGRAY);
    DrawText("-", 360, 305, 20, DARKGRAY);
    DrawText("+", 400, 305, 20, DARKGRAY);

    // Track anzeigen und Buttons
    DrawText(TextFormat("Track: %d", m_settings.TrackNumber), 220, 340, 20, DARKGRAY);
    Rectangle btnMinusTrack = {350, 340, 30, 30};
    Rectangle btnPlusTrack = {390, 340, 30, 30};
    DrawRectangleRec(btnMinusTrack, LIGHTGRAY);
    DrawRectangleRec(btnPlusTrack, LIGHTGRAY);
    DrawText("-", 360, 345, 20, DARKGRAY);
    DrawText("+", 400, 345, 20, DARKGRAY);

    // Button-Logik
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        if (CheckCollisionPointRec(mouse, btnMinusPlayers) && m_settings.playerCount > 1)
            m_settings.playerCount--;
        if (CheckCollisionPointRec(mouse, btnPlusPlayers) && m_settings.playerCount < 4)
            m_settings.playerCount++;
        if (CheckCollisionPointRec(mouse, btnMinusTrack) && m_settings.TrackNumber > 1)
            m_settings.TrackNumber--;
        if (CheckCollisionPointRec(mouse, btnPlusTrack) && m_settings.TrackNumber < 3)
            m_settings.TrackNumber++;
    }

    EndDrawing();
    if (IsKeyPressed(KEY_ENTER))
    {
        game.getState() = GameState::PLAYING;
    }
}

void GameEngine::drawGameMenu()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Tutorial", 190, 200, 20, DARKGRAY);
    DrawText("Use the arrow keys to navigate your player. Press Enter to confirm your choice", 220, 250, 20, DARKGRAY);


}

void GameEngine::drawGame()
{
    // TODO: implement Game window
}

void GameEngine::drawGameOver()
{
    // TODO: implement Game Over window
}
