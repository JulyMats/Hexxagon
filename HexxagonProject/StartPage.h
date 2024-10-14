#ifndef HEXXAGON_STARTPAGE_H
#define HEXXAGON_STARTPAGE_H
#pragma once
#include <SFML/Graphics.hpp>

class StartPage {
private:
    sf::RenderWindow& window;
    sf::Font titleFont;
    sf::Font buttonFont;
    sf::CircleShape button;
    sf::Text buttonText;
    sf::Text titleText;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

public:
    explicit StartPage(sf::RenderWindow &window);
    void draw();
    void handleMouseClick(sf::Event::MouseButtonEvent mouseButton);
};
#endif

