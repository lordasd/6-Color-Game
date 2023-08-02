#pragma once

#include <SFML/Graphics.hpp>

class TextureManager{
public:
	static TextureManager& instance();
	~TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	void operator=(const TextureManager&) = delete;

	const sf::Texture& getX() const;
	const sf::Texture& getMenu() const;
	const sf::Texture& getRandom() const;
	const sf::Texture& getGreedy() const;
	const sf::Texture& getSmart() const;
	const sf::Texture& getExit() const;
	const sf::Texture& getWin() const;
	const sf::Texture& getLose() const;
	const sf::Texture& getNew() const;
	const sf::Font& getFont() const;

private:
	TextureManager();

	sf::Texture m_x;
	sf::Texture m_menu;
	sf::Texture m_random;
	sf::Texture m_greedy;
	sf::Texture m_smart;
	sf::Texture m_exit;
	sf::Texture m_win;
	sf::Texture m_lose;
	sf::Texture m_new;
	sf::Font m_font;
};