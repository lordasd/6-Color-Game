#include "MainMenu.h"

MainMenu::MainMenu()
	:  m_backgroudMenu(TextureManager::instance().getMenu())
{
	// Set all button sprites
	sf::Vector2f location(WIDTH / 2 - 85, 260.f);
	m_buttons.emplace_back(TextureManager::instance().getRandom());
	m_buttons.emplace_back(TextureManager::instance().getGreedy());
	m_buttons.emplace_back(TextureManager::instance().getSmart());
	m_buttons.emplace_back(TextureManager::instance().getExit());

	// Set locations of the buttons in the window
	for (auto& button : m_buttons)
	{
		button.setPosition(location);
		location.y += 97.f;
	}
}

void MainMenu::drawMenu(sf::RenderWindow& window) const
{
	window.draw(m_backgroudMenu);
	for (const auto& button : m_buttons)
		window.draw(button);
}

std::optional<std::pair<GameState, OpponentType>> MainMenu::handleClick(sf::Vector2f mousePos)
{
	// return game state and opponent type depending on the button pressed;
	if (m_buttons[static_cast<int>(Buttons::Random)].getGlobalBounds().contains(mousePos))
		return std::make_pair(GameState::GamePlay, OpponentType::Random);
	else if(m_buttons[static_cast<int>(Buttons::Greedy)].getGlobalBounds().contains(mousePos))
		return std::make_pair(GameState::GamePlay, OpponentType::Greedy);
	else if(m_buttons[static_cast<int>(Buttons::Smart)].getGlobalBounds().contains(mousePos))
		return std::make_pair(GameState::GamePlay, OpponentType::Smart);
	else if (m_buttons[static_cast<int>(Buttons::Exit)].getGlobalBounds().contains(mousePos))
		return std::make_pair(GameState::Exit, OpponentType::None);

	return std::nullopt;
}
