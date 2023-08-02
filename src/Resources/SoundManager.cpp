#include "SoundManager.h"
#include <iostream>

SoundManager& SoundManager::instance()
{
	static SoundManager soundInstance;
	return soundInstance;
}

SoundManager::SoundManager()
{
	try {
		if (!m_click.loadFromFile("click.wav"))
			throw std::runtime_error("Can't load click.wav");
	}
	catch (const std::exception& e) {
		std::cerr << "File loading error: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

const sf::SoundBuffer& SoundManager::getClick() const
{
	return m_click;
}