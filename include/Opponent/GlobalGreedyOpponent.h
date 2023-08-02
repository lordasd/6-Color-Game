#pragma once

#include "Opponent.h"

class GlobalGreedyOpponent : public Opponent {
public:
	GlobalGreedyOpponent();
	virtual sf::Color makeMove(GameBoard& gameBoard) const override;

};