#pragma once

#include "TextureManager.h"
#include "Config.h"
#include "GameState.h"
#include "Opponent.h"
#include <optional>

enum class Buttons { Random, Greedy, Smart, Exit};

class MainMenu {
public:
	MainMenu();
	void drawMenu(sf::RenderWindow& window) const;
	std::optional<std::pair<GameState, OpponentType>> handleClick(sf::Vector2f mousePos);

private:
	sf::Sprite m_backgroudMenu;
	std::vector<sf::Sprite> m_buttons;
};