#pragma once

#include <SFML/Audio.hpp>

class SoundManager {
public:
	static SoundManager& instance();
	~SoundManager() = default;
	SoundManager(const SoundManager&) = delete;
	void operator=(const SoundManager&) = delete;

	const sf::SoundBuffer& getClick() const;

private:
	SoundManager();

	sf::SoundBuffer m_click;
};