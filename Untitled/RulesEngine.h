#ifndef RULESENGINE_H
#define RULESENGINE_H

#include <vector>
#include "BoardLocation.h"
#include "LinkedList.h"
#include "Player.h"
#include "TileBag.h"
#include "GamesEngine.h"

/**
 * @class RulesEngine
 *
 * @brief This class implements the rules for a tile matching game.
 *
 * The RulesEngine class provides methods to check the validity of moves,
 * check for matches, and determine the score of a given set of tiles.
 * The rules implemented by this class are used by the GamesEngine class
 * to run Qwirkle.
 */

class GamesEngine;

class RulesEngine {
public:
    /**
     * @brief Constructor
     *
     * Initializes the rules engine.
     */
    RulesEngine();

    /**
     * @brief Constructor with game engine pointer
     *
     * Initializes the rules engine with a pointer to the game engine.
     *
     * @param gamesEngine Pointer to the games engine
     */
    explicit RulesEngine(GamesEngine *gamesEngine);

    /**
     * @brief Check if the game is over
     *
     * @return bool Returns true if the game is over, false otherwise
     */
    bool isGameOver();

    /**
     * @brief Apply the move
     *
     * Applies the move made by the player to the board.
     *
     * @param move The board location of the move
     * @param player Pointer to the player making the move
     */
    void applyMove(BoardLocation &move, Player *player);

    /**
     * @brief Check if the player has the tile
     *
     * Check if the player has the specified tile in their hand.
     *
     * @param playerHand Pointer to the player's hand
     * @param tile Pointer to the tile to check for
     *
     * @return bool Returns true if the player has the tile, false otherwise
     */
    bool isPlayerHasTile(LinkedList *playerHand, const Tile *tile);

    /**
     * @brief Check if the move is adjacent to another tile
     *
     * Check if the specified move is adjacent to another tile on the board.
     *
     * @param move The board location of the move
     *
     * @return bool Returns true if the move is adjacent to another tile, false otherwise
     */
    bool isMoveAdjacentToOtherTile(const BoardLocation &move) const;

    /**
     * @brief Check if the move is valid based on the rules of Qwirkle
     *
     * @param location The board location of the move
     *
     * @return bool Returns true if the move is valid, false otherwise
     */
    bool isValidMove(const BoardLocation &location) const;

    /**
     * @brief Check if the player has enough tile
     *
     * Check if the player has enough tiles to make the specified move.
     *
     * @param playerHand Pointer to the player's hand
     * @param currentTile Pointer to the current tile in the move
     *
     * @return bool Returns true if the player has enough tiles, false otherwise
     */
    bool isPlayerHasEnoughTiles(LinkedList *playerHand, const Tile *currentTile) const;

    /**
     * @brief Verify the line of tiles
     *
     * Verify the line of tiles to ensure it is a valid move based on the rules of Qwirkle.
     *
     * @param line The line of tiles to be verified.
     * @return bool Returns true if the line of tiles is valid, false otherwise.
     */
     bool verifyByLine(std::vector<Tile *> line) const;

     /**
    * @brief Check if all players have an empty hand
    *
    * This function checks if all players have an empty hand.
    *
    * @return bool Returns true if all players have an empty hand, false otherwise.
    */
    bool allPlayersHaveEmptyHand();

    /**
    * @brief This function returns a vector of `Tile` objects that are vertically aligned with the given `BoardLocation`.
    *
    * @param location The `BoardLocation` from which to retrieve a vertical line of tiles.
    *
    * @return The vector of vertically aligned `Tile` objects.
    */
    std::vector<Tile *>  hasVertical(const BoardLocation &location) const;


    /**
     * @brief This function returns a vector of `Tile` objects that are horizontally aligned with the given `BoardLocation`.
     *
     * @param location The `BoardLocation` from which to retrieve a horizontal line of tiles.
     *
     * @return The vector of horizontally aligned `Tile` objects.
     */
    std::vector<Tile *> hasHorizontal(const BoardLocation &location) const;

    void scoreMove(const BoardLocation &location) const;
    void scoreMove(std::vector<BoardLocation >);

    private:
    // Pointer to the games engine
    GamesEngine *ge;

};

#endif
