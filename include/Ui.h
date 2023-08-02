#pragma once

#include <vector>
#include <array>
#include "Hexagon.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Config.h"
#include <optional>
#include "TextureManager.h"
#include "SoundManager.h"

class Ui {
public:
	Ui() = default;
	Ui(const sf::Color& opponentStartColor, const sf::Color& playerStartColor);
	void drawUi(sf::RenderWindow& window);
	std::optional<sf::Color> handleClick(const sf::Vector2f& mousePos);
	void handleOpponent(const sf::Color& color);
	std::pair<sf::Color, sf::Color> takenColors() const;
	void setCapturedAmount(const std::pair<size_t, size_t> captured);
	const std::pair<size_t, size_t> getCapturedAmount() const;
	const std::vector<sf::Color>& getColorArr() const;
	void resetTakenButtons(const sf::Color& opponentColor, const sf::Color& playerColor);

private:
	std::vector<sf::CircleShape> m_buttons;
	sf::RectangleShape m_buttonsBackground;
	std::array<bool, COLORS_AMOUNT> m_button_is_taken{};
	int m_opponents_button_index;
	std::vector<sf::Color> m_color_arr =
	{ sf::Color::Blue, sf::Color::Yellow, sf::Color::Red,
	  sf::Color::Green, sf::Color::Magenta, sf::Color::Cyan };
	std::pair<sf::Sprite, sf::Sprite> m_x;
	// Player & Enemy capture percentage
	std::pair<float, float> m_captured;
	sf::Font m_font;
	std::pair<sf::Text, sf::Text> m_capturedText;
	sf::Sound m_click;
};