#include "GlobalGreedyOpponent.h"

GlobalGreedyOpponent::GlobalGreedyOpponent()
	:	Opponent(OpponentType::Smart) {}

sf::Color GlobalGreedyOpponent::makeMove(GameBoard& gameBoard) const
{
    const auto& availableColors = gameBoard.getColorArr();
    const auto& takenColors = gameBoard.takenColors();

    std::map<sf::Color, int, ColorComparator> colorCount;

    // Initialize colors mapping
    for (size_t i = 0; i < COLORS_AMOUNT; ++i)
        colorCount.emplace(availableColors[i], 0);

    // Reset visited
    gameBoard.unVisitNodes();
       
    // Recursively find best color by visiting neighbors of neighbors...
    gameBoard.dfsColorCount(takenColors, colorCount);

    // Default color in case no valid neighbors are found
    sf::Color mostCommonColor = takenColors.second;
    int maxCount = 0;

    // Find the color with the highest count among the valid neighbors
    for (const auto& entry : colorCount)
    {
        if (entry.second > maxCount)
        {
            maxCount = entry.second;
            mostCommonColor = entry.first;
        }
    }

    return mostCommonColor;
}