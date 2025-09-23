Pong Game
In this lab, you will implement the Pong Game with a single player controlling a paddle to hit incoming balls. The player moves the paddle up or down to prevent the balls from hitting the wall behind them. Each successful hit increases the player's score by 1. If the player misses a ball, the game is over. As the score increases, the paddle size decreases, and the number of balls increases, making the game progressively harder.

Pong Game Program Overview
The Pong Game program implements a simplified version of the classic Pong game using object-oriented programming concepts in C++. The game will feature three main classes: Ball, Player and Screen, along with the main function to drive the game loop.


Ball Class in Ball.cpp and Ball.h: This class will represent the balls in the game. It includes the properties like x and y coordinates, velocity_x and velocity_y denoting the velocity (not speed) in the x and y direction respectively, width, height and id of a ball in the game. The ball's movement will be updated in each time step of the game loop based on these attributes.

Player Class in Player.cpp and Player.h: This class is responsible for controlling the paddle, which can move up or down with the objective of hitting the ball. The Player class will manage the paddle's position (x and y coordinates), size (width and height) and speed at which the paddle moves. Every 2 hits, the height of the paddle will shrink by 1 unit till it reaches a height of 3, adding an additional layer of difficulty.

Screen Class in Screen.cpp and Screen.h: The Screen class will handle the display of the game. It is responsible for printing the current state of the game, including the positions of the ball, the paddle, and the score, on the console/terminal. The class is implemented for you. You are not required to understand it. You will use the Screen class to print the balls and the paddle. The class uses some functions implemented in io.cpp and declared in io.h in file. Do not change anything in these files.

Main Function in main.cpp: The main function will control the game loop, initializing the game components, taking input from the user and updating the game state on each iteration. It will manage the game's flow by checking for collisions between the paddle and the balls, updating the score, and ending the game when the player misses a ball.

As the player hits the ball, their score increases, the paddle size decreases (if conditions are satisfied), and more balls are introduced into the game (if conditions are satisfied). The challenge increases with time, testing the player's reflexes and strategy. If the player misses a ball, the game ends, and the final score is displayed.

Problem Statement
In this lab, you are tasked with implementing the simplified version of the Pong game program. The objective is to simulate a player controlling a paddle that moves vertically as the user moves to hit balls, earning points as the game progresses.

In order to do so, you will implement the methods of the class Ball, as defined in Ball.h, Player, as defined in Player.h. You will also implement the main function, which "plays" the move indicated by a player's input. The remainder of this section describes: (1) the Player class and its methods, (2) the Ball class and its methods, (3) the main function that implements the game loop.

The Player Class
The dynamics of the paddle in the Pong game is represented by an instance of the Player class. The definition of this class appears in the file Player.h, which is released with the assignment. You may NOT modify this file to add to or delete from its content. Modifying the file often results in a mark of zero for the assignment. The class contains the following data members:

x and y coordinate of the paddle in the canvas/game window, which is managed by the Screen class. As shown in Fig.2, the value of x ranges between 0 and  WIDTH - 1 and y ranges between 0 and HEIGHT - 1. The macros WIDTH and HEIGHT are defined in Globals.h file, which is also part of the assignment release. You may NOT modify this file to add to or delete from its content.
width and height are the width and height of the paddle. The width should be set to 1 unit.

The class contains the following function members that you will implement:

default constructor does nothing
another constructor sets the x and y coordinates, height and width
getX() returns the value of the x coordinate
getY() returns the value of the y coordinate
getHeight() returns the height of the paddle
getWidth() returns the width of the paddle
decreaseHeight(int delta_to_decrease_by) decreases the height by delta_to_decrease_by amount. The minimum height is 3.
update(char c) updates the y coordinates of the paddle according to the value of c. If the user presses the up arrow key (represented by c == 'A'), the y coordinate should increase by the value of 2. Conversely, if the down arrow key is pressed (c == 'B'), the y coordinate should decrease by the value of 2. The paddle should not fall below the floor or above the ceiling. Hence, you should limit the y-coordinate to the minimum y or the maximum y, respectively, if needed. In Fig. 2, we show the paddle x and y coordinates with respect to the game window to help you figure out the allowed range of the y coordinate.
draw(Screen& screen_to_draw_to) renders the paddle on the game window by invoking addPixel on the screen_to_draw_to object (an instance of the Screen class). The addPixel function prototype is void addPixel(double x, double y, char symbol), where x and y are the coordinates of the pixel/point we want to draw, and symbol is #. To draw the paddle, call addPixel repeatedly on each pixel/point of the paddle. In Fig. 3, we show the game printed on the terminal. The paddle is shown with #.
Implement Player.cpp first when you start coding. 


The Ball Class
The dynamics of the balls in the Pong game is represented by an instance of the Ball class. The definition of this class appears in the file Ball.h, which is released with the assignment. You may NOT modify this file to add to or delete from its content. Modifying the file often results in a mark of zero for the assignment. The class contains the following data members:

x and y coordinate of the ball in the canvas/game window, which is managed by the Screen class. The value of x ranges between 0 and WIDTH - 1 and y ranges between 0 and  HEIGHT - 1. The macros WIDTH and HEIGHT are defined in Globals.h file, which is also part of the assignment release. You may NOT modify this file to add to or delete from its content.
width and height are the width and height of the ball, should be set to 1 unit for all balls.
velocity_x and velocity_y are the velocities of the ball in the x and y direction. velocity_x and velocity_y are the number of units a ball moves in the x direction and y direction (respectively) in one time step or iteration. For example, if the velocity_x is negative, this means the ball's x position is decreasing by velocity_x's magnitude every time step. The time step is defined in Globals.h as the macro timeStep. Decreasing x coordinates means the ball is moving to the left. Decreasing y coordinate means the ball is moving down as illustrated in Fig. 2.
id is a unique identifier for each ball in the game. It can be set to the ball's number. It will be used to check if a ball is colliding with another ball.
 

The class contains the following function members that you will implement:

default constructor that does nothing
another constructor that sets the x and y coordinates, height, width, velocity_x, velocity_y and id. height and width are 1.
getX() returns the value of the x coordinate
getID() returns the value of the id of the ball
update() would first account for the change in the velocity in the y direction due to gravity, then updates the x and y coordinates of the ball for one time step timeStep, where timeStep is a variable defined in Globals.h. The velocity in the y direction becomes more negative with acceleration of 0.02 units per (time step)
, i.e. velocity_y = velocity_y - 0.02 * timeStep. The displacement (change in position) of the ball in a particular direction (x or y) is its velocity in that direction 
 timeStep. Use this to calculate the new x and y coordinates. Don't bounce the ball (change the velocities) in this function.
overlap(Ball& b) should first check if the ball of the current instance collides with ball b. There are four conditions to check as overlaps can happen from 4 angles. If it doesn't collide, return that there is no overlap. If it collides with it, the function determines in which direction the collision is happening. The function returns an int, which is either HORIZONTAL_OVERLAP, VERTICAL_OVERLAP or NO_OVERLAP. The values of these macros are defined in Globals.h. If there is no overlap, the function should return NO_OVERLAP. In Fig. 4, we show how to measure the dimensions of the overlap. If the vertical overlap is larger than the horizontal, the function should return VERTICAL_OVERLAP. Otherwise, it should return HORIZONTAL_OVERLAP. 
overlap(Player& p) should first check if the ball of the current instance collides with the player p. The logic of the function is the same as overlap(Ball& b). 
bounce(Ball arr[], int ballCount, Player player) checks if the ball of the current instance bounces of any other ball, wall or the paddle of the player. The coordinates of the game window range from 0 to WIDTH - 1 in the x direction, and from 0 to HEIGHT - 1 in the y direction. If the current ball location is at or beyond the vertical walls, the sign of the velocity in the x direction should be flipped. You need to consider the dimensions of the ball here. If the current ball location is on the ground or beyond, the sign of the velocity in the y direction should be flipped. To bounce off another ball, you need to call the overlap function on all balls. If two balls overlap horizontally, flip the y-velocity; otherwise, flip the x-velocity. 
draw(Screen& screen_to_draw_to) renders the ball on the game window by calling addPixel on the screen_to_draw_to object (an instance of the Screen class). The addPixel function prototype is void addPixel(double x, double y, char symbol), where x and y are the coordinates, and symbol is 'o' (lower case letter O). Since the width and height of the ball is 1, we only call addPixel once.

The Game Controller
The game controller is implemented in main.cpp. Its role is to (i) create the game elements (player and balls), (ii) run the main game loop, which continues until the player quits or a ball escapes off the left wall, and (iii) within the loop, handle user input, update game physics, manage scoring, and render the current state.

The game is displayed as a sequence of frames. A frame means one full update of the screen showing the player, the balls, and the score. The number of frames shown per second is the frames per second (FPS), defined as screen_fps in Globals.h. For example, 60 FPS means the game draws 60 frames every second.

To keep the physics accurate, each frame is broken into several time steps. The number of time steps per frame is simulation_fps. The duration of one time step is timeStep (defined in Globals.h).

So, in each frame, the game runs simulation_fps iterations of the loop before drawing to the screen. 

What happens in one iteration/time step? 

Handle input using get_input() from io.cpp.

If the player types 'q', the game ends.

If the user input is not '\0', the paddle moves left or right using Player methods.

If no input is given, get_input() returns '\0', and the paddle stays in place.

Update balls:

Each ball moves according to its velocity.

Check if balls are to bounce from the paddle/walls/ceiling.

If a ball bounces off the left ball, the game ends.

If a ball collides with the paddle, the score increases by 1.
Game progression:

Every 2 hits, the paddle size decreases by 1 using a method in Player class.
Every 5 hits, we increase the number of balls by 1 till we have a maximum of 5 balls.
New balls created should have (x, y) = (30.0, 30.0), velocity_x = 0.9 and velocity_y = 0.
When the simulation_fps time steps are complete:

The game renders the frame by calling the draw() methods of Ball and Player.

The main loop waits for the correct frame duration so that the game runs smoothly at screen_fps.

We repeat the above process as long as the game did not end. The game ends when the player quits or a ball bouncing off the left wall.

Important! The skeleton code in main.cpp will render the updated game state to the screen by drawing the player, the balls and the score. It will also go through another game cycle after the time of one frame has passed. You are not required to edit the lines in the main.cpp. You are only required to add your game loop in the main function. 

Include Files
In addition to the Ball.h and Player.h files described above, the file Globals.h has global definitions for multiple macros such as simulation_fps and HORIZONTAL_OVERLAP. You should include this file if you plan to use it in Ball.cpp and/or Player.cpp.

We also have io.h and Screen.h function implementations for input/output and screen printing. Again, you may NOT modify these files to add to or delete from their content. Modifying the files commonly results in a mark of zero for the assignment.