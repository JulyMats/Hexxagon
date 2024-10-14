#include <iostream>
#include "Menu.h"

/**
* Constructor, load fonts and icon, images and prepare all titles, backgrounds to be drawn
*/
Menu::Menu(sf::RenderWindow &window) : window(window) {

    sf::Image icon;
    if (!icon.loadFromFile("../img/icon.png")) {
        std::cout << "Failed to load icon." << std::endl;
    }
    window.setIcon(icon);

    if (!font.loadFromFile("../fonts/a SignboardCpsNr BoldItalic.ttf")) {
        std::cout << "Failed to load font." << std::endl;
    }
    if (!titleFont.loadFromFile("../fonts/ColumbiaRandom BoldItalic.ttf")) {
        std::cout << "Failed to load font." << std::endl;
    }

    if (!pearlsTexture.loadFromFile("../img/pearl.png")) {
        std::cout << "Failed to load image." << std::endl;
    }

    if (!rubiesTexture.loadFromFile("../img/rubie.png")) {
        std::cout << "Failed to load image." << std::endl;
    }

    titleText.setFont(titleFont);
    titleText.setFillColor(sf::Color::White);
    titleText.setCharacterSize(140);
    titleText.setPosition({205, 80});
    titleText.setString("HEXXAGON");

    rectangleBackground.setSize({800, 600});
    sf::Color color(172, 83, 194, 160);
    rectangleBackground.setFillColor(color);
    rectangleBackground.setPosition({200, 100});

    rubiesText.setFont(font);
    rubiesText.setFillColor(sf::Color::Red);
    rubiesText.setString("RUBIES");
    rubiesText.setCharacterSize(30);
    rubiesText.setPosition({450, 250});

    pearlsText.setFont(font);
    pearlsText.setFillColor(sf::Color::Cyan);
    pearlsText.setString("PEARLS");
    pearlsText.setCharacterSize(30);
    pearlsText.setPosition({650, 250});

    rubiesImage.setRadius(45);
    rubiesImage.setPointCount(6);
    rubiesImage.setRotation(sf::Angle(90));
    rubiesImage.setTexture(&rubiesTexture);
    rubiesImage.setPosition({550, 280});

    pearlsImage.setRadius(45);
    pearlsImage.setPointCount(6);
    pearlsImage.setRotation(sf::Angle(90));
    pearlsImage.setTexture(&pearlsTexture);
    pearlsImage.setPosition({750, 280});

    firstOptionText.setFont(font);
    firstOptionText.setFillColor(sf::Color::Black);
    firstOptionText.setString("PLAYER   vs.   COMPUTER");
    firstOptionText.setCharacterSize(30);
    firstOptionText.setPosition({400, 400});

    secondOptionText.setFont(font);
    secondOptionText.setFillColor(sf::Color::Black);
    secondOptionText.setString("PLAYER   vs.   PLAYER");
    secondOptionText.setCharacterSize(30);
    secondOptionText.setPosition({400, 450});

    buttonText.setFont(font);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setString("START GAME");
    buttonText.setCharacterSize(50);
    buttonText.setPosition({450, 570});


    button.setSize({500, 100});
    button.setFillColor(sf::Color::White);
    button.setOutlineColor(sf::Color(255, 0, 255, 120));
    button.setOutlineThickness(5);
    button.setPosition({350, 550});

    if (!backgroundTexture.loadFromFile("../img/background.jpg")) {
        std::cout << "Failed to load image for background." << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);


}
/**
 * draw window and display it
 */
void Menu::draw() {
    window.draw(backgroundSprite);
    window.draw(rectangleBackground);
    window.draw(titleText);
    window.draw(rubiesText);
    window.draw(pearlsText);
    window.draw(rubiesImage);
    window.draw(pearlsImage);
    window.draw(firstOptionText);
    window.draw(secondOptionText);
    window.draw(button);
    window.draw(buttonText);
}

/**
 *
 * handle select option in menu screen, if first option clicked starts game computer vs. player, else game player vs player
 *
 */
void Menu::handleMouseClick(sf::Event::MouseButtonEvent mouseButton) {
    if (mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (button.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
            selectedOption = numberOfActiveOption;
        }
        if(firstOptionText.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
            firstOptionText.setFillColor(sf::Color::White);
            numberOfActiveOption = 1;
        }
        if(secondOptionText.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
            secondOptionText.setFillColor(sf::Color::White);
            numberOfActiveOption = 2;
        }
    }
}

void Menu::handleTextEnter() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if(numberOfActiveOption != 1) {
        if (firstOptionText.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
            firstOptionText.setFillColor(sf::Color::White);
        } else
            firstOptionText.setFillColor(sf::Color::Black);
    }
    if(numberOfActiveOption != 2) {
        if (secondOptionText.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
            secondOptionText.setFillColor(sf::Color::White);
        } else
            secondOptionText.setFillColor(sf::Color::Black);
    }
    if (button.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
        button.setOutlineColor(sf::Color::Magenta);
    } else
        button.setOutlineColor(sf::Color(255, 0, 255, 120));
}

int Menu::getSelectedOptionNumber() const {
    return selectedOption;
}
