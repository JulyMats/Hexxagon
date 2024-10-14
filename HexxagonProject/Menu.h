#ifndef HEXXAGON_MENU_H
#define HEXXAGON_MENU_H
#include <SFML/Graphics.hpp>
class Menu {
private:
    sf::RenderWindow &window;
    sf::Font font;
    sf::Font titleFont;
    sf::Text titleText;
    sf::Text rubiesText;
    sf::Text pearlsText;
    sf::Text buttonText;
    sf::Text firstOptionText;
    sf::Text secondOptionText;
    sf::CircleShape rubiesImage;
    sf::CircleShape pearlsImage;
    sf::Texture rubiesTexture;
    sf::Texture pearlsTexture;
    sf::Sprite rubiesSprite;
    sf::Texture pearlsSprite;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape rectangleBackground;
    sf::RectangleShape button;
    int numberOfActiveOption;
    int selectedOption;
public:
    explicit Menu(sf::RenderWindow &window);
    void draw();
    void handleMouseClick(sf::Event::MouseButtonEvent mouseButton);
    void handleTextEnter();
    int getSelectedOptionNumber() const;
};
#endif
