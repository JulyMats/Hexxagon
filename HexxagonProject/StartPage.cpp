#include <iostream>
#include "StartPage.h"

StartPage::StartPage(sf::RenderWindow &window) : window(window) {
    sf::Image icon;
    if (!icon.loadFromFile("../img/icon.png")) {
        std::cout << "Failed to load icon." << std::endl;
    }
    window.setIcon(icon);

    if (!buttonFont.loadFromFile("../fonts/Batavia Bold.ttf")) {
        std::cout << "Failed to load font." << std::endl;
    }
    if (!titleFont.loadFromFile("../fonts/ColumbiaRandom BoldItalic.ttf")) {
        std::cout << "Failed to load font." << std::endl;
    }

    sf::Text titleTxt(titleFont, "HEXXAGON", 100);
    titleTxt.setFillColor(sf::Color::Magenta);
    titleTxt.setPosition({270.f, 200.f});
    titleTxt.setLetterSpacing(3);
    titleText = titleTxt;

    button.setRadius(100.f);
    button.setFillColor(sf::Color::Magenta);
    button.setPosition({470.f, 400.f});

    sf::Text buttonTxt(buttonFont, "START", 40);
    buttonTxt.setFillColor(sf::Color::White);
    buttonTxt.setPosition({480.f, 470.f});
    buttonText = buttonTxt;

    if (!backgroundTexture.loadFromFile("../img/background.jpg")) {
        std::cout << "Failed to load image for background." << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void StartPage::draw() {
    window.draw(backgroundSprite);
    window.draw(titleText);
    window.draw(button);
    window.draw(buttonText);
}

void StartPage::handleMouseClick(sf::Event::MouseButtonEvent mouseButton) {
    if (mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (button.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
            button.setFillColor(sf::Color::Transparent);
        }
    }
}