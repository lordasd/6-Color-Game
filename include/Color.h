#pragma once

#include <SFML/Graphics.hpp>
#include "Config.h"

// Comparator for sf::Color
struct ColorComparator
{
    bool operator()(const sf::Color& lhs, const sf::Color& rhs) const
    {
        return lhs.toInteger() < rhs.toInteger();
    }
};

const sf::Color getRandomColor();