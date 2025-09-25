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
  // gravity
  velocity_y -= 0.02 * timeStep;

  // displacement
  x = x + velocity_x * timeStep;
  y = y + velocity_y * timeStep;
}

// int Ball::overlap(Ball& b) {
//   // Calculate x overlap
//   double x1 = getX();
//   double width1 = width;
//   double x2 = b.getX();
//   double width2 = b.width;

//   int x_overlap = 0;
//   if (!(x1 + width1 < x2 || x2 + width2 < x1)) {
//     x_overlap = ((x1 + width1 - x2) > 0 ? x1 + width1 - x2 : x2 + width2 -
//     x1);
//   }

//   // Calculate y overlap
//   double y1 = y;
//   double h1 = height;
//   double y2 = b.y;
//   double h2 = b.height;

//   int y_overlap = 0;
//   if (!(y1 + h1 < y2 || y2 + h2 < y1)) {
//     y_overlap = ((y1 + h1 - y2) > 0 ? y1 + h1 - y2 : y2 + h2 - y1);
//   }

//   if ((x_overlap == 0) && (y_overlap == 0))
//     return NO_OVERLAP;
//   else
//     return (x_overlap > y_overlap) ? HORIZONTAL_OVERLAP : VERTICAL_OVERLAP;
// }

int Ball::overlap(Ball& b) { return NO_OVERLAP; }

// overlap function for Player
int Ball::overlap(Player& p) {
  // ball paras
  double x1 = getX();
  double w1 = width;
  double y1 = y;
  double h1 = height;

  // paddle paras
  double x2 = p.getX();
  double w2 = p.getWidth();
  double y2 = p.getY();
  double h2 = p.getHeight();

  // they only overlap when in both directions
  bool bool_x_overlaps = (x1 < x2 + w2 && x1 + w1 > x2);
  bool bool_y_overlaps = (y1 < y2 + h2 && y1 + h1 > y2);

  double x_overlap = 0;
  double y_overlap = 0;

  if (bool_x_overlaps && bool_y_overlaps) {
    x_overlap = std::min(x1 + w1 - x2, x2 + w2 - x1);
    y_overlap = std::min(y1 + h1 - y2, y2 + h2 - y1);
  }

  if ((x_overlap == 0.0) && (y_overlap == 0.0))
    return NO_OVERLAP;
  else
    return (x_overlap > y_overlap) ? HORIZONTAL_OVERLAP : VERTICAL_OVERLAP;
}

// bounce function
void Ball::bounce(Ball arr[], int ballCount, Player player) {
  // check collision with walls
  // Right wall bounce
  if (x + width >= WIDTH - 1) {
    velocity_x = -velocity_x;
  }

  // left wall will end the game
  //, this logic is implemented in main.cpp

  // check vertical
  if (y <= 0 || y + height >= HEIGHT - 1) {
    velocity_y = -velocity_y;
  }

  // Check collision with paddle
  int paddleOverlap = this->overlap(player);
  if (paddleOverlap == HORIZONTAL_OVERLAP) {
    velocity_y = -velocity_y;
  } else if (paddleOverlap == VERTICAL_OVERLAP) {
    velocity_x = -velocity_x;
  }

  // // Check collision with other balls
  // for (int i = 0; i < ballCount; i++) {
  //   if (arr[i].getID() != this->id) {  // don't check itself
  //     int overlapType = this->overlap(arr[i]);
  //     if (overlapType == HORIZONTAL_OVERLAP) {
  //       // If two balls overlap horizontally, flip y-velocity
  //       this->velocity_y = -this->velocity_y;
  //     } else if (overlapType == VERTICAL_OVERLAP) {
  //       // If two balls overlap vertically, flip x-velocity (otherwise case)
  //       this->velocity_x = -this->velocity_x;
  //     }
  //   }
  // }
}

void Ball::draw(Screen& screen_to_draw_to) {
  screen_to_draw_to.addPixel(x, y, 'o');
}
