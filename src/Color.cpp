#include "Color.h"

const sf::Color getRandomColor()
{
    // Return random color from the colors bellow
    switch (rand() % COLORS_AMOUNT)
    {
    case 0:
        return sf::Color::Red;
    case 1:
        return sf::Color::Blue;
    case 2:
        return sf::Color::Green;
    case 3:
        return sf::Color::Yellow;
    case 4:
        return sf::Color::Cyan;
    case 5:
        return sf::Color::Magenta;
    }
    return sf::Color::White;
}