# snake-game
This is a simple and classic Snake game built using C++. The game runs in the console, where you control a snake that moves around the screen, eats food, and grows in length. The goal is to keep the snake alive for as long as possible without crashing into its own body or the walls of the screen.

**How I Built It:**
I started by setting up the screen dimensions and creating a simple interface to display the game. The snake is represented as a series of coordinates on the screen, and its movement is controlled by the arrow keys (W, A, S, D).

**Key Features:**
Snake Movement: The snake moves continuously in the current direction and responds to user input to change direction.
Growing Mechanism: The snake grows longer each time it eats food. The food is randomly placed on the screen.
Collision Detection: The game checks if the snake runs into itself or the edges of the screen. If it does, the game ends.
Score Display: The current score is displayed at the top of the screen, showing how many pieces of food the snake has eaten.
**Technologies Used:**
C++: The core logic of the game is written in C++, utilizing standard libraries for handling input/output and screen manipulation.
Windows API: I used the Windows API to control the console cursor position, which helps in rendering the snake and food at specific coordinates on the screen.
Randomized Food Placement: The food position is generated randomly within the boundaries of the screen, ensuring a new challenge with each game.
**How to Play:**
Use W, A, S, D keys to move the snake up, left, down, and right respectively.
The snake will keep moving in the current direction until a new direction is provided.
The game ends if the snake collides with itself or the screen boundary.
Your score increases each time the snake eats food, which appears as x on the screen.
**What I Learned:**
This project was a great exercise in handling real-time input, managing game state, and working with basic graphics in a console environment. It also helped me understand the importance of clean, human-friendly code, both for my own understanding and for sharing with others.
