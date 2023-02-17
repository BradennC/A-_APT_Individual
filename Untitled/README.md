# A2-APT

Assignment 2, Advanced Prog. Tech. RMIT 2023

## Description

This game is implemented using C++ and includes the following classes:

**BoardLocation**
* Represent the location of the tiles on the board.

**LinkedList**
* Implement a linked list data structure to store player hand tiles.

**Player**
* Represent a player in the game, including their score, name, and tile hand.

**TileBag**
* Store the tiles available for the players to draw from.

**GamesEngine**
* Store the state of the game and manage the game loop.

**RulesEngine**
* Verify the validity of the player's moves and apply them to the game state

## Installing & Executing program

To run this game, you need to have a C++ compiler and the standard library.To compile and run this game, follow these steps:

* Clone this repository
* Navigate to the repository directory
* Run the following command to compile the code:
```
g++ -Wall -Werror -std=c++14 -O -o qwirkle TileBag.cpp Tile.cpp BoardLocation.cpp RulesEngine.cpp GamesEngine.cpp LinkedList.cpp  Node.cpp Player.cpp qwirkle.cpp
```
* Alternatively, you can compile using the provided Makefile:
```
make qwirkle

* Run the following command to execute the code:
```
./qwirkle
```

## Gameplay

The game starts with the player who has the first turn. Each turn, a player can either place tiles on the board or draw tiles from the tile bag. 
When placing tiles, the player must follow the rules of Qwirkle, which require that the tiles be placed adjacent to existing tiles on the board 
and match either the color or shape of the adjacent tiles. Points are earned based on the number of tiles placed and the number of lines created. 
The game continues until all tiles have been placed or the tile bag is empty. The player with the highest score at the end of the game wins.

## Testing

There are 11 tests that can be run to test various aspects of the game. Below are explanations of the purpose of each test
as well as commands used to run them.

Test 1
Menu option 1 is selected and prompts for input of player names. Tests for incorrectly formatted names 
(names should be uppercase letters only), before then testing a correctly formatted name for player 1. Ctrl-d is tested for exiting the program at the point of the player 2 name prompt (play cannot continue in this test in order to avoid
issues with testing a randomly ordered tile bag).

Test run commands:
> ./qwirkle < tests/input/test1.input > tests/actual_outputs/test1.gameout
> diff -w tests/expected_outputs/test1.output tests/actual_outputs/test1.gameout

Test 2
Menu option 2 is used to load a saved game. The loaded game as a new game with player names and scores both at 0 and an empty board. A full standard game is played from start to finish with no input errors, no saves or early exit. Player options of play or replace tile are both tested. Scoring, including the scoring of a Qwirkle, is tested. Printing of game results is tested with player 1 being the winner.

Test run commands:
> ./qwirkle < tests/input/test2.input > tests/actual_outputs/test2.gameout
> diff -w tests/expected_outputs/test2.output tests/actual_outputs/test2.gameout

Test 3
Tests all points in the game where a user can enter invalid input, including main menu selections, incorrectly formatted commands during gameplay, invalid commands that break game rules and invalid save game command. The game is then eventually played to the end with player 1 winning. Invalid commands include:
* Invalid main menu selection (using letters or selecting non-existent menu option).
* Placing a tile at a place off the board.
* Attempting to place a tile not in a player's hand.
* Attempting to replace a tile not in a player's hand.
* Attempting to replace a tile with an invalid tile code.
* Attempting to place a tile in an illegal position (not adjactent to any other tiles or not in a matching line).
* Illegal commands (e.g. "change" tile instead of "replace" tile or "save to" instead of just "save").

Test run commands:
> ./qwirkle < tests/input/test3.input > tests/actual_outputs/test3.gameout
> diff -w tests/expected_outputs/test3.output tests/actual_outputs/test3.gameout if [-e tests/exp_saved_games/test3.expsave] diff -w -y tests/exp_saved_games/test3.expsave tests/actual_saved_games/test3.save

Test 4
Tests that games can be saved correctly. A game is loaded using menu option 2. Three rounds are played before a save command. Three more rounds are then played to test that a player can save then continue with their turn and the rest of the game. The gave is then saved again, to the same file. This tests that the most up-to-date state of the game is saved, overwriting the previous save. Quit game is then tested using ctrl-d.

Test run commands:
> ./qwirkle < tests/input/test4.input > tests/actual_outputs/test4.gameout
> diff -w tests/expected_outputs/test4.output tests/actual_outputs/test4.gameout if [-e tests/exp_saved_games/test4.expsave] diff -w -y tests/exp_saved_games/test4.expsave tests/actual_saved_games/test4.save

Test 5
Tests the 'quit' function during gameplay. A game is loaded using menu option 2, then normal gameplay is played for 3 rounds before the game is exited using the command "quit".

Test run commands:
> ./qwirkle < tests/input/test5.input > tests/actual_outputs/test5.gameout
> diff -w tests/expected_outputs/test5.output tests/actual_outputs/test5.gameout

Test 6
Tests that games are loaded correctly. Menu option 2 is used to attempt to load a game from a file that doesn't exist. Then a game is loaded from a file that doesn't contain valid game data. Finally, a game is loaded using good game data, before playing out a full game to the end.

Test run commands:
> ./qwirkle < tests/input/test6.input > tests/actual_outputs/test6.gameout
> diff -w tests/expected_outputs/test6.output tests/actual_outputs/test6.gameout

Test 7
Exiting the game using ctrl-d is tested after selecting menu option 2 and being prompted for a file name.

Test run commands:
> ./qwirkle < tests/input/test7.input > tests/actual_outputs/test7.gameout
> diff -w tests/expected_outputs/test7.output tests/actual_outputs/test7.gameout

Test 8
Menu options 3 and 4 are tested. Menu option 3 is selected to show game credits. The menu is then presented again and option 4 is selected to quit the game.

Test run commands:
> ./qwirkle < tests/input/test8.input > tests/actual_outputs/test8.gameout
> diff -w tests/expected_outputs/test8.output tests/actual_outputs/test8.gameout

Test 9
Tests exiting the game using ctrl-d from the main menu, before any menu option is selected.

Test run commands:
> ./qwirkle < tests/input/test9.input > tests/actual_outputs/test9.gameout
> diff -w tests/expected_outputs/test9.output tests/actual_outputs/test9.gameout

Test 10
Loads a game using menu option 2, then a full game is played out resulting in a tied game, testing the printing of the game results in such a situation.

Test run commands:
> ./qwirkle < tests/input/test10.input > tests/actual_outputs/test10.gameout
> diff -w tests/expected_outputs/test10.output tests/actual_outputs/test10.gameout

Test 11
Loads a game using menu option 2, then a full game is played out resulting in player 2 winning, testing the printing of the game results in such a situation. During the game an attempt to draw a tile from an empty bag is also made. 

Test run commands:
> ./qwirkle < tests/input/test11.input > tests/actual_outputs/test11.gameout
> diff -w tests/expected_outputs/test11.output tests/actual_outputs/test11.gameout

## Authors

Contributors names and contact info

 * Philip Hobbs - s3692631@student.rmit.edu.au
 * Justin Healy - s3886040@student.rmit.edu.au
 * Quinn Goh - s3724287@student.rmit.edu.au
 * Braden Cole - s3727913@student.rmit.edu.au

## License

This project is licensed under the MIT License - see the MIT-license.md file for details

## Acknowledgments

