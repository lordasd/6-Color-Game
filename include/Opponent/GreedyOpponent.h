#pragma once

#include "Opponent.h"

class GreedyOpponent : public Opponent {
public:
	GreedyOpponent();
	virtual sf::Color makeMove(GameBoard& gameBoard) const override;

};