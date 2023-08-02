#pragma once

// Window size
const unsigned int WIDTH = 700;
const unsigned int HEIGHT = 800;

// Board size
const size_t BOARD_SIZE = 20U;
const float BOARD_WIDTH = 487.5f;

// Hexagon
const size_t HEXAGON_SHAPE = 6U;

// Button
const sf::Vector2f BUTTON_SIZE(50.f, 50.f);

// Colors
const int COLORS_AMOUNT = 6;
const sf::Color Orange(255, 152, 0);

// One tile captured
const float ONE_TILE_CAPTURED = 1.f / (BOARD_SIZE * BOARD_SIZE);

// Opponent starting index
const int OPPONENT_STRT = BOARD_SIZE - 1;

// Player starting index
const int PLAYER_STRT = (BOARD_SIZE - 1) * BOARD_SIZE;