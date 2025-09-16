//
//  Ball.cpp
//  Lab 2 Pong Game
//
//  Created by Fei Mo, 2025/9/15

#include "Ball.h"

Ball::Ball() {}

Ball::Ball(double x, double y, double velocity_x, double velocity_y, int id) {
  this->x = x;
  this->y = y;
  this->velocity_x = velocity_x;
  this->velocity_y = velocity_y;
  this->id = id;
  this->width = 1.0;
  this->height = 1.0;
}

double Ball::getX() { return x; }

int Ball::getID() { return id; }

void Ball::update() {
  velocity_y = velocity_y - 0.02 * timeStep;  // gravity

  // displacement
  x = x + velocity_x * timeStep;
  y = y + velocity_y * timeStep;
}

// TODO: overlap function
