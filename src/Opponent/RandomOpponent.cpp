#include "RandomOpponent.h"

RandomOpponent::RandomOpponent()
	:	Opponent(OpponentType::Random) {}

sf::Color RandomOpponent::makeMove(GameBoard& gameBoard) const
{
    const auto& colors = gameBoard.takenColors();

    // Return random color from the colors bellow
    while (true)
    {
        const auto& color = getRandomColor();

        if (color == sf::Color::Red && colors.first != sf::Color::Red && colors.second != sf::Color::Red)
            return sf::Color::Red;
        else if (color == sf::Color::Blue && colors.first != sf::Color::Blue && colors.second != sf::Color::Blue)
            return sf::Color::Blue;
        else if (color == sf::Color::Green && colors.first != sf::Color::Green && colors.second != sf::Color::Green)
            return sf::Color::Green;
        else if (color == sf::Color::Yellow && colors.first != sf::Color::Yellow && colors.second != sf::Color::Yellow)
            return sf::Color::Yellow;
        else if (color == sf::Color::Cyan && colors.first != sf::Color::Cyan && colors.second != sf::Color::Cyan)
            return sf::Color::Cyan;
        else if (color == sf::Color::Magenta && colors.first != sf::Color::Magenta && colors.second != sf::Color::Magenta)
            return sf::Color::Magenta;
    }
    
    return sf::Color::White;
}
