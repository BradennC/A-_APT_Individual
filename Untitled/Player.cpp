#include "Player.h"

Player::Player(std::string name) {
    this->name = name;
    this->score = 0;
    this->hand = new LinkedList;
}

Player::Player(std::string name, LinkedList *newHand) {
    this->name = name;
    this->score = 0;
    this->hand = newHand;
}

Player::~Player() {
    delete this->hand;
}

void Player::setPlayerName(std::string name) {
    this->name = name;
}

void Player::setPlayerScore(int score) {
    this->score = score;
}

void Player::setPlayerHand(LinkedList* hand) {
    this->hand = hand;
}

void Player::playTile(Tile* tile){
    // getindex of tile to play
    int index = this->hand->getIndex(tile);

    // delete tile from hand
    this->hand->deleteAtIndex(index);
}

void Player::drawTiles(TileBag* tileBag, int amount) {

    for (int i = 0; i < amount; i++) {
        Tile *tile = tileBag->drawTile();
        // Add the drawn tile to the player's hand
        hand->addBack(tile);
    }
}

void Player::replaceTile(Tile* tile, TileBag* tileBag){
    if (tileBag->isEmpty())
    {
        return;
    }
    //get index of tile in hand
    int index = this->hand->getIndex(tile);
    
    if (index <= 5)
    {
        //add replacedTile to tilebag
        tileBag->addTile(tile);
    
        //remove the tile from players hand
        this->hand->deleteAtIndex(index);
    }
}

std::string Player::getPlayerName() {
    return this->name;
}

int Player::getPlayerScore() {
    return this->score;
}

LinkedList *Player::getPlayerHand() {
    return hand;
}


void Player::printAllTiles() {
    for(int i = 0; i < this->getPlayerHand()->size(); ++i){
        char colour = this->getPlayerHand()->get(i)->colour;
        if (colour == 'R')
        {
            std::cout << "\u001b[41m" << this->getPlayerHand()->get(i)->colour << this->getPlayerHand()->get(i)->shape << "\u001b[0m";
        }
        if (colour == 'B')
        {
            std::cout << "\u001b[44m" << this->getPlayerHand()->get(i)->colour << this->getPlayerHand()->get(i)->shape << "\u001b[0m";
        }
        if (colour == 'Y')
        {
            std::cout << "\u001b[43m" << this->getPlayerHand()->get(i)->colour << this->getPlayerHand()->get(i)->shape << "\u001b[0m";
        }
        if (colour == 'G')
        {
            std::cout << "\u001b[42m" << this->getPlayerHand()->get(i)->colour << this->getPlayerHand()->get(i)->shape << "\u001b[0m";
        }
        if (colour == 'O')//Try find a more orange colour
        {
            std::cout << "\u001b[43;1m" << this->getPlayerHand()->get(i)->colour << this->getPlayerHand()->get(i)->shape << "\u001b[0m";
        }
        if (colour == 'P')
        {
           std::cout << "\e[45m" << this->getPlayerHand()->get(i)->colour << this->getPlayerHand()->get(i)->shape << "\u001b[0m"; 
        }
        // comma seperator helps readability in terminal
        if(i != this->getPlayerHand()->size() - 1){
            std::cout << ",";
        }
    }
    std::cout << std::endl;
}

