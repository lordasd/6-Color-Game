#include "Ui.h"

#include <iomanip>

Ui::Ui(const sf::Color& opponentStartColor, const sf::Color& playerStartColor)
	:	m_x(TextureManager::instance().getX(), TextureManager::instance().getX()),
		m_click(SoundManager::instance().getClick()), m_font(TextureManager::instance().getFont()),
		m_buttonsBackground(sf::Vector2f(425.f, 90.f))
{
	// Set buttons background colors
	m_buttonsBackground.setPosition(143.f, HEIGHT - 210);
	m_buttonsBackground.setFillColor(sf::Color(124, 175, 205));
	m_buttonsBackground.setOutlineThickness(1);
	m_buttonsBackground.setOutlineColor(sf::Color(sf::Color::Black));

	sf::Vector2f buttonPos(145.f, HEIGHT - 200);
	m_buttons.reserve(COLORS_AMOUNT);
	for (int i = 0;  i < COLORS_AMOUNT; ++i, buttonPos.x += 70.f)
	{
		m_buttons.emplace_back(sf::CircleShape(35.f, 6));
		m_buttons.back().setFillColor(m_color_arr[i]);
		m_buttons.back().setOutlineColor(sf::Color::Black);
		m_buttons.back().setOutlineThickness(3);
		m_buttons.back().setPosition(buttonPos);
		// Set button to be taken, so no one can press it
		if (m_color_arr[i] == opponentStartColor || m_color_arr[i] == playerStartColor)
			m_button_is_taken[i] = true;
		// Save index of the opponents button
		if (m_color_arr[i] == opponentStartColor)
			m_opponents_button_index = i;
	}
}

void Ui::drawUi(sf::RenderWindow& window)
{
	window.draw(m_buttonsBackground);

	for (size_t button = 0; button < COLORS_AMOUNT; ++button)
	{
		// Draw button
		window.draw(m_buttons[button]);

		// Set X sprite on the taken buttons
		if (m_button_is_taken[button])
		{
			if (button == m_opponents_button_index)
				m_x.second.setPosition(m_buttons[button].getPosition().x + 10.f,
					m_buttons[button].getPosition().y + 10.f);
			else
				m_x.first.setPosition(m_buttons[button].getPosition().x + 10.f,
					m_buttons[button].getPosition().y + 10.f);
		}
		// Draw X on the buttons
		window.draw(m_x.first);
		window.draw(m_x.second);
	}

	// Set font parameters
	m_capturedText.first = sf::Text("Player\n" + std::to_string(m_captured.first), m_font, 30U);
	m_capturedText.second = sf::Text("Opponent\n" + std::to_string(m_captured.second), m_font, 30U);
	m_capturedText.first.setFillColor(sf::Color::Black);
	m_capturedText.second.setFillColor(sf::Color::Black);
	m_capturedText.first.setPosition(40.f, 450.f);
	m_capturedText.second.setPosition(WIDTH - 200.f, 450.f);

	// Draw captured perentage
	window.draw(m_capturedText.first);
	window.draw(m_capturedText.second);
}

std::optional<sf::Color> Ui::handleClick(const sf::Vector2f& mousePos)
{
	for (int i = 0; i < COLORS_AMOUNT; ++i)
	{
		// If mouse clicked the button and button is not
		// taken by player or opponent return the color
		if (m_buttons[i].getGlobalBounds().contains(mousePos) && !m_button_is_taken[i])
		{
			m_click.play(); // Play sound when clicked on a legit button
			// Clear the previous taken button of the player
			for (int j = 0; j < COLORS_AMOUNT; ++j)
				if (j != m_opponents_button_index && m_button_is_taken[j])
					m_button_is_taken[j] = false;

			// Take the button for the player
			m_button_is_taken[i] = true;
			return m_buttons[i].getFillColor();
		}
	}
	return std::nullopt;
}

void Ui::handleOpponent(const sf::Color& color)
{
	m_button_is_taken[m_opponents_button_index] = false;
	for (int i = 0; i < COLORS_AMOUNT; ++i)
	{
		if (m_color_arr[i] == color)
		{
			m_button_is_taken[i] = true;
			m_opponents_button_index = i;
			return;
		}
	}
}

std::pair<sf::Color, sf::Color> Ui::takenColors() const
{
	std::vector<sf::Color> colors;
	for (size_t i = 0; i < COLORS_AMOUNT; ++i)
		if (m_button_is_taken[i])
			colors.emplace_back(m_buttons[i].getFillColor());

	return std::make_pair(colors[0], colors[1]);
}

void Ui::setCapturedAmount(const std::pair<size_t, size_t> captured)
{
	m_captured.first = static_cast<float>(captured.first) * ONE_TILE_CAPTURED * 100.f;
	m_captured.second = static_cast<float>(captured.second) * ONE_TILE_CAPTURED * 100.f;
}

const std::pair<size_t, size_t> Ui::getCapturedAmount() const
{
	return std::pair<size_t, size_t>(static_cast<size_t>(m_captured.first), static_cast<size_t>(m_captured.second));
}

const std::vector<sf::Color>& Ui::getColorArr() const
{
	return m_color_arr;
}

void Ui::resetTakenButtons(const sf::Color& opponentColor, const sf::Color& playerColor)
{
	// Reset the take buttons
	std::fill(m_button_is_taken.begin(), m_button_is_taken.end(), false);

	// Set as taken for the opponent and player
	for (int i = 0; i < COLORS_AMOUNT; ++i)
	{
		if (m_color_arr[i] == opponentColor)
		{
			m_button_is_taken[i] = true;
			m_opponents_button_index = i;
		}
		else if (m_color_arr[i] == playerColor)
			m_button_is_taken[i] = true;
	}
}