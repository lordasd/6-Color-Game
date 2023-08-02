#pragma once

#include <SFML/Graphics.hpp>
#include "GameBoard.h"
#include "Color.h"
#include <map>

enum class OpponentType { Random, Greedy, Smart, None};

class Opponent {
public:
	Opponent() = default;
	Opponent(const OpponentType& type);
	virtual sf::Color makeMove(GameBoard& gameBoard) const = 0;

private:
	OpponentType m_type;
};