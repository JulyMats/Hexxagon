#ifndef HEXXAGON_ENGINE_H
#define HEXXAGON_ENGINE_H
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "StartPage.h"
#include "Menu.h"
#include "HighScopes.h"


class Engine{
    std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(sf::VideoMode({1200, 800}),"Hexxagon",
                                                                                  (sf::Style::Default),sf::ContextSettings(0, 0, 8));;
    sf::CircleShape blackHexagon;
    sf::Texture hexagonTexture;
    sf::Texture pearlTexture;
    sf::Texture rubieTexture;
    int placeCount[58][2];
    sf::RectangleShape buttonRectangle;
    sf::Text buttonText;
    sf::Font font;
    int numberOfPearls;
    int numberOfRubies;
    const int numberOfCells = 58;
    int prevClickedCellIndex = -1;
    bool isPlayerOneTurn = true;
    bool isPlayerTwoTurn = false;
    bool isGameVSComputer = false;
    bool isComputerTurn = false;
    std::vector<sf::CircleShape> hexagons;
    std::vector<int> pearls;
    std::vector<int> rubies;
    std::vector<int> cellIndexOfActiveChoice;
    sf::Text pearlsLives;
    sf::Text rubiesLives;
    sf::RectangleShape pearlsRectangle;
    sf::RectangleShape rubiesRectangle;
    std::vector<HighScore> highScores;
public:
    Engine();
    void input();
    void update(sf::Time const &deltaTime);
    void draw();
    void run();
    void showStartPage();
    void showMenu();
    void gameBoardInIt();
    int getClickedCellIndex(const sf::Vector2i& mousePos);
    bool isPointInsideHexagon(const sf::Vector2f &point, const sf::Vector2f &hexagonCenter, float hexagonRadius);
    bool isNeighborCell(int clickedCellIndex, int cellIndex);
    void highlightNeighboringCells(int clickedCellIndex);
    void drawGameBoard();
    bool is2LevelNeighborCell(int clickedCellIndex, int cellIndex);
    void resetHighlight();
    void drawPearls();
    void drawRubies();
    void checkNeighboringCells(int clickedCellIndex);
    void changePlayerTurn();
    void drawLives();
    void showWinScreen();
    void checkGameOver();
    void resetGame();
    void computerMove();
    void writeGameStateToFile(int numberOfRubies, int numberOfPearls);
    void clearGameStateFile();
    void addHighScore(std::vector<HighScore> &highScores, const std::string &playerName, int score);
    void sortHighScores(std::vector<HighScore> &highScores);
    void saveHighScores(const std::vector<HighScore> &highScores);
    void loadHighScores(std::vector<HighScore>& highScores);
};


#endif
