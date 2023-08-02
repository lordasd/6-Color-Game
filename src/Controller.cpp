#include "Controller.h"

#include <iostream>

Controller::Controller()
	:	m_window(Window()),
        m_renderWindow(m_window.getRenderedWindow()),
		m_state(GameState::Menu), m_board(GameBoard())
{}

void Controller::run()
{
    try
    {
        // Game state loop
        while (m_state != GameState::Exit)
        {
            if (m_state == GameState::Menu)
                runMenu();
            else if (m_state == GameState::GamePlay)
            {
                play();
                m_board.resetBoard();
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }
}

void Controller::play()
{
    while (m_renderWindow.isOpen() && m_state == GameState::GamePlay)
    {
        for (auto event = sf::Event{}; m_renderWindow.pollEvent(event); )
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_state = GameState::Menu;
                break;
            case sf::Event::MouseButtonPressed:
                m_board.handleClick(m_renderWindow.mapPixelToCoords
                ({ event.mouseButton.x, event.mouseButton.y }), m_state);
                if (m_board.isWin())
                    m_state = GameState::Won;
                break;
            default:
                break;
            }
        }
        // Handle opponents move
        if (m_state == GameState::GamePlay && m_board.getTurn() == Turn::Opponent)
        {
            auto color = m_opponent->makeMove(m_board);
            m_board.handleOpponent(color);
            if (m_board.isWin())
                m_state = GameState::Lost;
        }

        m_renderWindow.clear();
        m_board.drawBoard(m_renderWindow);
        m_renderWindow.display();
    }

    // Show resulting screen
    if (m_state == GameState::Won || m_state == GameState::Lost)
        handleResult(m_board);
}

void Controller::runMenu()
{
    std::optional<std::pair<GameState, OpponentType>> states;

    while (m_renderWindow.isOpen() && m_state == GameState::Menu)
    {
        for (auto event = sf::Event{}; m_renderWindow.pollEvent(event); )
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_state = GameState::Exit;
                m_renderWindow.close();
                break;
            case sf::Event::MouseButtonPressed:
                states = m_menu.handleClick(m_renderWindow.mapPixelToCoords(
                                           { event.mouseButton.x, event.mouseButton.y }));
                break;
            default:
                break;
            }
        }
    
        // Check if opponent type has been selected
        if (states.has_value() &&
            states->first == GameState::GamePlay &&
            states->second != OpponentType::None)
        {
            // Create the opponent based on the selected type
            m_opponent = createOpponent(states->second);

            // Change the state to GamePlay
            m_state = states->first;
        }
        else if (states.has_value() && states->first == GameState::Exit)
            m_state = GameState::Exit;

        m_renderWindow.clear();
        m_menu.drawMenu(m_renderWindow);
        m_renderWindow.display();
    }
}

void Controller::handleResult(GameBoard& gameBoard)
{
    sf::Sprite background, exit;
    
    // Get apropriate textures
    exit.setTexture(TextureManager::instance().getExit());
    if (m_state == GameState::Won)
        background.setTexture(TextureManager::instance().getWin());
    else if(m_state == GameState::Lost)
        background.setTexture(TextureManager::instance().getLose());;

    // Set their positions in the window
    background.setPosition(165.f, 185.f);
    exit.setPosition(280.f, 450.f);

    while (m_renderWindow.isOpen() && (m_state == GameState::Won || m_state == GameState::Lost) )
    {
        for (auto event = sf::Event{}; m_renderWindow.pollEvent(event); )
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_state = GameState::Menu;
                break;
            case sf::Event::MouseButtonPressed:
                if (exit.getGlobalBounds().contains(m_renderWindow.mapPixelToCoords
                                                   ({ event.mouseButton.x, event.mouseButton.y })))
                    m_state = GameState::Menu;
                break;
            default:
                break;
            }
        }

        m_renderWindow.clear();
        gameBoard.drawBoard(m_renderWindow);
        m_renderWindow.draw(background);
        m_renderWindow.draw(exit);
        m_renderWindow.display();
    }
}

std::unique_ptr<Opponent> Controller::createOpponent(const OpponentType& type) const
{
    switch (type)
    {
    case OpponentType::Random:
        return std::make_unique<RandomOpponent>();
    case OpponentType::Greedy:
        return std::make_unique<GreedyOpponent>();
    case OpponentType::Smart:
        return std::make_unique<GlobalGreedyOpponent>();
    default:
        return nullptr;
    }
}