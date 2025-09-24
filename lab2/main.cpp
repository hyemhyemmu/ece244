//
//  main.cpp
//  Lab 2 Pong Game
//
//  Created by Nathan Hung on 2024-09-11.
//  Modified by Salma Emara on 2024-09-11
//  Copyright © 2024 Nathan Hung. No rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <string>

#include "Ball.h"
#include "Globals.h"
#include "Player.h"
#include "Screen.h"
#include "io.h"

int main() {
  int score = 0;
  bool gameEnded = false;
  std::string messageToPutOnScreen;

  std::chrono::steady_clock::time_point begin_time =
      std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point now_time;
  Screen screen = Screen();

  int ballCount = 0;
  const int max_ballCount = 5;

  Ball balls_array[max_ballCount];

  balls_array[0] = Ball(30.0, 30.0, 1.7, 0, ballCount);
  ballCount++;

  Player player = Player(0, 5, 10);

  while (!gameEnded) {
    // -------------------------

    for (int step = 0; step < simulation_fps; step++) {
      // Handle input
      char input = get_input();
      switch (input) {
        case ('q'):
          gameEnded = true;
          break;
        case ('A'):  // up
        case ('B'):  // down
          player.update(input);
          break;
        default:
          // No input or other input, paddle stays in place
          break;
      }

      if (gameEnded) break;

      // update balls
      for (int i = 0; i < ballCount; i++) {
        balls_array[i].update();
      }

      // array to track previous overlap status for collision detection
      bool ball_was_overlapping[max_ballCount] = {false};

      // if bounce with paddle
      for (int i = 0; i < ballCount; i++) {
        bool currently_overlapping =
            (balls_array[i].overlap(player) != NO_OVERLAP);

        // only score if ball is overlapping now but wasn't overlapping before
        if (currently_overlapping && !ball_was_overlapping[i]) {
          score++;
          ball_was_overlapping[i] = true;

          // Every 2 hits, decrease paddle size by 1
          if (score % 2 == 0) {
            player.decreaseHeight(1);
          }

          // Every 5 hits, add a new ball (max 5 balls)
          if (score % 5 == 0 && ballCount <= max_ballCount) {
            balls_array[ballCount] = Ball(30.0, 30.0, 0.9, 0, ballCount);
            ball_was_overlapping[ballCount] = false;
            ballCount++;
          }
        }

        // Update overlap status for next frame
        ball_was_overlapping[i] = currently_overlapping;
      }

      // bounce with balls
      for (int i = 0; i < ballCount; i++) {
        balls_array[i].bounce(balls_array, ballCount, player);

        // Check if ball hit left wall (game ends)
        if (balls_array[i].getX() <= 0) {
          gameEnded = true;
          break;
        }
      }

      if (gameEnded) break;
    }

    // Draw all game objects after simulation steps are complete
    for (int i = 0; i < ballCount; i++) {
      balls_array[i].draw(screen);
    }
    player.draw(screen);

    // -------------------------
    messageToPutOnScreen = "Your score is: " + std::to_string(score);
    screen.update(messageToPutOnScreen);

    // wait until 1/fps seconds
    while (std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now() - begin_time)
               .count() < (long int)milliseconds_per_frame) {
    }

    begin_time = std::chrono::steady_clock::now();
  }
  messageToPutOnScreen = "Game over. Your score is: " + std::to_string(score);
  screen.update(messageToPutOnScreen);

  return 0;
}
