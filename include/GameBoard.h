#pragma once

#include <vector>
#include "Graph.h"
#include "Hexagon.h"
#include "TextureManager.h"
#include "Config.h"
#include "Ui.h"
#include "GameState.h"
#include "Color.h"

enum class Turn { Player, Opponent};

class GameBoard {
public:
	GameBoard();
	void drawBoard(sf::RenderWindow& window);
	void handleClick(const sf::Vector2f& mousePos, GameState& state);
	void handleOpponent(const sf::Color color);
	Turn getTurn() const;
	bool isWin() const;
	std::pair<sf::Color, sf::Color> takenColors() const;
	const std::vector<sf::Color>& getColorArr() const;
	const std::pair<size_t, size_t> countCapturedTiles() const;
	void unVisitNodes();
	void countColorsForOpponent(const std::pair<sf::Color, sf::Color>& colors, std::map<sf::Color, int, ColorComparator>& colorCount);
	void dfsColorCount(const std::pair<sf::Color, sf::Color>& takenColors, std::map<sf::Color, int, ColorComparator>& colorCount);
	bool countColorsRecursive(Node<Hexagon>& node, std::map<sf::Color, int, ColorComparator>& colorCount, const std::pair<sf::Color, sf::Color>& takenColors, const sf::Color& lastColor) const;
	void resetBoard();
		
private:
	Graph<Hexagon> m_graph;
	Ui m_ui;
	std::vector<sf::RectangleShape> m_aroundBoard;
	Turn m_turn;
	sf::Color m_curr_outline;
	sf::Clock m_clock;
	sf::Sprite m_new;
	// Player, Opponent capured tiles
	std::pair<size_t, size_t> m_capuredAmount;

	void createGraph();
	void assignNeighbors();
	void setBoardStartingColors();
    bool hasMatchingNeighborColor(const Node<Hexagon>& node) const;

	void colorBoard(const sf::Color& color);
	void captureConnectedNodes(Node<Hexagon>& node, const sf::Color& color);
	void setBoardBorders(float HexagonRadius, float startingPosX);

};