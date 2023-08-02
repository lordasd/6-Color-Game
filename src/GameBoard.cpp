#include "GameBoard.h"
#include "Iterator.h"

GameBoard::GameBoard()
    : m_graph(), m_capuredAmount(1,1),
      m_turn(Turn::Player), m_curr_outline(sf::Color::Black),
      m_clock(sf::Clock()), m_new(TextureManager::instance().getNew())
{
    // Initialize board
    createGraph();
    assignNeighbors();
    setBoardStartingColors();

    // Create Ui object and get starting colors of the players
    m_ui = Ui(m_graph.getNode(BOARD_SIZE - 1).m_node.getColor(),
              m_graph.getNode((BOARD_SIZE - 1) * BOARD_SIZE).m_node.getColor());
    
    m_new.setPosition(270.f, HEIGHT - 90.f);
    m_clock.restart();
}

void GameBoard::createGraph()
{
    // Calculate the hexagon radius based on the board and window size
    float HexagonRadius = static_cast<float>(BOARD_WIDTH) / (static_cast<float>(BOARD_SIZE) * sqrt(3.f));
    float hexagonWidth = HexagonRadius * sqrt(3.f);
    float hexagonHalfWidth = HexagonRadius * sqrt(3.f) / 2.f;

    // Calculate the starting position of the hexagons
    float startingPosX = ((WIDTH - (BOARD_SIZE * hexagonWidth)) / 2.0f) - hexagonWidth/3.f;
    float startingPosY = 15.f;

    // Offest when moving the hexagons
    float horizontalOffset = hexagonWidth;
    float verticalOffset = HexagonRadius * 1.5f;

    // Set borders around the board
    setBoardBorders(HexagonRadius, startingPosX);

    // Position of a hexagon as a float vector
    sf::Vector2f hexagon_position(startingPosX, startingPosY);

    // Boolian check to move left/right
    bool left = false, right = true;

    // Create all nodes for the graph
    for (size_t i = 0; i < BOARD_SIZE; ++i, hexagon_position.y += verticalOffset)
    {
        for (size_t j = 0; j < BOARD_SIZE; ++j, hexagon_position.x += horizontalOffset)
        {
            // Add a node to the graph
            m_graph.insert(Node<Hexagon>(Hexagon(hexagon_position, HexagonRadius)));

            // Set starting point for player and opponent
            if (i == 0 && j == BOARD_SIZE - 1)
                m_graph.getNode(i * BOARD_SIZE + j).m_node.setOccupied(Occupied::Opponent);
            else if (i == BOARD_SIZE - 1 && j == 0)
                m_graph.getNode(i * BOARD_SIZE + j).m_node.setOccupied(Occupied::Player);
        }

        // Move hexagons to the right or left
        if (right)
        {
            hexagon_position.x = startingPosX + (hexagonHalfWidth);
            right = false;
            left = true;
        }
        else if (left)
        {
            hexagon_position.x = startingPosX;
            left = false;
            right = true;
        }
    }
}

void GameBoard::assignNeighbors()
{
    // Iterate over the nodes in the graph
    for (size_t row = 0; row < BOARD_SIZE; ++row)
    {
        for (size_t col = 0; col < BOARD_SIZE; ++col)
        {
            Node<Hexagon>& currentNode = m_graph.getNode(row * BOARD_SIZE + col);

            // Add the neighbors based on the pattern
            // Common neighbors for both even and odd rows
            if (col > 0) // Left
                currentNode.insert(&m_graph.getNode(row * BOARD_SIZE + col - 1));
            if (col < BOARD_SIZE - 1) // Right
                currentNode.insert(&m_graph.getNode(row * BOARD_SIZE + col + 1));
            if (row > 0) // Top
                currentNode.insert(&m_graph.getNode((row - 1) * BOARD_SIZE + col));
            if (row < BOARD_SIZE - 1) // Bottom
                currentNode.insert(&m_graph.getNode((row + 1) * BOARD_SIZE + col));

            // Unique neighbors for even rows
            if (row % 2 == 0)
            {
                if (row > 0 && col > 0) // Top-left
                    currentNode.insert(&m_graph.getNode((row - 1) * BOARD_SIZE + col - 1));
                if (row < BOARD_SIZE - 1 && col > 0) // Bottom-left
                    currentNode.insert(&m_graph.getNode((row + 1) * BOARD_SIZE + col - 1));
            }

            // Unique neighbors for odd rows
            if (row % 2 != 0)
            {
                if (row > 0 && col < BOARD_SIZE - 1) // Top-right
                    currentNode.insert(&m_graph.getNode((row - 1) * BOARD_SIZE + col + 1));
                if (row < BOARD_SIZE - 1 && col < BOARD_SIZE - 1) // Bottom-right
                    currentNode.insert(&m_graph.getNode((row + 1) * BOARD_SIZE + col + 1));
            }
        }
    }
}

void GameBoard::setBoardStartingColors()
{
    // Set random color and default outline color
    for (auto& node : m_graph)
    {
        node.m_node.setColor(getRandomColor());
        node.m_node.setOutlineColor(sf::Color::Black);
    }

    // Get starting nodes
    auto& player_point = m_graph.getNode(PLAYER_STRT);
    auto& enemy_point = m_graph.getNode(OPPONENT_STRT);

    /* While player and oponenet have similar colors and both of them
    have similar colors to their neighbors, change them(randomize) */
    while (player_point.m_node.getColor() == enemy_point.m_node.getColor() ||
        hasMatchingNeighborColor(player_point) ||
        hasMatchingNeighborColor(enemy_point))
    {
        player_point.m_node.setColor(getRandomColor());
        enemy_point.m_node.setColor(getRandomColor());
    }

    // Set text to display percentage of captured tiles
    m_ui.setCapturedAmount(countCapturedTiles());
}

bool GameBoard::hasMatchingNeighborColor(const Node<Hexagon>& node) const
{
    // Nodes current color
    const sf::Color currentColor = node.m_node.getColor();

    // Compare nodes color to neighbors color
    for (auto neighbor : node.m_neighbors)
        if (neighbor->m_node.getColor() == currentColor)
            return true;
    return false;
}

void GameBoard::drawBoard(sf::RenderWindow& window)
{
    sf::Time elapsed = m_clock.getElapsedTime();

    // Set opposite outline color clock if 0.5 seconds have passed
    if (elapsed.asSeconds() >= 0.5f)
    {  
        if (m_turn == Turn::Player)
        {
            if (m_curr_outline == sf::Color::Black)
                m_curr_outline = sf::Color::White;
            else
                m_curr_outline = sf::Color::Black;
        }
        // Reset clock for next set
        m_clock.restart();
    }

    // Draw board - shapes
    for (auto& node : m_graph)
    {
        if (node.m_node.getOccupied() == Occupied::Player)
            node.m_node.outlineColorSwitch(m_curr_outline, elapsed);

        window.draw(node.m_node.getHexagon());
    }

    // Draw borders for the board
    for (auto& border : m_aroundBoard)
        window.draw(border);

    // Draw exit button
    window.draw(m_new);

    // Draw the UI
    m_ui.drawUi(window);
}

void GameBoard::handleClick(const sf::Vector2f& mousePos, GameState& state)
{
    if (m_new.getGlobalBounds().contains(mousePos))
    {
        state = GameState::Menu;
        return;
    }
    
    // Get clicked color
    auto color = m_ui.handleClick(mousePos);
    
    // If player clicks on a button, do changes
    if (color.has_value())
    {
        colorBoard(color.value());
        m_turn = Turn::Opponent;
    }
}

void GameBoard::handleOpponent(const sf::Color color)
{
    // Change taken button by the opponent
    m_ui.handleOpponent(color);
    // Color board for the opponent choice
    colorBoard(color);
    // Players next turn players
    m_turn = Turn::Player;
}

std::pair<sf::Color, sf::Color> GameBoard::takenColors() const
{
    return m_ui.takenColors();
}

Turn GameBoard::getTurn() const
{
    return m_turn;
}

bool GameBoard::isWin() const
{
    const auto& stats = m_ui.getCapturedAmount();
  
    if (m_turn == Turn::Opponent && stats.first >= 50)
        return true; // Player won
    else if (m_turn == Turn::Player && stats.second >= 50)
        return true; // Opponent won
    return false;
}

const std::vector<sf::Color>& GameBoard::getColorArr() const
{
    return m_ui.getColorArr();
}

void GameBoard::colorBoard(const sf::Color& color)
{
    // Initialize visited flag for all nodes
    unVisitNodes();

    // Search for player's cells
    for (auto& node : m_graph)
    {
        if (m_turn == Turn::Player)
        {
            // If a cell is occupied by a player and has not been visited
            if (node.m_node.getOccupied() == Occupied::Player && !node.visited && node.m_node.getColor() != color)
            {
                // Set our color
                node.m_node.setColor(color);

                // Capture connected nodes with the same color using DFS
                captureConnectedNodes(node, color);
            }
        }
        else if (m_turn == Turn::Opponent)
        {
            // If a cell is occupied by a player and has not been visited
            if (node.m_node.getOccupied() == Occupied::Opponent && !node.visited && node.m_node.getColor() != color)
            {
                // Set our color
                node.m_node.setColor(color);

                // Capture connected nodes with the same color using DFS
                captureConnectedNodes(node, color);
            }
        }
    }

    // Set text to display percentage of captured tiles
    m_ui.setCapturedAmount(countCapturedTiles());
}

void GameBoard::captureConnectedNodes(Node<Hexagon>& node, const sf::Color& color)
{
    // Mark the current node as visited
    node.visited = true;

    for (auto& neighbor : node.m_neighbors)
    {
        if (neighbor->m_node.getOccupied() == Occupied::None &&
            neighbor->m_node.getColor() == color && !neighbor->visited)
        {
            // Capture the node and recursively capture its connected nodes
            if (m_turn == Turn::Player)
            {
                neighbor->m_node.setOccupied(Occupied::Player);
                m_capuredAmount.first++;
            }
            else if (m_turn == Turn::Opponent)
            {
                neighbor->m_node.setOccupied(Occupied::Opponent);
                m_capuredAmount.second++;
            }
            neighbor->m_node.setColor(color);
            captureConnectedNodes(*neighbor, color);
        }
    }
}

void GameBoard::setBoardBorders(float HexagonRadius, float startingPosX)
{
    // Set offsets to change the borders depending on the size of the board
    float offsetX{}, offsetY{};
    if constexpr(BOARD_SIZE > 15)
    {
        if constexpr(BOARD_SIZE >= 30)
            offsetX = 1;
        else
            offsetX = 4;
        offsetY = 21;
    }
    else if constexpr (BOARD_SIZE <= 15)
    {
        offsetX = 7;
        if constexpr (BOARD_SIZE > 7)
            offsetY = 5;
    }

    // Create 4 rectangles to cover the hexagons and create a board
    m_aroundBoard.emplace_back(sf::RectangleShape(sf::Vector2f(startingPosX + HexagonRadius * sqrt(3.f) / 2.f + offsetX, HEIGHT))); // left
    m_aroundBoard.back().setPosition(0.f, 0.f);
    
    m_aroundBoard.emplace_back(sf::RectangleShape(sf::Vector2f(startingPosX + HexagonRadius * sqrt(3.f) / 2.f + offsetX, HEIGHT))); // right
    m_aroundBoard.back().setPosition(WIDTH - startingPosX - (HexagonRadius * sqrt(3.f) / 2.f + offsetX), 0.f);

    m_aroundBoard.emplace_back(sf::RectangleShape(sf::Vector2f(WIDTH, 43.f - offsetY))); // up
    m_aroundBoard.back().setPosition(0.f, 0.f);

    m_aroundBoard.emplace_back(sf::RectangleShape(sf::Vector2f(WIDTH, 363.f))); // down
    m_aroundBoard.back().setPosition(0.f, HEIGHT - 363.f);

    // Set shapes and outlines color
    for (auto& border : m_aroundBoard)
    {
        border.setFillColor(sf::Color(128, 203, 196));
        border.setOutlineThickness(1);
        border.setOutlineColor(sf::Color::Black);
    }
}

const std::pair<size_t, size_t> GameBoard::countCapturedTiles() const
{
    return m_capuredAmount;
}

void GameBoard::unVisitNodes()
{
    for (auto& node : m_graph)
        node.visited = false;
}

void GameBoard::countColorsForOpponent(const std::pair<sf::Color, sf::Color>& colors, std::map<sf::Color, int, ColorComparator>& colorCount)
{
    // For each node which is occupied by the opponent
    for (const auto& node : m_graph)
    {
        if (node.m_node.getOccupied() == Occupied::Opponent)
        {
            // Go over his neighbors and search
            for (const auto& neighbor : node.m_neighbors)
            {
                // Not visited yet, not owned by anyone and color isn't taken
                if (neighbor->m_node.getOccupied() == Occupied::None &&
                    !neighbor->visited && neighbor->m_node.getColor() != colors.first && neighbor->m_node.getColor() != colors.second)
                {
                    neighbor->visited = true;
                    colorCount[neighbor->m_node.getColor()] += 1;
                }
            }
        }
    }
}

void GameBoard::dfsColorCount(const std::pair<sf::Color, sf::Color>& takenColors, std::map<sf::Color, int, ColorComparator>& colorCount)
{
    // For each node which is occupied by the opponent
    for (auto& node : m_graph)
    {
        if (node.m_node.getOccupied() == Occupied::Opponent && !node.visited)
        {
            node.visited = true;
            // Count colors of neighbors and neighbors of neighbors recursively
            for (const auto& neighbor : node.m_neighbors)
            {
                auto& lastColor = neighbor->m_node.getColor();
                countColorsRecursive(*neighbor, colorCount, takenColors, lastColor);
            }
        }
    }
}

bool GameBoard::countColorsRecursive(Node<Hexagon>& node, std::map<sf::Color, int, ColorComparator>& colorCount, const std::pair<sf::Color, sf::Color>& takenColors, const sf::Color& lastColor) const
{
    // If node doesn't all the requierments, return false
    if (node.visited || node.m_node.getOccupied() != Occupied::None ||
        node.m_node.getColor() == takenColors.first || node.m_node.getColor() == takenColors.second || node.m_node.getColor() != lastColor)
    {
        return false;
    }

    // Found a color to add to the map
    if (node.m_node.getOccupied() == Occupied::None && node.m_node.getColor() == lastColor)
    {
        colorCount[node.m_node.getColor()] += 1;
        node.visited = true;
    }

    // Try to find more colors from the neighbors
    for (const auto& neighbor : node.m_neighbors)
    {
        // If fails, continue to next node
        if (!countColorsRecursive(*neighbor, colorCount, takenColors, lastColor))
            continue;

        // Also check neighbors of neighbors
        for (const auto& neighborOfNeighbor : neighbor->m_neighbors)
        {
            // If fails, continue to next node
            if (!countColorsRecursive(*neighborOfNeighbor, colorCount, takenColors, lastColor))
                continue;
        }
    }
    return true;
}

void GameBoard::resetBoard()
{
    // Set all tiles to unoccupied
    for (auto& node : m_graph)
        node.m_node.setOccupied(Occupied::None);

    // First turn will be players
    m_turn = Turn::Player;

    // Reset amount of starting captured tiles
    m_capuredAmount.first = m_capuredAmount.second = 1;
    
    // Randomize tile colors
    setBoardStartingColors();

    auto opponentIt = m_graph.begin() + OPPONENT_STRT;
    auto playerIt = m_graph.begin() + PLAYER_STRT;

    // Set occupation for the players
    opponentIt->m_node.setOccupied(Occupied::Opponent);
    playerIt->m_node.setOccupied(Occupied::Player);

    // Set the taken buttons
    if(opponentIt != m_graph.end() && playerIt != m_graph.end())
        m_ui.resetTakenButtons(opponentIt->m_node.getColor(), playerIt->m_node.getColor());
}