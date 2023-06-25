<h1 align="center">
  <br>
  <br>
  Ludo
  <br>
</h1>

<h4 align="center">A Console-Based Ludo Game created in C++ with Multi-Threading</h4>

<p align="center">
  <a href="#introduction">Introduction</a> •
  <a href="#development">Development</a> •
  <a href="#controls">Controls</a> •
  <a href="#gameplay">Gameplay</a> •
  <a href="#contact">Contact</a>
</p>


<p align="center">
  <img src="https://user-images.githubusercontent.com/83888735/232159361-bd3bd271-609f-4148-b183-6a15c45d47d9.gif">
</p>


# Introduction
Welcome to Ludo, a console-based game created in C++! This classic board game has been brought to life in a digital format, allowing up to 4 players to enjoy the game simultaneously. The game utilizes multi-threading to ensure smooth gameplay and responsiveness.

The objective of Ludo is to move all your tokens from the starting point to the center of the board, following the clockwise direction. The first player to move all their tokens to the center is declared the winner.

Please refer to the rest of this README.md file for instructions on how to install and play the game.

# Development
### Dependencies

 - C++ Compiler

### Installation
To install and run the game, follow these steps:
 - Clone the repository to your local machine.
 - Open a terminal or command prompt and navigate to the project directory.
 - Compile the source code using a C++ compiler. For example, if you're using g++, run the following command:

```shell
g++ -o ludo main.cpp -lpthread
```


### Run Game
Run the compiled executable:
```shell
./ludo
```

# Controls
To play the game, you will need to use the following controls:

 - `1`, `2`, `3`, `4`: Select a token to move (corresponding to the player's tokens).
 - `1`: Roll the dice to generate a random number.

The controls are displayed in the console, and you will be prompted to input the desired action during your turn.

# Gameplay
### Player Tokens
Each player is represented by a color and has 4 tokens. The players and their corresponding colors are as follows:

 - Player 1: Red
 - Player 2: Blue
 - Player 3: Green
 - Player 4: Yellow

### Turns and Movement
The game follows a turn-based system, starting with Player 1 and proceeding in a clockwise order. On your turn, you can choose a token to move by inputting the corresponding number. After selecting a token, you will roll the dice to determine the number of steps the token can move.

You can only move a token out of the starting point if you roll a 6 on the dice. Tokens can move in a clockwise direction along the designated path on the board. If a token lands on an opponent's token, the opponent's token is sent back to the starting point.

The game continues until one player successfully moves all their tokens to the center of the board. That player is declared the winner.

### Multi-Threaded Gameplay
The game utilizes multi-threading to ensure a smooth and responsive experience. Each player's turn is handled by a separate thread, allowing simultaneous gameplay for up to 4 players. This enhances the multiplayer experience and adds excitement to the game.

# Contact
If you have any questions or feedback about the game, feel free to contact me using the information below:

-   **Email:** [mohammadali417@outlook.com](mailto:mohammadali417@outlook.com)
-   **GitHub:** [MuhammadAli511](https://github.com/MuhammadAli511)
-   **LinkedIn:** [Muhammad Ali](https://www.linkedin.com/in/muhammad-ali-6932bb211/)

Thanks for playing Ludo, and I hope you have a great time with your friends and family! Enjoy the game!