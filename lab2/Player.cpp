//
//  Player.cpp
//  Lab 2 Pong Game
//
//  Created by Fei Mo, 2025/9/15

#include "Player.h"
#define PLAYER_WIDTH 1
#define MIN_HEIGHT 3

Player::Player() {}

Player::Player(double x, double y, int height) {
  this->x = x;
  this->y = y;
  this->height = height;
  this->width = PLAYER_WIDTH;
}

double Player::getX() { return x; }

double Player::getY() { return y; }

int Player::getHeight() { return height; }

// width is a private variable,
// so just return default value
int Player::getWidth() { return PLAYER_WIDTH; }

void Player::decreaseHeight(int delta_to_decrease_by) {
  int new_height = getHeight() - delta_to_decrease_by;
  height = std::max(new_height, MIN_HEIGHT);
}

// update paddle y-location based on input char
void Player::update(char c) {
  if (c == 'A') {  // up
    y += 2.0;
  } else if (c == 'B') {  // down
    y -= 2.0;
  }

  // Apply boundary constraints
  if (y < 0.0) {
    y = 0.0;  // bottom boundary
  }
  if (y + height > HEIGHT - 1) {
    y = HEIGHT - 1 - height;  // top boundary
  }
}

void Player::draw(Screen& screen_to_draw_to) {
 for (int i = 0; i < getHeight(); i++) {
    for (int j = 0; j < getWidth(); j++) {
      screen_to_draw_to.addPixel(x + j, y + i, '#');
    }
  }}
