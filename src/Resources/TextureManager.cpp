#include "TextureManager.h"
#include <iostream>

TextureManager& TextureManager::instance()
{
	static TextureManager textInstance;
	return textInstance;
}

TextureManager::TextureManager()
{
    try {
        if (!m_x.loadFromFile("x.png"))
            throw std::runtime_error("Failed to load x.png");
        if (!m_menu.loadFromFile("menu.png"))
            throw std::runtime_error("Failed to load menu.png");
        if (!m_random.loadFromFile("random.png"))
            throw std::runtime_error("Failed to load random.png");
        if (!m_greedy.loadFromFile("greedy.png"))
            throw std::runtime_error("Failed to load greedy.png");
        if (!m_smart.loadFromFile("smart.png"))
            throw std::runtime_error("Failed to load smart.png");
        if (!m_exit.loadFromFile("exit.png"))
            throw std::runtime_error("Failed to load exit.png");
        if (!m_win.loadFromFile("win.png"))
            throw std::runtime_error("Failed to load win.png");
        if (!m_lose.loadFromFile("lose.png"))
            throw std::runtime_error("Failed to load lose.png");
        if (!m_new.loadFromFile("new.png"))
            throw std::runtime_error("Failed to load new.png");
        if (!m_font.loadFromFile("pixelfont.otf"))
            throw std::runtime_error("Failed to load pixelfont.otf");
    }
    catch (const std::exception& e) {
        std::cerr << "File loading error: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

const sf::Texture& TextureManager::getX() const
{
    return m_x;
}

const sf::Texture& TextureManager::getMenu() const
{
    return m_menu;
}

const sf::Texture& TextureManager::getRandom() const
{
    return m_random;
}

const sf::Texture& TextureManager::getGreedy() const
{
    return m_greedy;
}

const sf::Texture& TextureManager::getSmart() const
{
    return m_smart;
}

const sf::Texture& TextureManager::getExit() const
{
    return m_exit;
}

const sf::Texture& TextureManager::getWin() const
{
    return m_win;
}

const sf::Texture& TextureManager::getLose() const
{
    return m_lose;
}

const sf::Texture& TextureManager::getNew() const
{
    return m_new;
}

const sf::Font& TextureManager::getFont() const
{
	return m_font;
}