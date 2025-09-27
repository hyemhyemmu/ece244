//
//  Ball.cpp
//  Lab 2 Pong Game
//
//  Created by Fei Mo, 2025/9/15

#include "Ball.h"
#define BALL_WIDTH 1.0
#define BALL_HEIGHT 1.0

Ball::Ball() {}

Ball::Ball(double x, double y, double velocity_x, double velocity_y, int id) {
  this->x = x;
  this->y = y;
  this->velocity_x = velocity_x;
  this->velocity_y = velocity_y;
  this->id = id;
  this->width = BALL_WIDTH;
  this->height = BALL_HEIGHT;
}

double Ball::getX() { return x; }

int Ball::getID() { return id; }

void Ball::update() {
  // gravity
  velocity_y -= 0.02 * timeStep;

  // displacement
  x += velocity_x * timeStep;
  y += velocity_y * timeStep;
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
  double Ball_x1 = x;
  double Ball_y1 = y;
  double Ball_x2 = x + width;
  double Ball_y2 = y + height;

  double Player_x1 = p.getX();
  double Player_y1 = p.getY();
  double Player_x2 = p.getX() + p.getWidth();
  double Player_y2 = p.getY() + p.getHeight();

  // Calculate overlap amounts
  double x_overlap =
      std::min(Player_x2, Ball_x2) - std::max(Player_x1, Ball_x1);
  double y_overlap =
      std::min(Player_y2, Ball_y2) - std::max(Player_y1, Ball_y1);

  // Check if there's actual overlap
  if (x_overlap >= 0.0 && y_overlap >= 0.0) {
    // If y_overlap equals ball height, it's horizontal overlap
    if (y_overlap == height) {
      return HORIZONTAL_OVERLAP;
    }
    // Otherwise, it's vertical overlap
    return VERTICAL_OVERLAP;
  } else {
    return NO_OVERLAP;
  }
}

// bounce function
void Ball::bounce(Ball arr[], int ballCount, Player player) {
  // Check collision with paddle first (like reference answer)
  if (overlap(player) == VERTICAL_OVERLAP) {
    velocity_y *= -1.0;
  } else if (overlap(player) == HORIZONTAL_OVERLAP) {
    velocity_x *= -1.0;
  }

  // check collision with walls
  // Right wall bounce
  if (x >= WIDTH - 1.0) {
    velocity_x *= -1.0;
  }

  // left wall will end the game
  //, this logic is implemented in main.cpp

  // check vertical
  if ((y <= 0.0) || (y >= HEIGHT - 1.0)) {
    velocity_y *= -1.0;
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
