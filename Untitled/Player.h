#ifndef A2_APT_PLAYER
#define A2_APT_PLAYER

#include <iostream>
#include "TileBag.h"
#include "LinkedList.h"

class Player {

public:
    /**
    * @brief constructor
    *
    * @param name name to be defined in player object
    */
    Player(std::string name);

    /**
    * @brief constructor
    *
    * @param name name to be defined in player object
    * @param newHand provide pre made linkedlist to store as players hand
    */
    Player(std::string name, LinkedList* newHand);

    /**
    * @brief deconstructor
    *
    * deletes players hand
    * 
    */
    ~Player();

    /**
    * @brief function to find and remove tile from players hand
    *
    * @param tile tile pointer to tile which needs to be removed 
    * 
    */
    void playTile(Tile* tile);

    /**
    * @brief Draws tile from the tile bag and passes it to players hand
    *
    * @param tile tile pointer to tile which needs to be added 
    * @param tilebag pointer to tilebag instance
    * 
    */
    void playerDrawTile(TileBag* tileBag);

    /**
    * @brief replaces tile in players hand
    *
    * @param tile tile pointer to tile which needs to be replaced 
    * @param tilebag pointer to tilebag instance
    * 
    */
    void replaceTile(Tile* tile, TileBag* tileBag);

    /**
    * @brief prints player hand
    *
    * Values are printed with seperating commas
    * 
    */
    void printAllTiles();

    /**
    * @brief draws tiles from tile bag for player
    *
    * @param tilebag pointer to tilebag instance
    * @param amount int in the amount of tiles to be drawn 
    * 
    */
    void drawTiles(TileBag* tileBag, int amount);

    /**
    * @brief getter for player name
    * 
    * @return returns player name string
    *
    */
    std::string getPlayerName();
    /**
    * @brief getter for player score
    * 
    * @return returns player scorre int
    *
    */
    int getPlayerScore();
    /**
    * @brief getter for player hand
    * 
    * @return returns player hand LinkedList pointer
    *
    */
    LinkedList* getPlayerHand();

    /**
    * @brief sets player name
    *
    * @param name string value of name to be set
    * 
    */
    void setPlayerName(std::string name);
    /**
    * @brief sets player score
    *
    * @param score int of score to be set
    * 
    */
    void setPlayerScore(int score);
    /**
    * @brief sets player hand
    *
    * @param hand pointer to linkedlist of tiles
    * 
    */
    void setPlayerHand(LinkedList* hand);

private:
    // object member variables
    // Remains private to ensure no data is leaked unintentionally
    std::string name;
    int score;
    LinkedList* hand;
};

#endif // A2_APT_PLAYER