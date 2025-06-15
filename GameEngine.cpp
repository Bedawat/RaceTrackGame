//
// Created by Peter Wätzel on 01.06.25.
//

#include "GameEngine.h"
#include "raylib.h"


GameEngine::GameEngine() : game(m_settings)
{
    InitWindow(m_settings.windowWidth, m_settings.windowHeight, "Racetrack Game");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
}

GameEngine::~GameEngine()
{
    CloseWindow();
}

void GameEngine::run()
{
    while (m_isRunning && !WindowShouldClose())
    {
        update();
        draw();
    }
}

void GameEngine::update()
{
    switch (game.getGameState())
    {
    case START_MENU:
        {
            // Wenn Enter gedrückt wurde, zu PLAYING wechseln und Player, Track initialisieren
            if (IsKeyPressed(KEY_ENTER))
            {
                game.setGameState(PLAYING);
                game.init();
            }
            else if (IsKeyPressed(KEY_ESCAPE))
            {
                m_isRunning = false;
            }
            break;
        }
    case GAME_MENU:
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                game.setGameState(PLAYING);
            }
            else if (IsKeyPressed(KEY_ESCAPE))
            {
                game.reset();
                game.setGameState(START_MENU);
            }
            break;
        }
    case PLAYING:
        {
            if (IsKeyPressed(KEY_ESCAPE))
            {
                game.setGameState(GAME_MENU);
            }
            game.update();
            break;
        }
    case GAME_OVER:
        {
            // Wenn Enter gedrückt wurde, zurück zum START_MENU
            if (IsKeyPressed(KEY_ENTER))
            {
                game.reset();
            }
            else if (IsKeyPressed(KEY_ESCAPE))
            {
                m_isRunning = false;
            }
            break;
        }
    case TUTORIAL:
        {
            if (IsKeyPressed(KEY_ESCAPE))
            {
                game.setPreviousGameState();
            }
            break;
        }
    }
}

void GameEngine::draw()
{
    switch (game.getGameState())
    {
    case START_MENU:
        {
            drawStartMenu();
            break;
        }
    case GAME_MENU:
        {
            drawGameMenu();
            break;
        }
    case PLAYING:
        {
            drawGame();
            break;
        }
    case GAME_OVER:
        {
            drawGameOver();
            break;
        }
    case TUTORIAL:
        {
            drawTutorial();
            break;
        }
    }
}


void GameEngine::drawStartMenu()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    int centerX = m_settings.windowWidth / 2;
    int y = 100;
    int lineHeight = 35;

    const char* title = "Welcome to the Racetrack Game!";
    DrawText(title, centerX - MeasureText(title, 28) / 2, y, 28, DARKGRAY);
    y += lineHeight + 10;

    const char* line1 = "Ziel: Erreiche als Erster das Ziel auf der Rennstrecke.";
    DrawText(line1, centerX - MeasureText(line1, 20) / 2, y, 20, GRAY);
    y += lineHeight;

    const char* line2 = "Steuerung: Pfeiltasten zum Auswählen der Richtung.";
    DrawText(line2, centerX - MeasureText(line2, 20) / 2, y, 20, GRAY);
    y += lineHeight;

    const char* line3 = "Bestätige deine Auswahl mit ENTER.";
    DrawText(line3, centerX - MeasureText(line3, 20) / 2, y, 20, GRAY);
    y += lineHeight;

    const char* line4 = "Passe Spieleranzahl und Strecke unten an.";
    DrawText(line4, centerX - MeasureText(line4, 20) / 2, y, 20, GRAY);
    y += lineHeight + 10;

    const char* startText = "Press ENTER to start";
    DrawText(startText, centerX - MeasureText(startText, 24) / 2, y, 24, DARKGRAY);
    y += lineHeight + 20;

    // Spieleranzahl mittig mit Buttons
    std::string playersText = TextFormat("Players: %d", m_settings.playerCount);
    int playersTextWidth = MeasureText(playersText.c_str(), 20);
    int totalPlayersWidth = playersTextWidth + 80; // 2x Button (je 30) + 2x Abstand (je 10)
    int playersStartX = centerX - totalPlayersWidth / 2;

    DrawText(playersText.c_str(), playersStartX, y, 20, DARKGRAY);

    Rectangle btnMinusPlayers = {
        static_cast<float>(playersStartX + playersTextWidth + 10), static_cast<float>(y), 30.0f, 30.0f
    };
    Rectangle btnPlusPlayers = {
        static_cast<float>(playersStartX + playersTextWidth + 50), static_cast<float>(y), 30.0f, 30.0f
    };
    DrawRectangleRec(btnMinusPlayers, LIGHTGRAY);
    DrawRectangleRec(btnPlusPlayers, LIGHTGRAY);
    DrawText("-", playersStartX + playersTextWidth + 17, y + 5, 20, DARKGRAY);
    DrawText("+", playersStartX + playersTextWidth + 57, y + 5, 20, DARKGRAY);

    y += lineHeight + 10;

    // Track mittig mit Buttons
    std::string trackText = TextFormat("Track: %d", m_settings.TrackNumber);
    int trackTextWidth = MeasureText(trackText.c_str(), 20);
    int totalTrackWidth = trackTextWidth + 80;
    int trackStartX = centerX - totalTrackWidth / 2;

    DrawText(trackText.c_str(), trackStartX, y, 20, DARKGRAY);

    Rectangle btnMinusTrack = {
        static_cast<float>(trackStartX + trackTextWidth + 10), static_cast<float>(y), 30.0f, 30.0f
    };
    Rectangle btnPlusTrack = {
        static_cast<float>(trackStartX + trackTextWidth + 50), static_cast<float>(y), 30.0f, 30.0f
    };
    DrawRectangleRec(btnMinusTrack, LIGHTGRAY);
    DrawRectangleRec(btnPlusTrack, LIGHTGRAY);
    DrawText("-", trackStartX + trackTextWidth + 17, y + 5, 20, DARKGRAY);
    DrawText("+", trackStartX + trackTextWidth + 57, y + 5, 20, DARKGRAY);

    y += lineHeight + 10;
    const char* tutorialText = "Tutorial anzeigen";
    int tutBtnWidth = MeasureText(tutorialText, 22) + 40;
    int tutBtnHeight = 40;
    int tutBtnX = centerX - tutBtnWidth / 2;
    int tutBtnY = y;

    Rectangle btnTutorial = {
        static_cast<float>(tutBtnX), static_cast<float>(tutBtnY), static_cast<float>(tutBtnWidth),
        static_cast<float>(tutBtnHeight)
    };
    DrawRectangleRec(btnTutorial, LIGHTGRAY);
    DrawText(tutorialText, tutBtnX + 20, tutBtnY + 8, 22, DARKGRAY);


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
        if (CheckCollisionPointRec(mouse, btnTutorial))
        {
            game.setGameState(TUTORIAL);
        }
    }

    EndDrawing();
}

void GameEngine::drawGameMenu()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    int centerX = m_settings.windowWidth / 2;
    int y = 100;
    int lineHeight = 35;

    const char* title = "Spiel-Erklärung";
    DrawText(title, centerX - MeasureText(title, 28) / 2, y, 28, DARKGRAY);
    y += lineHeight + 10;

    const char* line1 = "Ziel: Erreiche als Erster das Ziel auf der Rennstrecke.";
    DrawText(line1, centerX - MeasureText(line1, 20) / 2, y, 20, GRAY);
    y += lineHeight;

    const char* line2 = "Steuerung: Pfeiltasten zum Auswählen der Richtung.";
    DrawText(line2, centerX - MeasureText(line2, 20) / 2, y, 20, GRAY);
    y += lineHeight;

    const char* line3 = "Bestätige deine Auswahl mit ENTER.";
    DrawText(line3, centerX - MeasureText(line3, 20) / 2, y, 20, GRAY);
    y += lineHeight;

    const char* line4 = "Passe Spieleranzahl und Strecke im Hauptmenü an.";
    DrawText(line4, centerX - MeasureText(line4, 20) / 2, y, 20, GRAY);
    y += lineHeight + 10;

    const char* info1 = "Drücke ENTER, um zum Spiel zurückzukehren.";
    DrawText(info1, centerX - MeasureText(info1, 20) / 2, y, 20, DARKGRAY);
    y += lineHeight;

    const char* info2 = "Drücke ESC, um ins Hauptmenü zurückzukehren.";
    DrawText(info2, centerX - MeasureText(info2, 20) / 2, y, 20, DARKGRAY);

    y += lineHeight + 10;
    const char* tutorialText = "Tutorial anzeigen";
    int tutBtnWidth = MeasureText(tutorialText, 22) + 40;
    int tutBtnHeight = 40;
    int tutBtnX = centerX - tutBtnWidth / 2;
    int tutBtnY = y;

    Rectangle btnTutorial = {
        static_cast<float>(tutBtnX), static_cast<float>(tutBtnY), static_cast<float>(tutBtnWidth),
        static_cast<float>(tutBtnHeight)
    };
    DrawRectangleRec(btnTutorial, LIGHTGRAY);
    DrawText(tutorialText, tutBtnX + 20, tutBtnY + 8, 22, DARKGRAY);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        if (CheckCollisionPointRec(mouse, btnTutorial))
        {
            game.setGameState(TUTORIAL);
        }
    }

    EndDrawing();
}

void GameEngine::drawGame()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    game.draw();
    EndDrawing();
}

void GameEngine::drawGameOver()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    int centerX = m_settings.windowWidth / 2;
    int y = 120;
    int lineHeight = 45;

    const char* title = "Game Over!";
    DrawText(title, centerX - MeasureText(title, 40) / 2, y, 40, RED);
    y += lineHeight + 10;

    if (game.getWinner() >= 0)
    {
        std::string text = "Gewinner: Spieler " + std::to_string(game.getWinner() + 1);
        Player winner = game.getPlayers().at(game.getWinner());
        DrawText(text.c_str(), centerX - MeasureText(text.c_str(), 30) / 2, y, 30, winner.getColor());
        y += lineHeight;
        std::string pathText = "Anzahl der Spielzüge: " + std::to_string(winner.getPathLength());
        DrawText(pathText.c_str(), centerX - MeasureText(pathText.c_str(), 30) / 2, y, 30, winner.getColor());
        y += lineHeight + 10;
    }

    const char* info = "Drücke ENTER, um zum Hauptmenü zurückzukehren.";
    DrawText(info, centerX - MeasureText(info, 22) / 2, y + 30, 22, DARKGRAY);

    const char* info2 = "Drücke ESC, um das Spiel zu beenden.";
    DrawText(info2, centerX - MeasureText(info2, 20) / 2, y + 65, 20, DARKGRAY);

    EndDrawing();
}

void GameEngine::drawTutorial()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    int centerX = m_settings.windowWidth / 2;
    int y = 100;
    int lineHeight = 32;

    const char* title = "Tutorial";
    DrawText(title, centerX - MeasureText(title, 28) / 2, y, 28, DARKGRAY);
    y += lineHeight + 10;

    const char* line1 = "In jedem Spielzug bewegt der Spieler sein Auto von einem Gitterpunkt zu einem anderen.";
    DrawText(line1, centerX - MeasureText(line1, 20) / 2, y, 20, GRAY);
    y += lineHeight;

    const char* line2 = "Jeder Gitterpunkt hat acht benachbarte Punkte:";
    DrawText(line2, centerX - MeasureText(line2, 20) / 2, y, 20, GRAY);
    y += lineHeight;

    const char* line3 = "oben, unten, links, rechts und die vier Diagonalrichtungen.";
    DrawText(line3, centerX - MeasureText(line3, 20) / 2, y, 20, GRAY);
    y += lineHeight + 10;

    const char* line7 = "Der erste Zug eines Spielers muss zu einem der acht Nachbarpunkte";
    DrawText(line7, centerX - MeasureText(line7, 20) / 2, y, 20, GRAY);
    y += lineHeight;

    const char* line8 = "seiner Startposition führen (oder stehen bleiben).";
    DrawText(line8, centerX - MeasureText(line8, 20) / 2, y, 20, GRAY);
    y += lineHeight + 10;

    const char* line9 = "In jedem folgenden Zug kann der Spieler entweder";
    DrawText(line9, centerX - MeasureText(line9, 20) / 2, y, 20, GRAY);
    y += lineHeight;

    const char* line10 = "dieselbe Anzahl an Feldern in dieselbe Richtung wie im vorherigen Zug zurücklegen";
    DrawText(line10, centerX - MeasureText(line10, 20) / 2, y, 20, GRAY);
    y += lineHeight;

    const char* line11 = "(der dadurch erreichte Gitterpunkt ist der Hauptpunkt für diesen Zug),";
    DrawText(line11, centerX - MeasureText(line11, 20) / 2, y, 20, GRAY);
    y += lineHeight;

    const char* line12 = "oder stattdessen einen der acht Nachbarpunkte dieses Hauptpunkts wählen.";
    DrawText(line12, centerX - MeasureText(line12, 20) / 2, y, 20, GRAY);
    y += lineHeight + 20;

    const char* line4 = "Die Spieler bewegen ihre Autos abwechselnd.";
    DrawText(line4, centerX - MeasureText(line4, 20) / 2, y, 20, GRAY);
    y += lineHeight;

    const char* line5 = "Jeder Spielzug wird durch eine Linie markiert,";
    DrawText(line5, centerX - MeasureText(line5, 20) / 2, y, 20, GRAY);
    y += lineHeight;

    const char* line6 = "die vom Startpunkt des Zugs zum neuen Punkt führt.";
    DrawText(line6, centerX - MeasureText(line6, 20) / 2, y, 20, GRAY);
    y += lineHeight + 10;

    const char* info = "Drücke ESC, um zurückzukehren.";
    DrawText(info, centerX - MeasureText(info, 20) / 2, y, 20, DARKGRAY);

    EndDrawing();
}
