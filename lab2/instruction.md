The Game Controller
The game controller is implemented in main.cpp. Its role is to (i) create the game elements (player and balls), (ii) run the main game loop, which continues until the player quits or a ball escapes off the left wall, and (iii) within the loop, handle user input, update game physics, manage scoring, and render the current state.

The game is displayed as a sequence of frames. A frame means one full update of the screen showing the player, the balls, and the score. The number of frames shown per second is the frames per second (FPS), defined as screen_fps in Globals.h. For example, 60 FPS means the game draws 60 frames every second.

To keep the physics accurate, each frame is broken into several time steps. The number of time steps per frame is simulation_fps. The duration of one time step is timeStep (defined in Globals.h).

So, in each frame, the game runs simulation_fps iterations of the loop before drawing to the screen. 

What happens in one iteration/time step? 

Handle input using get_input() from io.cpp.

If the player types 'q', the game ends.

If the user input is not '\0', the paddle moves up or down using Player methods.

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