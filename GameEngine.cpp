//
// Created by Peter Wätzel on 01.06.25.
//

#include "GameEngine.h"
#include "raylib.h"


GameEngine::GameEngine()
{
    InitWindow(settings.windowWidth, settings.windowHeight, "Racetrack Game");
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
    case GameState::MENU:
        {
            drawMenu();
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

void GameEngine::drawMenu()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Welcome to the Racetrack Game!", 190, 200, 20, DARKGRAY);
    DrawText("Press ENTER to start", 220, 250, 20, DARKGRAY);

    // Spieleranzahl anzeigen und Buttons
    DrawText(TextFormat("Players: %d", settings.playerCount), 220, 300, 20, DARKGRAY);
    Rectangle btnMinusPlayers = {350, 300, 30, 30};
    Rectangle btnPlusPlayers = {390, 300, 30, 30};
    DrawRectangleRec(btnMinusPlayers, LIGHTGRAY);
    DrawRectangleRec(btnPlusPlayers, LIGHTGRAY);
    DrawText("-", 360, 305, 20, DARKGRAY);
    DrawText("+", 400, 305, 20, DARKGRAY);

    // Track anzeigen und Buttons
    DrawText(TextFormat("Track: %d", settings.TrackNumber), 220, 340, 20, DARKGRAY);
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
        if (CheckCollisionPointRec(mouse, btnMinusPlayers) && settings.playerCount > 1)
            settings.playerCount--;
        if (CheckCollisionPointRec(mouse, btnPlusPlayers) && settings.playerCount < 4)
            settings.playerCount++;
        if (CheckCollisionPointRec(mouse, btnMinusTrack) && settings.TrackNumber > 1)
            settings.TrackNumber--;
        if (CheckCollisionPointRec(mouse, btnPlusTrack) && settings.TrackNumber < 3)
            settings.TrackNumber++;
    }

    EndDrawing();
    if (IsKeyPressed(KEY_ENTER))
    {
        game.getState() = GameState::PLAYING;
    }
}

void GameEngine::drawGame()
{
}

void GameEngine::drawGameOver()
{
}
