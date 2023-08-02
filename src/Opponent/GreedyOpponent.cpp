#include "GreedyOpponent.h"

GreedyOpponent::GreedyOpponent()
	:  Opponent(OpponentType::Greedy) {}

sf::Color GreedyOpponent::makeMove(GameBoard& gameBoard) const
{
    const auto& availableColors = gameBoard.getColorArr();
    const auto& colors = gameBoard.takenColors();

    std::map<sf::Color, int, ColorComparator> colorCount;

    // Initialize colors mapping
    for (size_t i = 0; i < COLORS_AMOUNT; ++i)
        colorCount.emplace(availableColors[i], 0);

    // Reset visited
    gameBoard.unVisitNodes();

    // Count colors of neighbors
    gameBoard.countColorsForOpponent(colors, colorCount);

    sf::Color mostCommonColor = colors.second; // Default color in case no valid neighbors are found
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