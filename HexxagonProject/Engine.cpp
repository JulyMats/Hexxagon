#include <fstream>
#include <cmath>
#include <iostream>
#include "Engine.h"
void Engine::input() {
    sf::Event event;
    while(window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
            clearGameStateFile();
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                if (buttonRectangle.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                    showMenu();
                    resetGame();
                    clearGameStateFile();
                    loadHighScores(highScores);
                }
                int clickedCellIndex = getClickedCellIndex(mousePos);
                if (clickedCellIndex != -1) {
                    if(isPlayerOneTurn) {
                        if(hexagons[clickedCellIndex].getOutlineColor() == sf::Color::Green) {
                            pearls[clickedCellIndex] = 1;
                            resetHighlight();
                            checkNeighboringCells(clickedCellIndex);
                            draw();
                            changePlayerTurn();
                        } else if(hexagons[clickedCellIndex].getOutlineColor() == sf::Color::Yellow) {
                            pearls[clickedCellIndex] = 1;
                            pearls[prevClickedCellIndex] = 0;
                            resetHighlight();
                            checkNeighboringCells(clickedCellIndex);
                            draw();
                            changePlayerTurn();
                        } else if(pearls[clickedCellIndex] == 1) {
                            resetHighlight();
                            highlightNeighboringCells(clickedCellIndex);
                        }
                    } else if(isPlayerTwoTurn) {
                        if (hexagons[clickedCellIndex].getOutlineColor() == sf::Color::Green) {
                            rubies[clickedCellIndex] = 1;
                            resetHighlight();
                            checkNeighboringCells(clickedCellIndex);
                            draw();
                            changePlayerTurn();
                        } else if (hexagons[clickedCellIndex].getOutlineColor() == sf::Color::Yellow) {
                            rubies[clickedCellIndex] = 1;
                            rubies[prevClickedCellIndex] = 0;
                            resetHighlight();
                            checkNeighboringCells(clickedCellIndex);
                            draw();
                            changePlayerTurn();
                        } else if (rubies[clickedCellIndex] == 1) {
                            resetHighlight();
                            highlightNeighboringCells(clickedCellIndex);
                        }
                    }
                }
                prevClickedCellIndex = clickedCellIndex;
            }
        } else if(event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (buttonRectangle.getGlobalBounds().contains(
                    {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                buttonRectangle.setOutlineColor(sf::Color::Magenta);
            } else {
                buttonRectangle.setOutlineColor(sf::Color(255, 0, 255, 120));
            }
        }
    }
}

void Engine::update(const sf::Time &deltaTime) {
    if(isComputerTurn) {
        sf::sleep(sf::milliseconds(1000));
        computerMove();
        changePlayerTurn();
    }
}

void Engine::draw() {
    window->clear();
    drawGameBoard();
    drawPearls();
    drawRubies();
    window->draw(buttonRectangle);
    window->draw(buttonText);
    window->draw(rubiesRectangle);
    window->draw(pearlsRectangle);
    drawLives();
    checkGameOver();
    window->display();

}

Engine::Engine() {
    sf::Image icon;
    if (!icon.loadFromFile("../img/icon.png")) {
        std::cout << "Failed to load icon." << std::endl;
    }
    window->setIcon(icon);
}

void Engine::run() {
    showStartPage();
    sf::Clock clock;
    gameBoardInIt();

    while(window->isOpen()) {
        sf::Time time = clock.restart();
        input();
        update(time);
        draw();
    }
}

void Engine::showMenu() {
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Hexxagon",(sf::Style::Default),sf::ContextSettings(0, 0, 8));
    Menu menu(window);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                menu.handleMouseClick(event.mouseButton);
                if(menu.getSelectedOptionNumber() == 1)
                    isGameVSComputer = true;
                if (menu.getSelectedOptionNumber() == 1 || menu.getSelectedOptionNumber() == 2) {
                    window.close();
                    break;
                }
            } else if(event.type == sf::Event::MouseMoved) {
                menu.handleTextEnter();
            }
        }
        window.clear(sf::Color::White);
        menu.draw();
        clearGameStateFile();
        loadHighScores(highScores);
        window.display();
    }
}

void Engine::showStartPage() {
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Hexxagon",(sf::Style::Default),sf::ContextSettings(0, 0, 8));
    StartPage startPage(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                startPage.handleMouseClick(event.mouseButton);
                window.close();
                showMenu();
                break;
            }
        }
        window.clear(sf::Color::White);
        startPage.draw();
        window.display();
    }
}

void Engine::drawGameBoard() {
    for (int i = 0; i <numberOfCells; ++i) {
        window->draw(hexagons[i]);
    }
}

void Engine::gameBoardInIt() {
    if (!font.loadFromFile("../fonts/a SignboardCpsNr BoldItalic.ttf")) {
        std::cout << "Failed to load font." << std::endl;
    }
    std::ifstream inputFile("../map/gameBoard.txt");
    if (!inputFile.is_open()) {
        std::cout << "Failed to load map." << std::endl;
    }
    if (!hexagonTexture.loadFromFile("../img/hexagon.png")) {
        std::cout << "Failed to load image." << std::endl;
    }

    std::string line;
    int j = 0;
    int counter = 0;
    while(std::getline(inputFile, line)) {
        int i = 0;
        for(char val : line) {
            if(val == 'O') {
                    sf::CircleShape hexagon;
                    hexagon.setRadius(45);
                    hexagon.setPointCount(6);
                    hexagon.setRotation(sf::Angle(90));
                    hexagon.setTexture(&hexagonTexture);
                    hexagon.setOutlineColor(sf::Color(140, 130, 130));
                    hexagon.setOutlineThickness(-4);
                    hexagon.setPosition({static_cast<float>(350 + i), static_cast<float>(15 + j)});
                    placeCount[counter][0] = (i + 350);
                    placeCount[counter][1] = (j + 15);
                    counter++;
                    i+=18;
                    hexagons.push_back(hexagon);
            } else {
                i+=18;
            }
        }
        j+=42;
    }

    if (!pearlTexture.loadFromFile("../img/pearl.png")) {
        std::cout << "Failed to load image." << std::endl;
    }

    if (!rubieTexture.loadFromFile("../img/rubie.png")) {
        std::cout << "Failed to load image." << std::endl;
    }

    for (int i = 0; i < numberOfCells; ++i) {
        if(i == 0 || i == 42 || i == 51) {
            pearls.push_back(1);
        } else
            pearls.push_back(0);
    }

    for (int i = 0; i < numberOfCells; ++i) {
        if(i == 10 || i== 14 || i == 57) {
            rubies.push_back(1);
        } else
            rubies.push_back(0);
    }

    inputFile.close();
    numberOfRubies = 3;
    numberOfPearls = 3;

    buttonRectangle.setSize({80, 30});
    buttonRectangle.setFillColor(sf::Color::White);
    buttonRectangle.setOutlineColor(sf::Color(255, 0, 255, 120));
    buttonRectangle.setOutlineThickness(3);
    buttonRectangle.setPosition({100, 700});

    buttonText.setFont(font);
    buttonText.setCharacterSize(20);
    buttonText.setString("QUIT");
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition({115, 705});

    rubiesRectangle.setSize({30, 50});
    rubiesRectangle.setFillColor(sf::Color::Red);
    rubiesRectangle.setPosition({1100, 600});

    pearlsRectangle.setSize({30, 50});
    pearlsRectangle.setFillColor(sf::Color::Cyan);
    pearlsRectangle.setPosition({1100, 670});

    rubiesLives.setFont(font);
    rubiesLives.setFillColor(sf::Color::White);
    rubiesLives.setCharacterSize(50);
    rubiesLives.setPosition({1080, 600});

    pearlsLives.setFont(font);
    pearlsLives.setFillColor(sf::Color::White);
    pearlsLives.setCharacterSize(50);
    pearlsLives.setPosition({1080, 670});

}

bool Engine::isPointInsideHexagon(const sf::Vector2f& point, const sf::Vector2f& hexagonCenter, float hexagonRadius) {
    if (point.x >= hexagonCenter.x - 2*hexagonRadius && point.x <= hexagonCenter.x &&
        point.y >= hexagonCenter.y && point.y <= hexagonCenter.y + 2*hexagonRadius)
        return true;
    else
        return false;
}

int Engine::getClickedCellIndex(const sf::Vector2i& mousePos) {
    for (int i = 0; i < numberOfCells; ++i) {
        sf::Vector2f cellPos = { static_cast<float>(placeCount[i][0]), static_cast<float>(placeCount[i][1]) };
        if (isPointInsideHexagon(static_cast<sf::Vector2f>(mousePos), cellPos, hexagons[i].getRadius())) {
            return i;
        }
    }
    return -1;
}

void Engine::highlightNeighboringCells(int clickedCellIndex) {
    hexagons[clickedCellIndex].setOutlineColor(sf::Color::Yellow);

    for (int i = 0; i < numberOfCells; ++i) {
        if (isNeighborCell(clickedCellIndex, i) && pearls[i] != 1 && rubies[i] != 1) {
            hexagons[i].setOutlineColor(sf::Color::Green);
            cellIndexOfActiveChoice.push_back(i);
        } else if(is2LevelNeighborCell(clickedCellIndex, i) && pearls[i] != 1 && rubies[i] != 1) {
            hexagons[i].setOutlineColor(sf::Color::Yellow);
            cellIndexOfActiveChoice.push_back(i);
        }
    }
}

bool Engine::isNeighborCell(int clickedCellIndex, int cellIndex) {
    // Check if the cell indices are valid
    if (clickedCellIndex < 0 || clickedCellIndex >= numberOfCells ||
        cellIndex < 0 || cellIndex >= numberOfCells) {
        return false;
    }

    // Get the positions of the clicked cell and the target cell
    sf::Vector2f clickedCellPos = { static_cast<float>(placeCount[clickedCellIndex][0]), static_cast<float>(placeCount[clickedCellIndex][1]) };
    sf::Vector2f targetCellPos = { static_cast<float>(placeCount[cellIndex][0]), static_cast<float>(placeCount[cellIndex][1]) };

    // Calculate the distance between the cells
    float distance;
    distance = std::sqrt(
            std::pow(clickedCellPos.x - targetCellPos.x, 2) + std::pow(clickedCellPos.y - targetCellPos.y, 2));

    // Define the maximum distance for neighbor cells
    float maxDistance = hexagons[clickedCellIndex].getRadius() * 2;

    // Check if the distance is within the maximum distance
    return distance <= maxDistance && distance != 0;
}

bool Engine::is2LevelNeighborCell(int clickedCellIndex, int cellIndex) {
    // Check if the cell indices are valid
    if (clickedCellIndex < 0 || clickedCellIndex >= numberOfCells ||
        cellIndex < 0 || cellIndex >= numberOfCells) {
        return false;
    }

    // Get the positions of the clicked cell and the target cell
    sf::Vector2f clickedCellPos = { static_cast<float>(placeCount[clickedCellIndex][0]), static_cast<float>(placeCount[clickedCellIndex][1]) };
    sf::Vector2f targetCellPos = { static_cast<float>(placeCount[cellIndex][0]), static_cast<float>(placeCount[cellIndex][1]) };

    // Calculate the distance between the cells
    float distance;
    distance = std::sqrt(
            std::pow(clickedCellPos.x - targetCellPos.x, 2) + std::pow(clickedCellPos.y - targetCellPos.y, 2));

    // Define the maximum distance for neighbor cells
    float maxDistance = hexagons[clickedCellIndex].getRadius() * 4;

    // Check if the distance is within the maximum distance
    return distance <= maxDistance && distance!= 0;
}

void Engine::resetHighlight() {
    for (int i = 0; i < numberOfCells; ++i) {
        hexagons[i].setOutlineColor(sf::Color(140, 130, 130));
    }
}

void Engine::drawPearls() {
    for (int i = 0; i < numberOfCells; ++i) {
        if(pearls[i] == 1) {
            sf::CircleShape pearl;
            pearl.setRadius(45);
            pearl.setPointCount(6);
            pearl.setRotation(sf::Angle(90));
            pearl.setTexture(&pearlTexture);
            pearl.setPosition({static_cast<float>(placeCount[i][0]), static_cast<float>(placeCount[i][1])});
            window->draw(pearl);
        }
    }
}

void Engine::drawRubies() {
    for (int i = 0; i < numberOfCells; ++i) {
        if(rubies[i] == 1) {
            sf::CircleShape rubie;
            rubie.setRadius(45);
            rubie.setPointCount(6);
            rubie.setRotation(sf::Angle(90));
            rubie.setTexture(&rubieTexture);
            rubie.setPosition({static_cast<float>(placeCount[i][0]), static_cast<float>(placeCount[i][1])});
            window->draw(rubie);
        }
    }
}

void Engine::checkNeighboringCells(int clickedCellIndex) {
    for (int i = 0; i < numberOfCells; ++i) {
        if (isNeighborCell(clickedCellIndex, i)) {
            if(isPlayerOneTurn) {
                if(rubies[i]== 1) {
                    rubies[i] = 0;
                    pearls[i] = 1;
                }
            } else if(isPlayerTwoTurn) {
                if(pearls[i] == 1) {
                    pearls[i] = 0;
                    rubies[i] = 1;
                }
            }
        }
    }
}

void Engine::changePlayerTurn() {
    if (!isGameVSComputer) {
        if (isPlayerOneTurn) {
            isPlayerOneTurn = false;
            isPlayerTwoTurn = true;
        } else {
            isPlayerOneTurn = true;
            isPlayerTwoTurn = false;
        }
    } else {
        if (isPlayerOneTurn) {
            isPlayerOneTurn = false;
            isComputerTurn = true;
        } else {
            isPlayerOneTurn = true;
            isComputerTurn = false;
        }
    }
}

void Engine::drawLives() {
    numberOfRubies = 0;
    numberOfPearls = 0;
    for (int i = 0; i < numberOfCells; ++i) {
        if(rubies[i] == 1) {
            numberOfRubies++;
        }
        if(pearls[i]==1) {
            numberOfPearls++;
        }
    }
    rubiesLives.setString(std::to_string(numberOfRubies));
    pearlsLives.setString(std::to_string(numberOfPearls));
    writeGameStateToFile(numberOfRubies, numberOfPearls);
    window->draw(pearlsLives);
    window->draw(rubiesLives);
}

void Engine::checkGameOver() {
    if(numberOfPearls == 0 || numberOfRubies == 0) {
        showWinScreen();
        std::string playerName;
        int score;
        if(numberOfPearls == 0){
            playerName = "rubies";
            score = numberOfRubies;
        } else {
            playerName = "pearls";
            score = numberOfPearls;
        }
        addHighScore(highScores, playerName, score);
    }
}

void Engine::showWinScreen() {
    sf::RectangleShape rectangleBackground;
    rectangleBackground.setSize({600, 400});
    sf::Color color(0, 0, 0, 200);
    rectangleBackground.setFillColor(color);
    rectangleBackground.setPosition({300, 200});

    sf::Text winText(font, "", 70);
    numberOfPearls == 0 ? winText.setString("RUBIES WIN!") : winText.setString("PEARLS WIN!");
    winText.setPosition({380, 400});

    sf::CircleShape playerImage;
    playerImage.setRadius(75);
    playerImage.setPointCount(6);
    playerImage.setRotation(sf::Angle(90));
    numberOfPearls == 0 ? playerImage.setTexture(&rubieTexture) : playerImage.setTexture(&pearlTexture);
    playerImage.setPosition({680, 250});

    window->draw(rectangleBackground);
    window->draw(winText);
    window->draw(playerImage);
}

void Engine::resetGame() {
    numberOfPearls = 3;
    numberOfRubies = 3;

    for (int i = 0; i < numberOfCells; ++i) {
        if(i == 0 || i == 48 || i == 51)
            pearls[i] = 1;
        else
            pearls[i] = 0;
        if(i == 10 || i== 14 || i == 57)
            rubies[i] = 1;
        else
            rubies[i] = 0;
    }
    isPlayerOneTurn = true;
    isPlayerTwoTurn = false;
    draw();
}

void Engine::computerMove() {
    int maxNumberOfNeighborRubies = 0;
    int bestMoveOption = -1;
    int prevCell = -1;
    bool is2LevelOption = false;
    for (int i = 0; i < numberOfCells; ++i) {
        if(rubies[i] == 1) {
            for (int j = 0; j < numberOfCells; ++j) {
                if (isNeighborCell(i, j) && pearls[j] != 1 && rubies[j] != 1) {
                    int counter = 0;
                    for (int k = 0; k < numberOfCells; ++k) {
                        if((isNeighborCell(j, k)) && pearls[k] == 1)
                            counter++;
                    }
                    if(counter >= maxNumberOfNeighborRubies) {
                        maxNumberOfNeighborRubies = counter;
                        bestMoveOption = j;
                        prevCell = i;
                        is2LevelOption = false;
                    }
                } else if(is2LevelNeighborCell(i, j) && pearls[j] != 1 && rubies[j] != 1) {
                    int counter = 0;
                    for (int k = 0; k < numberOfCells; ++k) {
                        if((isNeighborCell(j, k)) && pearls[k] == 1)
                            counter++;
                    }
                    if(counter >= maxNumberOfNeighborRubies) {
                        maxNumberOfNeighborRubies = counter;
                        bestMoveOption = j;
                        prevCell = i;
                        is2LevelOption = true;
                    }
                }
            }
        }
    }
    if(is2LevelOption) {
        rubies[prevCell] = 0;
        rubies[bestMoveOption] = 1;
    } else {
        rubies[bestMoveOption] = 1;
    }
    for (int i = 0; i < numberOfCells; ++i) {
        if (isNeighborCell(bestMoveOption, i)) {
            if(pearls[i]== 1) {
                pearls[i] = 0;
                rubies[i] = 1;
            }
        }
    }
}

void Engine::writeGameStateToFile(int numberOfRubies, int numberOfPearls) {
    std::ofstream outputFile("../game_state.txt", std::ios::app);
    if (!outputFile.is_open()) {
        return;
    }
    // Write the game state information to the file
    outputFile << "Player 1 currently has " <<numberOfPearls<< " pearls on the board." << std::endl;
    outputFile << "Player 2 currently has " << numberOfRubies << " rubies on the board." << std::endl;
    // Close the file
    outputFile.close();
}

void Engine::clearGameStateFile() {
    std::ofstream outputFile("../game_state.txt", std::ofstream::out | std::ofstream::trunc);
    if (!outputFile.is_open()) {
        // Handle error if the file fails to open
        return;
    }
    // Close the file, which will clear its contents
    outputFile.close();
}

void Engine::loadHighScores(std::vector<HighScore>& highScores)
{
    std::ifstream inputFile("../high_scores.txt");
    if (!inputFile.is_open()) {
        std::cout << "Failed to load file." << std::endl;
        return;
    }

    highScores.clear();

    std::string name;
    int score;
    while (inputFile >> name >> score) {
        highScores.push_back({name, score});
    }

    inputFile.close();
}

void Engine::addHighScore(std::vector<HighScore>& highScores, const std::string& playerName, int score)
{
    highScores.push_back({playerName, score});
    sortHighScores(highScores);

    // Keep only the top 5 high scores
    if (highScores.size() > 5) {
        highScores.resize(5);
    }

    saveHighScores(highScores);
}

void Engine::sortHighScores(std::vector<HighScore>& highScores)
{
    std::sort(highScores.begin(), highScores.end(), [](const HighScore& a, const HighScore& b) {
        return a.score > b.score;  // Sort in descending order
    });
}

void Engine::saveHighScores(const std::vector<HighScore>& highScores)
{
    std::ofstream outputFile("../high_scores.txt");
    if (!outputFile.is_open()) {
        std::cout << "Failed to load file." << std::endl;
        return;
    }

    for (const auto& entry : highScores) {
        outputFile << entry.playerName << " " << entry.score << "\n";
    }

    outputFile.close();
}






