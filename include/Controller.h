#pragma once

#include <memory>
#include "TextureManager.h"
#include "Window.h"
#include "GameBoard.h"
#include "MainMenu.h"
#include "Ui.h"
#include "GameState.h"
#include "Opponent.h"
#include "RandomOpponent.h"
#include "GreedyOpponent.h"
#include "GlobalGreedyOpponent.h"

class Controller {
public:
	Controller();
	void run();
	void play();

private:
	Window m_window;
	sf::RenderWindow& m_renderWindow;
	MainMenu m_menu;
	GameState m_state;
	GameBoard m_board;
	std::unique_ptr<Opponent> m_opponent;

	void runMenu();
	void handleResult(GameBoard& gameBoard);
	std::unique_ptr<Opponent> createOpponent(const OpponentType& type) const;
};