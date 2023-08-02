#include "Hexagon.h"

Hexagon::Hexagon(const sf::Vector2f& pos, float radius)
	:	m_hexagon(radius, HEXAGON_SHAPE),
		m_color(sf::Color::White)
{
	// Set position of the hexagon in the window
	m_hexagon.setPosition(pos);

	// Set outline color and thickness
	m_hexagon.setOutlineColor(sf::Color::Black);
	m_hexagon.setOutlineThickness(1.f);

	// Set default color
	m_hexagon.setFillColor(m_color);
}

const sf::CircleShape& Hexagon::getHexagon() const
{
	return m_hexagon;
}

const Occupied& Hexagon::getOccupied() const
{
	return m_occupied;
}

void Hexagon::setOccupied(const Occupied& occupation)
{
	m_occupied = occupation;
}

const sf::Color& Hexagon::getColor() const
{
	return m_color;
}

void Hexagon::setColor(const sf::Color& color)
{
    m_color = color;
	m_hexagon.setFillColor(color);
}

void Hexagon::setOutlineColor(const sf::Color& outlineColor)
{
	m_hexagon.setOutlineColor(outlineColor);
}

void Hexagon::outlineColorSwitch(const sf::Color& curr_outline, const sf::Time& elapsed)
{
	// Toggle the outline color between white and black
	if (elapsed.asSeconds() >= 0.5f)
	{
		if (curr_outline == sf::Color::Black)
			m_hexagon.setOutlineColor(sf::Color::White);
		else
			m_hexagon.setOutlineColor(sf::Color::Black);
	}
	else
		m_hexagon.setOutlineColor(curr_outline);
}