#include <iostream>
#include <cassert>
#include <set>
#include "BoardLocation.h"
#include "LinkedList.h"
#include "RulesEngine.h"
#include "Player.h"
#include "TileBag.h"


RulesEngine::RulesEngine() {}

RulesEngine::RulesEngine(GamesEngine *gamesEngine) {

    this->ge = gamesEngine;


}

bool RulesEngine::isPlayerHasEnoughTiles(LinkedList *playerHand, const Tile *currentTile) const {

    int count = 0;
    bool playerHas = false;

    for (int i = 0; i < playerHand->size(); i++) {

        if (playerHand->get(i)->shape == currentTile->shape && playerHand->get(i)->colour == currentTile->colour) {
            count++;
        }
    }

    if (count >= 1) {

        playerHas = true;

    }

    return playerHas;
}

bool RulesEngine::isMoveAdjacentToOtherTile(const BoardLocation &move) const {

    int y = move.getRow();
    int x = move.getCol();

    bool tileRight = false;
    bool tileLeft = false;
    bool tileTop = false;
    bool tileBottom = false;


    if (x > 0) {

        if (ge->getTileAt(x - 1, y) != nullptr) {


            if (ge->getBoard()[x - 1][y]->colour == move.tile().colour ||
                ge->getBoard()[x - 1][y]->shape == move.tile().shape) {

                tileLeft = true;

            }
        }

    }

    if (ge->getBoard()[x + 1][y] != nullptr) {

        if (ge->getBoard()[x + 1][y]->colour == move.tile().colour ||
            ge->getBoard()[x + 1][y]->shape == move.tile().shape) {

            tileRight = true;

        }


    }

    if (y > 0) {

        if (ge->getBoard()[x][y - 1] != nullptr) {

            if (ge->getBoard()[x][y - 1]->colour == move.tile().colour ||
                ge->getBoard()[x][y - 1]->shape == move.tile().shape) {

                tileBottom = true;

            }
        }

    }

    if (ge->getBoard()[x][y + 1] != nullptr) {

        if (ge->getBoard()[x][y + 1]->colour == move.tile().colour ||
            ge->getBoard()[x][y + 1]->shape == move.tile().shape) {

            tileTop = true;

        }
    }


    return tileBottom || tileTop || tileLeft || tileRight;

}

bool RulesEngine::isGameOver() {
    // Check if the tile bag is empty and no player has any more tiles
    bool isGameOver = false;
    if (allPlayersHaveEmptyHand()) {
        isGameOver = true;
    }
    return isGameOver;
}

void RulesEngine::applyMove(BoardLocation &move, Player *player) {

    std::vector<Tile *> tiles;
    // Iterate through the move and place the tile on the board

    Tile *tile = new Tile(move.getTile());

    ge->placeTile(move.getCol(), move.getRow(), tile);

    ge->getCurrentPlayer()->playTile(tile);

    tiles.push_back(tile);

}

bool RulesEngine::verifyByLine(std::vector<Tile *> line) const {

    bool sameColour = true;
    bool sameShape = true;
    bool identical = false;

    //check the validity of the line
    for (unsigned int i = 0; i < line.size(); ++i) {
        for (unsigned int j = i + 1; j < line.size(); ++j) {

            if (line[i]->colour == line[j]->colour && line[i]->shape == line[j]->shape) {
                identical = true;
            }
            if (line[i]->colour != line[j]->colour) {
                sameColour = false;
            }
            if (line[i]->shape != line[j]->shape) {
                sameShape = false;
            }
        }
    }

    return !identical && (sameShape || sameColour);
}

bool RulesEngine::allPlayersHaveEmptyHand() {

    bool isGameOver = false;
    Player *player1 = ge->getPlayers()[0];
    Player *player2 = ge->getPlayers()[1];
    if (player1->getPlayerHand()->isEmpty() && player2->getPlayerHand()->isEmpty()) {
        isGameOver = true;
    }

    return isGameOver;

}

bool RulesEngine::isPlayerHasTile(LinkedList *playerHand, const Tile *tile) {

    Node *curr = playerHand->getHead();

    while (curr != nullptr) {
        if (curr->tile->colour == tile->colour && curr->tile->shape == tile->shape) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

bool RulesEngine::isValidMove(const BoardLocation &location) const {


    bool isValid = true;


    int col = location.getRow();
    int row = location.getCol();

    Tile *tile = new Tile(location.getTile().colour, location.getTile().shape);
    //Vectors to store the
    std::vector<Tile *> horizontalLine, verticalLine;

    //Boolean values to check the validity of the move
    bool isMoveAdjacentToOtherTilex = true;
    bool isEmptySpot = true;


    //Check if it has adjacent tiles
    if (!isMoveAdjacentToOtherTile(location)) {

        isMoveAdjacentToOtherTilex = false;
    }

    // The location must be empty
    if (ge->getBoard()[row][col] != nullptr) {
        isEmptySpot = false;
    }

    //Check vertical and store in vector
    verticalLine = hasVertical(location);

    //Check horizontal and store in vector
    horizontalLine = hasHorizontal(location);

    //If there is > 1 in the line - add the current tile to the line so that it can be validated
    if (horizontalLine.size() >= 1) { horizontalLine.push_back(tile); }

    //If there is > 1 in the line - add the current tile to the line so that it can be validated
    if (verticalLine.size() >= 1) { verticalLine.push_back(tile); }

    //Check the validity of the move overall by validating lines and conditions
    if (!verifyByLine(verticalLine) || !verifyByLine(horizontalLine) || !isMoveAdjacentToOtherTilex || !isEmptySpot) {

        isValid = false;

        //If it is valid - add points to the players score accordingly
    } else
    {
        isValid = true;
    }

    return isValid;

}


void RulesEngine::scoreMove(const BoardLocation &location) const {
    std::vector<Tile *> horizontalLine, verticalLine;
    Tile* tile = new Tile(location.getTile().colour, location.getTile().shape);

    horizontalLine = hasHorizontal(location);
    verticalLine = hasVertical(location);

    //If there is > 1 in the line - add the current tile to the line so that it can be validated
    if (horizontalLine.size() >= 1) { horizontalLine.push_back(tile); }

    //If there is > 1 in the line - add the current tile to the line so that it can be validated
    if (verticalLine.size() >= 1) { verticalLine.push_back(tile); }

        ge->getCurrentPlayer()->setPlayerScore(
                ge->getCurrentPlayer()->getPlayerScore() + verticalLine.size() + horizontalLine.size());

        //Check for Qwirkle
        if (verticalLine.size() == 6) {
            ge->getCurrentPlayer()->setPlayerScore(ge->getCurrentPlayer()->getPlayerScore() + 6);
            std::cout << "QWIRKLE!!!" << std::endl;
        }

        //Check for Qwirkle
        if (horizontalLine.size() == 6) {
            ge->getCurrentPlayer()->setPlayerScore(ge->getCurrentPlayer()->getPlayerScore() + 6);
            std::cout << "QWIRKLE!!!" << std::endl;
        }

    }

    void RulesEngine::scoreMove(std::vector<BoardLocation > moves) {
        

       std::set<std::vector<Tile *>> horizontalLinesSet;
        std::set<std::vector<Tile *>> verticalLineSet;
        std::vector<Tile *> horizontaLine, verticalLine;
        int score = 0;
        
        for (int i = 0 ; i < moves.size(); i ++)
        {
            horizontaLine = hasHorizontal(moves[i]);
            verticalLine = hasVertical(moves[i]);

            if (horizontaLine.size() >= 1)
            {
                horizontaLine.push_back(new Tile(moves[i].getTile().colour, moves[i].getTile().shape));
            }
            if (verticalLine.size() >= 1)
            {
                verticalLine.push_back(new Tile(moves[i].getTile().colour, moves[i].getTile().shape));
            }

            if (horizontalLinesSet.size() == 0)
            {
                horizontalLinesSet.insert(horizontaLine);
            }
            else if (horizontalLinesSet.size() > 0)
            {
                int num = 0;
                for (auto elem : horizontalLinesSet)
                {
                    for (int i = 0; i < elem.size(); i++)
                    {
                        for (int j = 0; j < horizontaLine.size(); j++)
                        {
                            if (horizontaLine[j]->colour == elem[i]->colour && horizontaLine[j]->shape == elem[i]->shape)
                            {
                                num++;
                            }
                        }
                    }
                    if (num != elem.size())
                    {
                        horizontalLinesSet.insert(horizontaLine);

                    }
                    num = 0;
                }
            }

            if (verticalLineSet.size() == 0)
            {
                verticalLineSet.insert(verticalLine);
            }
            else if (verticalLineSet.size() > 0)
            {
                int num = 0;
                for (auto elem : verticalLineSet)
                {
                    for (int i = 0; i < elem.size(); i++)
                    {
                        for (int j = 0; j < verticalLine.size(); j++)
                        {
                            if (verticalLine[j]->colour == elem[i]->colour && verticalLine[j]->shape == elem[i]->shape)
                            {
                                num++;
                            }
                        }
                    }
                    if (num != elem.size())
                    {
                        verticalLineSet.insert(verticalLine);

                    }
                    num = 0;
                }
            }

            std::cout << " H Set size" << horizontalLinesSet.size() << std::endl;
            std::cout << " V Set size" << verticalLineSet.size() << std::endl;
            int currScore = 0;
            for (auto elem : verticalLineSet)
            {
                std::cout << " new " << std::endl;
                
                currScore += elem.size();
                for (int i = 0; i < elem.size(); i++)
                {
                    std::cout << elem[i]->colour << elem[i]->shape << std::endl;

                }
            }

            for (auto elem : horizontalLinesSet)
            {
                std::cout << " new H" << std::endl;
                
                currScore += elem.size();
                for (int i = 0; i < elem.size(); i++)
                {
                    std::cout << elem[i]->colour << elem[i]->shape << std::endl;

                }
            }
            score = currScore;
            std::cout << "Score " << score << std::endl;
        }

        ge->getCurrentPlayer()->setPlayerScore(
            ge->getCurrentPlayer()->getPlayerScore() + score);

    }

std::vector<Tile *>  RulesEngine::hasVertical(const BoardLocation &location) const {

    int col = location.getRow();
    int row = location.getCol();

    // Create a new tile from the tile at the given location
    Tile *tile = new Tile(location.getTile().colour, location.getTile().shape);
    Tile *currentTile = new Tile(tile->colour, tile->shape);

    // Create a vector to store the vertical line of tiles
    std::vector<Tile *> verticalLine;

    // Check tiles to the left
    bool shouldStop = false;
    for (int lineLength = 1; lineLength < 26 && !shouldStop; lineLength++) {
        int r = row, c = col - lineLength;

        // Check if the location is within the bounds of the board
        if (c >= 0 && c < 26 && r >= 0 && r < 26) {

            // Check if the current location on the board is not empty
            if (ge->getBoard()[r][c] != nullptr) {
                // Check if the tile at the current location has the same colour or shape as the current tile
                if (ge->getBoard()[r][c]->colour == currentTile->colour ||
                    ge->getBoard()[r][c]->shape == currentTile->shape) {
                    // If so, update the current tile and add it to the vertical line
                    currentTile = ge->getBoard()[r][c];
                    verticalLine.push_back(ge->getBoard()[r][c]);
                } else {
                    // If not, stop checking for tiles
                    shouldStop = true;
                }
            } else {
                // If the current location is empty, stop checking for tiles
                shouldStop = true;
            }
        }

    }

    // Check tiles to the right
    shouldStop = false;
    for (int lineLength = 1; lineLength < 26 && !shouldStop; lineLength++) {
        int r = row, c = col + lineLength;

        // Check if the location is within the bounds of the board
        if (c >= 0 && c < 26 && r >= 0 && r < 26) {

            // Check if the current location on the board is not empty
            if (ge->getBoard()[r][c] != nullptr) {
                // Check if the tile at the current location has the same colour or shape as the current tile
                if (ge->getBoard()[r][c]->colour == currentTile->colour ||
                    ge->getBoard()[r][c]->shape == currentTile->shape) {
                    // If so, update the current tile and add it to the vertical line
                    currentTile = ge->getBoard()[r][c];
                    verticalLine.push_back(ge->getBoard()[r][c]);
                } else {
                    // If not, stop checking for tiles
                    shouldStop = true;
                }
            } else {
                // If the current location is empty, stop checking for tiles
                shouldStop = true;
            }
        }

    }

    // Return the line of tiles
    return verticalLine;

}

std::vector<Tile *> RulesEngine::hasHorizontal(const BoardLocation &location) const {
    // get the row and column values from the given BoardLocation object
    int col = location.getRow();
    int row = location.getCol();

    // create a new Tile object with the colour and shape of the tile in the given location
    Tile *tile = new Tile(location.getTile().colour, location.getTile().shape);
    Tile *currentTile = new Tile(tile->colour, tile->shape);

    // create an empty vector to store the line of matching tiles
    std::vector<Tile *> horizontalLine;

    // flag to stop the loop when the matching tile line ends
    bool shouldStop = false;

    // check tiles to the north of the given location and add to the line of matching tiles
    for (int lineLength = 1; lineLength < 26 && !shouldStop; lineLength++) {
        int r = row - lineLength, c = col;

        // check if the current location is within the bounds of the board
        if (c >= 0 && c < 26 && r >= 0 && r < 26) {
            // check if there is a tile at the current location
            if (ge->getBoard()[r][c] != nullptr) {
                // check if the tile at the current location has the same colour or shape as the tile in the given location
                if (ge->getBoard()[r][c]->colour == currentTile->colour ||
                    ge->getBoard()[r][c]->shape == currentTile->shape) {
                    // update the currentTile object to the matching tile
                    currentTile = ge->getBoard()[r][c];
                    // add the matching tile to the line of matching tiles
                    horizontalLine.push_back(ge->getBoard()[r][c]);
                } else {
                    // set the flag to stop the loop if the tile does not match
                    shouldStop = true;
                }
            } else {
                // set the flag to stop the loop if there is no tile at the current location
                shouldStop = true;
            }
        }
    }

    // reset the currentTile object to the tile in the given location
    currentTile = new Tile(tile->colour, tile->shape);
    // reset the flag to stop the loop
    shouldStop = false;

    // check tiles to the south of the given location and add to the line of matching tiles
    for (int lineLength = 1; lineLength < 26 && !shouldStop; lineLength++) {
        int r = row + lineLength, c = col;

        // check if the current location is within the bounds of the board
        if (c >= 0 && c < 26 && r >= 0 && r < 26) {
            // check if there is a tile at the current location
            if (ge->getBoard()[r][c] != nullptr) {
                // check if the tile at the current location has the same colour or shape as the tile in the given location
                if (ge->getBoard()[r][c]->colour == currentTile->colour ||
                    ge->getBoard()[r][c]->shape == currentTile->shape) {
                    // update the currentTile object to the matching tile
                    currentTile = ge->getBoard()[r][c];
                    // add the matching tile to the
                    horizontalLine.push_back(ge->getBoard()[r][c]);
                } else {
                    // If not, stop checking for tiles
                    shouldStop = true;
                }
            } else {
                // If the current location is empty, stop checking for tiles
                shouldStop = true;
            }
        }

    }

    return horizontalLine;

}
