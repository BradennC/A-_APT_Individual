//
// Created by Quinn Goh on 22/1/23.
//
#ifndef A2_APT_GAMESENGINE_H
#define A2_APT_GAMESENGINE_H

#include "RulesEngine.h"
#include "Player.h"
#include "TileBag.h"
#include <vector>
#include <array>



class RulesEngine;

/**
 * @class GamesEngine
 *
 * @brief This class implements the game logic for a tile matching game.
 *
 * The GamesEngine class provides methods to initialize the game,
 * make moves, update the score, and end the game. It uses the rules
 * implemented in the RulesEngine class to determine the outcome of a move
 * and updates the game state accordingly.
 */
class GamesEngine {

private:

    Player* player1;
    Player* player2;
    Player* activePlayer;
    TileBag* tileBag;
    RulesEngine* re;
    std::vector<std::vector<Tile*> > board;
    std::array<int, 2> boardShape;
    bool quitGame;
    int moveNumber;

public:
    /**
     * @brief Constructor
     *
     * Initializes the games engine.
     * Sets member variables to null or empty values.
     * Populates TileBag with tiles and initialises board Vector.
    */
    GamesEngine();

    /**
     * @brief deconstructor
     *
     * Deletes object member variables stored on the heap.
    */
    ~GamesEngine();

    /**
     * @brief prints main menu receives input from user
     *
     * Prints the menu function to initiailise gameplay, load, or display credits.
     * Will exit main menu loop when all gameplay has completed or quit is passed by the 
     * user
    */
    void mainMenu();

    /**
     * @brief receives and returns users input
     *
     * Listens for eof character and calls quitt function if received
     * 
     * @return will the users inout in string form
    */
    std::string getUserInput();

    /**
     * @brief requests player name from user
     *
     * Prints out questions for the user to the terminal to save player name.
     * When user input is received it will check input against nameChecker function
     * and continue to prompt if requirements not met.
     * When met player name varibale in the player will be updated.
    */
    void getPlayerName(Player* player, int playerNumber);

    /**
     * @brief holds main game play loop
     *
     * Calls game play functions printGameStatus and playerTurn.
     * Will continue main game play until the gameover function in the Rules engine 
     * returns a true value or quit boolean value equals true.
     * 
    */
    void playGame();

    /**
     * @brief Requests a file from the user and loads data structures
     *
     * Will read the contents of the file given by the user and reead line by line
     * to populate the data structures with information stored in the file.
     * Offers some validation chacks to prevent against program crash from false input.
     * 
    */
    void loadGame();

    /**
     * @brief Takes a filename as an argument and saves data structures
     * 
     * Data strctures will be written to file of the name passed to it as a 
     * an argument.
     * 
     * @param fileName file name passed by calling function.
     * 
    */
    void saveGame(std::string fileName);
    /**
     * @brief sets memebr variable quit to true
     *
     * Changes this->quit to true, then prints a Goodby message
     * 
    */
    void quit();

    /**
     * @brief Populates players tile list
     *
     * Populates the players hand lists by calling their member functions
     * and draws tiles from the tile bag.
    */
    void dealGame();


    /**
     * @brief Alternates the active player to the other player in the game
     * 
     * Functions assists in altering turns in the gameplay
     *
    */
    void updateActivePlayer();
    /**
     * @brief Runs the gameplay and input validation
     * 
     * Will prompt user for input, process the input and validate input.
     * If the input does not meet checks against shape, colour and command (replace etc)
     * input will be again requested, and the user will be informed of and invalid command.
     * 
     * @param activePlayer is passed the current activeplayer object to alter values
     *
    */
    void playerTurn(Player* activePlayer);

    /**
     * @brief Prints board
     * 
     * Method will print the board and reference headers on the rows and columns
     *
    */
    void printBoard();
    /**
     * @brief Prints current game satus
     * 
     * Will print Scores and then call the print board method
     *
    */
    void printGameStatus();

    /**
     * @brief Will print the final scores and the winner
     * 
     * Decides the winner depending on the final scores and prints the result
     *
    */
    void printGameResult();

    /**
     * @brief Shuffles list of tiles in the tileBag
     * 
     * Access the tileBags tile list and calls random number to delete at a random index
     * then reinstantiate deleted tile at the fron of the tileBag.
     * 
     * @param tileBag pointer to the tileBag instance
     * 
     * @returns return a pointer to the given linked list which has now been "shuffled"
    */
    LinkedList* shuffleTileBag(LinkedList* tilebag);

    /**
     * @brief Takes string input to return a boardlocation object
     * 
     * converts input into relevant data types the passes to a new board location object
     * 
     * @returns value returned is ref to newly created bpardLocation object
    */
    BoardLocation& convertStringToMove(std::string input);

    /**
     * @brief Takes string inpu to return a Tile*
     * 
     * converts input into relevant data types the passes to a new tile object
     * 
     * @returns value returned is ref to newly created bpardLocation object
    */
    Tile* convertStringToTile(std::string input);

    /**
     * @brief Is passed coordinates to locate a tile on the board
     * 
     * @returns value returned is ref to newly created bpardLocation object
    */
    Tile* getTileAt(int x, int y);


    /**
     * @brief Removes leading and trailing whitespace from a string
     * 
     * @returns string that was passed without whitespaces
    */
    std::string TrimFunction(std::string str);

    /**
     * @brief Checks name input
     * 
     * Will validate string input. Name value must be all uppercase.
     * Uses regex checker and false returned pass falied. 
     * 
     * @returns boolean value of whether name input is all uppercase letters
    */
    bool nameChecker(std::string const &str);

    /**
     * @brief Will generate tiles for the tile bag
     * 
     * Creates two of every type of tile to a total of 72 tiles. Then passes list
     * to the shuffleTileBag method and finally assigns to the tileBag list member
     * variable.
     * 
    */
    void generateRandomTiles();
    
    /**
     * @brief Will generate tiles for the tile bag
     * 
     * Will pass tileValue pointer argument to the board. At the x,y location
     * indicated by the x, y itn variables.
     * 
     * @param x int value of x coordinate
     * @param y int value of y coordinate
     * @param tileValue pointer to tile value being placed
     * 
    */
    void placeTile(int x, int y, Tile* tileValue);

    /**
     * @brief Getter for board object
     * 
     * @returns pointer to board vector
     * 
    */
    std::vector< std::vector<Tile*> > getBoard();
    /**
     * @brief Getter for tile bag object
     * 
     * @returns pointer to tileBag object
     * 
    */
    TileBag* getTileBag();
    /**
     * @brief Getter for both players
     * 
     * Pushes both player object vpointer to a vector and returns the vector
     * 
     * @returns players vector
     * 
    */
    std::vector<Player*> getPlayers();
    /**
     * @brief Getter for current player
     * 
     * 
     * @returns activeplayer
     * 
    */
    Player* getCurrentPlayer();
};


#endif //A2_APT_GAMESENGINE_H
