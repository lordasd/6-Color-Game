#pragma once

#include <SFML/Graphics.hpp>
#include "Config.h"
#include <vector>
#include "TextureManager.h"

enum class Occupied {
	None, Player, Opponent
};

class Hexagon {
public:
	Hexagon() = default;
	Hexagon(const sf::Vector2f& pos, float radius);

	const sf::CircleShape& getHexagon() const;
	const Occupied& getOccupied() const;
	const sf::Color& getColor() const;
	void setOccupied(const Occupied& occupation);
	void setColor(const sf::Color& color);
	void setOutlineColor(const sf::Color& outlineColor);
	void outlineColorSwitch(const sf::Color& curr_outline, const sf::Time& elapsed);

private:
	sf::CircleShape m_hexagon;
	sf::Color m_color;
	Occupied m_occupied = Occupied::None;
	sf::Clock m_clock;
};