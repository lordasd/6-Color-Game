#pragma once

#include "Opponent.h"

class RandomOpponent : public Opponent {
public:
	RandomOpponent();
	virtual sf::Color makeMove(GameBoard& gameBoard) const override;
private:

};