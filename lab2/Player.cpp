//
//  Player.cpp
//  Lab 2 Pong Game
//
//  Created by Fei Mo, 2025/9/15

#include "Player.h"

Player::Player() {}

Player::Player(double x, double y, int height) {
  this->x = x;
  this->y = y;
  this->height = height;
  this->width = 1;
}

double Player::getX() { return x; }

double Player::getY() { return y; }

int Player::getHeight() { return height; }

int Player::getWidth() { return width; }

void Player::decreaseHeight(int delta_to_decrease_by) {
  int newHeight = height - delta_to_decrease_by;
  height = (newHeight < 3) ? 3 : newHeight;
}

void Player::update(char c) {
  if (c == 'A') {  // up
    y += 2;

    if (y + height > HEIGHT - 1) {
      y = HEIGHT - 1 - height;  // up max
    }
  } else if (c == 'B') {  // down
    y -= 2;

    if (y < 0) {
      y = 0;  // down max
    }
  }
}

void Player::draw(Screen& screen_to_draw_to) {
  for (int j = y; j < y + height; ++j) {
    screen_to_draw_to.addPixel(x, j, '#');
  }
}
