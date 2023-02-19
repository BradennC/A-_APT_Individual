//
// Created by Quinn Goh on 22/1/23.
//

#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <cstdlib>
#include <random>
#include <sstream>
#include <vector>

#include "RulesEngine.h"
#include "Player.h"
#include "TileBag.h"
#include "Tile.h"
#include "TileCodes.h"
#include "GamesEngine.h"

GamesEngine::GamesEngine() {
    // initalising Memebr values to a minimal starting point
    this->re = new RulesEngine(this);
    this->player1 = new Player("");
    this->player2 = new Player("");
    this->activePlayer = this->player1;
    this->tileBag = nullptr;

    // Populating the tilebag with tiles
    generateRandomTiles();

    // Intialises the board vector to 27 to accomidate the edges of the board
    this->board = std::vector<std::vector<Tile *> >(27, std::vector<Tile *>(27));
    for (int row = 0; row < 27; row++) {
        for (int col = 0; col < 27; col++) {
            this->board[row][col] = nullptr;
        }
    }

    // Populating player tiles with tilebag values
    dealGame();
    // initalising Member values to a minimal starting point
    this->boardShape = {26, 26};
    this->quitGame = false;
    this->moveNumber = 0;
}


GamesEngine::~GamesEngine() {
    delete this->re;
    delete this->player1;
    delete this->player2;
    delete this->tileBag;
    for (int row = 0; row < 26; row++) {
        for (int col = 0; col < 26; col++) {
            delete this->board[row][col];
        }
    }
}

void GamesEngine::mainMenu() {

    // Initial Game loop
    while (this->quitGame == false && !re->isGameOver()) {

        // Print menu options
        std::cout << "\nMenu" << std::endl;
        std::cout << "-----" << std::endl;
        std::cout << "1. New Game" << std::endl;
        std::cout << "2. Load Game" << std::endl;
        std::cout << "3. Credits (show student information)" << std::endl;
        std::cout << "4. Quit\n" << std::endl;
        
        std::cout << "Enter your selection (1-4):" << std::endl;

        // Get user selection
        std::string menuSelection = getUserInput();

        // Run option based on user selection
        // Option 1 is newgame
        if (menuSelection == "1") {

            // Get names of players
            getPlayerName(player1, 1);
            if(!quitGame){
                getPlayerName(player2, 2);
                if(!quitGame){
                    playGame();
                }
            }
        // Option 2 is loadgame
        } else if (menuSelection == "2") {

            loadGame();
        // Option 3 is print credits
        } else if (menuSelection == "3") {

            std::cout << "\n--------------------------------" << std::endl;

            std::cout << "Name: Quinn Goh" << std::endl;
            std::cout << "Student ID: s3724287" << std::endl;
            std::cout << "Email: s3724287@student.rmit.edu.au" << std::endl;

            std::cout << std::endl;

            std::cout << "Name: Braden Cole" << std::endl;
            std::cout << "Student ID: s3727913" << std::endl;
            std::cout << "Email: s3727913@student.rmit.edu.au" << std::endl;

            std::cout << std::endl;

            std::cout << "Name: Justin Healy" << std::endl;
            std::cout << "Student ID: s3886040" << std::endl;
            std::cout << "Email: s3886040@student.rmit.edu.au" << std::endl;

            std::cout << std::endl;

            std::cout << "Name: Philip Hobbs" << std::endl;
            std::cout << "Student ID: s3692631" << std::endl;
            std::cout << "Email: s3692631@student.rmit.edu.au" << std::endl;

            std::cout << "--------------------------------" << std::endl;
        // Option 4 quits
        } else if (menuSelection == "4") {

            quit();
        // Case for any other input other than of the above options
        } else {
            if (!std::cin.eof()) {
                std::cout << "\nInvalid selection. Please enter a selection from 1 to 4" << std::endl;
            }
        }
    }
}

void GamesEngine::playGame() {

    std::cout << "\nLet's play!" << std::endl;

    while (!re->isGameOver() && !quitGame) {

        // print current scores and board
        printGameStatus();
        // get player's turn
        playerTurn(activePlayer);
    }
    // After loop a final check for gameover is run, then results are printed
    if(re->isGameOver()){
        printGameResult();
    }
}



void GamesEngine::playerTurn(Player* activePlayer){

    // print active player's hand
    std::cout << "\nYour hand is" << std::endl;
    this->activePlayer->printAllTiles();

    // continue to prompt player for move until a valid command is entered
    bool validCommand = false;
    while(!validCommand && !quitGame)
    {
        // Ask the player to make a move
        std::cout << "\nEnter your move" << std::endl;
        std::string stringInputForMove = getUserInput();

        // handle ctrl-d
        if(std::cin.eof())
        {
            validCommand = true;
        }

        // handle 'quit'
        if(stringInputForMove == "quit")
        {
            validCommand = true;
            quit();
        }
        else
        {
            // store each word of the command in a vector to make them easy to work with
            std::vector<std::string> commandWords;
            std::stringstream ss(stringInputForMove);
            std::string word;
            while(ss >> word){
                commandWords.push_back(word);
            }

            if (commandWords.size() == 1)
            {
                if (commandWords[0] == "help")
                {
                    helpMethod();
                    validCommand = true;
                }
            }

            // All valid commands (except 'quit') are either 2 or 4 words long. 
            // All other input gets 'invalid command' message.                
            if(commandWords.size() == 2)
            {
                // save command
                if(commandWords[0] == "save")
                {
                    saveGame(commandWords[1]);
                    validCommand = true;
                }

                // replace command
                if (commandWords[0] == "replace")
                {
                    // check valid tile format
                    bool validTile = false;
                    // check second word (tile code) is 2 characters, otherwise invalid move
                    if(commandWords[1].size() == 2)
                    {
                        // check colour is valid
                        char colour = commandWords[1][0];
                        if(colour == 'Y' ||
                           colour == 'G' ||
                           colour == 'B' ||
                           colour == 'R' ||
                           colour == 'P' ||
                           colour == 'O')
                        {
                            // check shape is valid
                            char shape = commandWords[1][1];
                            if(shape == '1' ||
                               shape == '2' ||
                               shape == '3' ||
                               shape == '4' ||
                               shape == '5' ||
                               shape == '6')
                            {
                                validTile = true;
                            }
                        }
                    }
                    
                    if(validTile)
                    {
                        //Create tile from move input
                        Tile* replaceTile = convertStringToTile(stringInputForMove);

                        if(activePlayer->getPlayerHand()->contains(*replaceTile) && !tileBag->isEmpty())
                        {
                            //Call replace tile
                            this->activePlayer->replaceTile(replaceTile, tileBag);

                            //draw new tile after replacing tile
                            this->activePlayer->drawTiles(tileBag, 1);

                            //update active player
                            updateActivePlayer();

                            //update move number
                            this->moveNumber++;

                            validCommand = true;
                        }
                    }
                }
            }

            if (commandWords.size() == 4)
            {
                // place command
                if(commandWords[0] == "place" && commandWords[2] == "at")
                {
                    // check valid tile format
                    bool validTile = false;
                    // check second word (tile code) is 2 characters, otherwise invalid move
                    if(commandWords[1].size() == 2)
                    {
                        // check colour is valid
                        char colour = commandWords[1][0];
                        if(colour == 'Y' ||
                           colour == 'G' ||
                           colour == 'B' ||
                           colour == 'R' ||
                           colour == 'P' ||
                           colour == 'O')
                        {
                            // check shape is valid
                            char shape = commandWords[1][1];
                            if(shape == '1' ||
                               shape == '2' ||
                               shape == '3' ||
                               shape == '4' ||
                               shape == '5' ||
                               shape == '6')
                            {
                                validTile = true;
                            }
                        }
                    }
                    // check valid board coordinate

                    // check valid board location
                    bool validBoardLocation = false;
                    std::string boardLocation = commandWords[3];
                    
                    // board locations must be either 2 or 3 characters,
                    // depending on row number.
                    if(boardLocation.size() == 2)
                    {
                        // check row is valid
                        std::string row = boardLocation.substr(0,1);
                        if(std::regex_match(row, std::regex("[A-Z]")))
                        {
                            // check column is valid
                            std::string col = boardLocation.substr(1,1);
                            try
                            {
                                int colInt = stoi(col);
                                if(colInt >= 0 && colInt <= 9)
                                {
                                    validBoardLocation = true;
                                }
                            }
                            catch(const std::invalid_argument& e)
                            {
                            }
                        }
                    } 
                    if(boardLocation.size() == 3)
                    {   
                        // check row is valid
                        std::string row = boardLocation.substr(0,1);
                        if(std::regex_match(row, std::regex("[A-Z]")))
                        {
                            // check column is valid
                            std::string colfirstDigit = boardLocation.substr(1,1);
                            std::string colSecondDigit = boardLocation.substr(2,1);
                            try
                            {
                                int colFirstDigitInt = stoi(colfirstDigit);
                                int colSecondDigitInt = stoi(colSecondDigit);
                                if( (colFirstDigitInt == 1 && (colSecondDigitInt >= 0 && colSecondDigitInt <= 9)) ||
                                    (colFirstDigitInt == 2 && (colSecondDigitInt >= 0 && colSecondDigitInt <= 5)) )
                                {   
                                    validBoardLocation = true;
                                }
                            }
                            catch(const std::invalid_argument& e)
                            {
                            }
                        }
                    }
                    if(validBoardLocation){
                        Tile* tile = convertStringToTile(stringInputForMove);
                        int index = this->activePlayer->getPlayerHand()->getIndex(tile);

                        if(validTile && index <= 5)
                        {
                            std::vector<BoardLocation *> moves;
                            BoardLocation& move = convertStringToMove(stringInputForMove);
                            

                            // Process the move and check if it is valid
                            if (re->isValidMove(move) || this->moveNumber == 0) 
                            {
                            
                                if (moveNumber == 0 && this->activePlayer->getPlayerScore() == 0){
                                    this->activePlayer->setPlayerScore(1);
                                }

                                
                                re->scoreMove(move);
                                //apply to move - and track the relevant point increases
                                re->applyMove(move, this->activePlayer);

                                if (tileBag->tiles->size() >= 1) {

                                    this->activePlayer->drawTiles(tileBag, 1);
                                }

                                

                                // If the move is valid, switch to the next player
                                updateActivePlayer();

                                this->moveNumber++;
                                validCommand = true;
                            }
                        }
                    }
                }              
            }
            //If multiplace command
            if(commandWords.size() >= 6 && commandWords.size() <= 14)
            {

                int atPos = (commandWords.size() / 2);

                if (commandWords[0] == "multiplace" && commandWords[atPos] == "at")
                {
                    bool validTiles = true;

                    //for loop to loop through tiles in command
                    for (int i = 1; i < atPos; i++)
                    {
                        if(commandWords[i].size() == 2)
                        {
                            // check colour is valid
                            char colour = commandWords[i][0];
                            if(colour == 'Y' ||
                            colour == 'G' ||
                            colour == 'B' ||
                            colour == 'R' ||
                            colour == 'P' ||
                            colour == 'O')
                            {
                                // check shape is valid
                                char shape = commandWords[i][1];
                                if(shape == '1' ||
                                shape == '2' ||
                                shape == '3' ||
                                shape == '4' ||
                                shape == '5' ||
                                shape == '6')
                                {
                                    //std::cout << "Valid tile" << std::endl;
                                }
                                else 
                                {
                                    validTiles = false;
                                }
                            }
                            else 
                            {
                                validTiles = false;
                            }
                        }
                    }

                    //Check for valid board locations
                    bool validBoardLocations = true;

                    for (int i = atPos + 1; i < commandWords.size(); i ++)
                    {
                        std::string boardLocation = commandWords[i];
                    
                    // board locations must be either 2 or 3 characters,
                    // depending on row number.
                    if(boardLocation.size() == 2)
                    {
                        // check row is valid
                        std::string row = boardLocation.substr(0,1);
                        if(std::regex_match(row, std::regex("[A-Z]")))
                        {
                            // check column is valid
                            std::string col = boardLocation.substr(1,1);
                            try
                            {
                                int colInt = stoi(col);
                                if(colInt >= 0 && colInt <= 9)
                                {
                                }
                                else
                                {
                                    validBoardLocations = false;
                                }
                            }
                            catch(const std::invalid_argument& e)
                            {
                            }
                        }
                    } 
                    if(boardLocation.size() == 3)
                    {   
                        // check row is valid
                        std::string row = boardLocation.substr(0,1);
                        if(std::regex_match(row, std::regex("[A-Z]")))
                        {
                            // check column is valid
                            std::string colfirstDigit = boardLocation.substr(1,1);
                            std::string colSecondDigit = boardLocation.substr(2,1);
                            try
                            {
                                int colFirstDigitInt = stoi(colfirstDigit);
                                int colSecondDigitInt = stoi(colSecondDigit);
                                if( (colFirstDigitInt == 1 && (colSecondDigitInt >= 0 && colSecondDigitInt <= 9)) ||
                                    (colFirstDigitInt == 2 && (colSecondDigitInt >= 0 && colSecondDigitInt <= 5)) )
                                {   
                      
                                }
                                else
                                {
                                    validBoardLocations = false;
                                }
                            }
                            catch(const std::invalid_argument& e)
                            {
                            }
                        }
                    }
                    }
                    
                    //Bool variables to track if moves are in same row or same col
                    bool sameRow = true;
                    bool sameCol = true;

                    //2 loops to check each move against other moves to find if same col or same row
                    for (int i = atPos + 1; i < commandWords.size(); i ++)
                    {
                        for (int k = atPos + 1; k < commandWords.size(); k++)
                        {
                            //Creatig string and move for i loop move
                            std::string multiMoveInput = commandWords[0] + " " + commandWords[1] + " "+ commandWords[2] + " " + commandWords[i];
                            BoardLocation bl1 = convertStringToMove(multiMoveInput);
                            //Creating string and move gor k loop move
                            std::string multiMoveInput2 = commandWords[0] + " " + commandWords[1] + " "+ commandWords[2] + " " + commandWords[k];
                            BoardLocation bl2 = convertStringToMove(multiMoveInput2);

                            //If cols font match set sameCol to false
                            if (bl1.getCol() != bl2.getCol())
                            {
                                sameCol = false;
                            }
                            //If rows dont match set sameRow to false
                            if (bl1.getRow() != bl2.getRow())
                            {
                                sameRow = false;
                            }
                        }
                    }

                    //Check if the tiles and board location are valid as well as either samecol or samerow is true
                    if (validTiles && validBoardLocations && (sameCol || sameRow))
                    {
                        //int for num of tiles placed
                        int numOfTilesPlaced = (commandWords.size() - 2) / 2;

                        //vector to store each move
                        std::vector<BoardLocation > moves;

                        //Loop through each move
                        for (int i = 1; i <= numOfTilesPlaced; i++)
                        {
                            
                            
                            std::string convTileString = commandWords[0] + " " + commandWords[i];
                            
                            Tile* tile = convertStringToTile(convTileString);
                            
                            int index = this->activePlayer->getPlayerHand()->getIndex(tile);


                            if (index <= 5)
                            {
                                
                                    int tilePos = i;
                                    int boardLocPos = (numOfTilesPlaced + 1) + i;
                                    std::string boardLocString = commandWords[0] + " " + commandWords[tilePos] + " " + commandWords[numOfTilesPlaced + 1] + " " + commandWords[boardLocPos];
                                    
                                    BoardLocation& move = convertStringToMove(boardLocString);
                                    moves.push_back(move);
                                    


                                    // Process the move and check if it is valid
                                    if (re->isValidMove(move) || this->moveNumber == 0) 
                                    {
                                        if (moveNumber == 0 && this->activePlayer->getPlayerScore() == 0){
                                            this->activePlayer->setPlayerScore(1);
                                        }

                                        
                                        //apply to move - and track the relevant point increases
                                        re->applyMove(move, this->activePlayer);
                                        
                                        if (i == numOfTilesPlaced)
                                        {
                                            re->scoreMove(moves);
                                        }
                                    }
                                    
                                
                            }
                        }

                        if (tileBag->tiles->size() >= 1) {

                                    this->activePlayer->drawTiles(tileBag, numOfTilesPlaced);
                                }

                                

                                // If the move is valid, switch to the next player
                                updateActivePlayer();

                                this->moveNumber++;
                                validCommand = true;
                        
                    }
                }
                

            }
        }
        if(!validCommand)
        {
            std::cout << "\nInvalid command!" << std::endl;
        }
    }

}


std::string GamesEngine::getUserInput() {
    std::cout << "> ";
    std::string userInput;
    getline(std::cin, userInput);
    // listening for eof character
    if (std::cin.eof()) {
        userInput = "";
        std::cout << std::endl;
        quit();
    }
    return userInput;
}

void GamesEngine::getPlayerName(Player* player, int playerNumber){

    std::cout << "\nEnter player " << playerNumber << " name (UPPERCASE LETTERS ONLY):" << std::endl;

    std::string playerName = getUserInput();

    //Check name is valid
    while (nameChecker(playerName) == false && !std::cin.eof()) {
        std::cout << "\nInvalid name!" << std::endl;
        std::cout << "\nEnter player " << playerNumber << " name (UPPERCASE LETTERS ONLY):" << std::endl;
        playerName = getUserInput();
    }

    //If name is valid setPlayer name
    player->setPlayerName(playerName);
}

std::string GamesEngine::TrimFunction(std::string str)
{
   const char* typeOfWhitespaces = " \t\n\r\f\v";
   str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
   str.erase(0,str.find_first_not_of(typeOfWhitespaces));
   return str;
}

void GamesEngine::loadGame() {
    bool goodLoad = false;
    while(!goodLoad)
    {
        std::cout << "\nEnter a file name of a saved game:" << std::endl;
        std::string file = getUserInput();
        if(std::cin.eof()){
            goodLoad = true;
            quitGame = true;
        }
        std::string line;
        std::ifstream myfile (file);
        // Count will keep track of line read position, incremented after every pass
        int count = 0;
        if (myfile.is_open()) {
            while ( getline(myfile,line) )
            {
                // Trims whitespaces
                line = TrimFunction(line);
                if(count == 0) {
                    this->player1->setPlayerName(line);
                } else if (count == 1) {
                    this->player1->setPlayerScore(std::stoi(line));
                }  else if (count == 2) {
                    //Set player1 hand
                    // String stream is used to split values seperated by a comma
                    LinkedList* hand = new LinkedList();
                    std::stringstream ss(line);
            
                    while (ss.good()) {
                        std::string substr;
                        getline(ss, substr, ',');
                        // int(substr[1] - 48) will convert binary char to int accuratley
                        Tile* tile = new Tile(substr[0], int(substr[1] - 48));

                        hand->addBack(tile);
                    }
                    player1->setPlayerHand(hand);
                } else if (count == 3) {
                    this->player2->setPlayerName(line);
                } else if (count == 4) {
                    this->player2->setPlayerScore(std::stoi(line));
                } else if(count == 5) {
                    //set player2 hand
                    LinkedList* hand = new LinkedList();
                    std::stringstream ss(line);
            
                    while (ss.good()) {
                        std::string substr;
                        getline(ss, substr, ',');
                        // int(substr[1] - 48) will convert binary char to int accuratley
                        Tile* tile = new Tile(substr[0], int(substr[1] - 48));

                        hand->addBack(tile);
                    }
                    player2->setPlayerHand(hand);
                } else if(count == 6) {
                    // Board shape! eg. height and width
                    std::stringstream ss(line);
                    int count = 0;
                    while (ss.good()) {
                        std::string substr;
                        getline(ss, substr, ',');
                        this->boardShape[count] = std::stoi(substr);
                        count++;
                    }
                    
                } else if(count ==7) {
                    // Update Board State
                    // Will check to see if board state is empty 
                    if(line != "") {
                        std::stringstream ss(line);

                        while (ss.good()) {
                            std::string substr;
                            getline(ss, substr, ',');
                            substr = this->TrimFunction(substr);
                            std::stringstream ss(substr);
                            char at, col1, col2;
                            int row1, row2;
                            ss >> col1 >> row1 >> at >> col2 >> row2;

                            Tile* tile = new Tile(col1 , row1);
                            int col2int = col2 - 'A';
                            this->board[col2int][row2] = tile;
                        }  
                    }
                    
                } else if(count ==8) {
                    // load tile bag
                    LinkedList* list = new LinkedList();
                    std::stringstream ss(line);
                    this->tileBag->clearTiles();
            
                    while (ss.good()) {
                        std::string substr;
                        getline(ss, substr, ',');
                        Tile* tile = new Tile(substr[0], int(substr[1] - 48));

                        list->addBack(tile);
                    }
                    this->tileBag->addTileList(list);
                } else if (count == 9) {
                    // current player name         
                    if(line ==  this->player1->getPlayerName()) {
                        this->activePlayer = this->player1;
                    } else {
                        this->activePlayer = this->player2;
                    }
                } 
                count++;
            }
            myfile.close();
            // Check to see 
            if(!player1->getPlayerName().empty() &&
            !player2->getPlayerName().empty() &&
            !player1->getPlayerHand()->isEmpty() &&
            !player2->getPlayerHand()->isEmpty() &&
            !tileBag->isEmpty() )
            {
                std::cout << "\nGame successfully loaded" << std::endl;
                goodLoad = true;
                // From here gameplay is to continue
                playGame();
            }
            else 
            {   
                if(!quitGame)
                {
                    // error message for when file can be opened, but doesn't contain good game data
                    std::cout << "\nCould not load game!" << std::endl;
                }

            }
        }
        else 
        {
            if(!quitGame)
            {
                // error message for can't open file
                std::cout << "\nCould not load game!" << std::endl;
            }

        }
    }
   
}

void GamesEngine::saveGame(std::string fileName) {
    std::ofstream outputStream;
    outputStream.open(fileName, std::ios::out);
    if(outputStream.is_open()) {
        
        // Save player1 details
        outputStream << player1->getPlayerName() << std::endl; 
        outputStream << player1->getPlayerScore() << std::endl; 
        LinkedList* hand = player1->getPlayerHand();
        for (int i = 0; i < hand->size() ; i++) {
         outputStream << hand->get(i)->colour << hand->get(i)->shape; 
         if(i < 5) {
            outputStream << ","; 
         }
        }
        outputStream << std::endl;
        // Save player2 details
        outputStream << player2->getPlayerName() << std::endl; 
        outputStream << player2->getPlayerScore() << std::endl; 
        hand = player2->getPlayerHand();
        for (int i = 0; i < hand->size() ; i++) {
         outputStream << hand->get(i)->colour << hand->get(i)->shape; 
         if(i < 5) {
            outputStream << ","; 
         }
        }
        outputStream << std::endl;
        // Save board shape
        outputStream << this->boardShape[0] << "," << this->boardShape[1] << std::endl;
        // Save the state of the board
        // Define a char array to return int values to char id
        char alph[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for(unsigned int i=0;i<this->board.size();i++){
		      for(unsigned int j=0;j<this->board[i].size();j++){
               if(this->board[i][j] != 0) {
                  outputStream<<this->board[i][j]->colour<< this->board[i][j]->shape << "@";
                  outputStream << alph[i] << j << ", ";
               }
            }
	      }
         outputStream << std::endl;

         // Tile bag is saved to local file
         LinkedList* tiles = this->tileBag->tiles;
         for (int i = 0; i < tiles->size() ; i++) {
         outputStream << tiles->get(i)->colour << tiles->get(i)->shape; 
         if(i < tiles->size() - 1) {
            outputStream << ","; 
         }
        }
        outputStream << std::endl;
        // Active player name saved
        outputStream << activePlayer->getPlayerName() << std::endl; 
        outputStream.close();
        std::cout << "\nGame saved successfully!" << std::endl;
    } else {
        std::cout << "problem writing to file " << std::endl;
    } 
}

void GamesEngine::quit() {
    this->quitGame = true;
    std::cout << "\nGoodbye!" << std::endl;
}

void GamesEngine::updateActivePlayer() {
    if (this->activePlayer == player1) {
        this->activePlayer = player2;
    } else {
        this->activePlayer = player1;
    }
}

void GamesEngine::placeTile(int x, int y, Tile* tileValue) {

    this->board[x][y] = tileValue;
}

bool GamesEngine::nameChecker(std::string const &str) {
    return std::regex_match(str, std::regex("^[A-Z]+$"));
};

//Method for shuffling tiles in tilebag
LinkedList *GamesEngine::shuffleTileBag(LinkedList *list) {
    
    
    LinkedList* shuffledList = new LinkedList();

    int maxIndex = list->size() - 1;
    for(int i = maxIndex; i >= 0; --i){
        std::random_device randEngine;
        std::uniform_int_distribution<int> uniform_dist(0,i);
        int randIndex = uniform_dist(randEngine);

        Tile* tile = list->get(randIndex);
        Tile* copy = new Tile(tile->colour, tile->shape);
        shuffledList->addFront(copy);
        list->deleteAtIndex(randIndex);
    }

    return shuffledList;
};

void GamesEngine::printGameStatus() {
    // Print current scores
    std::cout << std::endl;
    std::cout << this->activePlayer->getPlayerName() << ", it's your turn\n" << std::endl;
    std::cout << "Current scores" << std::endl;
    std::cout << this->player1->getPlayerName() << ": " << this->player1->getPlayerScore() << std::endl;
    std::cout << this->player2->getPlayerName() << ": " << this->player2->getPlayerScore() << std::endl;
    std::cout << std::endl;

    // Print the current board
    printBoard();
}

void GamesEngine::dealGame() {
    this->player1->drawTiles(this->tileBag, 6);
    this->player2->drawTiles(this->tileBag, 6);
}

void GamesEngine::printGameResult() {
    // Print the final score
    std::cout << "Game over" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << player1->getPlayerName() << ": " << player1->getPlayerScore() << std::endl;
    std::cout << player2->getPlayerName() << ": " << player2->getPlayerScore() << std::endl;
    std::cout << std::endl;
    if(player1->getPlayerScore() > player2->getPlayerScore()){
        std::cout << player1->getPlayerName() << " WINS!!" << std::endl;
    } else if(player2->getPlayerScore() > player1->getPlayerScore()){
        std::cout << player2->getPlayerName() << " WINS!!" << std::endl;
    } else {
        std::cout << "IT'S A TIE!!" << std::endl;
    }
}

Tile* GamesEngine::convertStringToTile(std::string input)
{
    std::stringstream ss(input);
    std::string word;
    char col;
    int shape;

    ss >> word >> col >> shape;

    Tile* tile = new Tile(col, shape);

    return tile;
}


BoardLocation& GamesEngine::convertStringToMove(std::string input) {
    std::stringstream ss(input);
    std::string word;
    char col1, col2;
    int row1, row2;
    ss >> word >> col1 >> row1 >> word >> col2 >> row2;

    int col2_int = col2 - 'A';


    BoardLocation* move = new BoardLocation(row2, col2_int, Tile(col1, row1));
    BoardLocation& moveRef = *move;

    return moveRef;
}

void GamesEngine::printBoard() {

    // Print header row
    std::cout << " ";
    for (int i = 0; i < 10; i++) {
        std::cout << "  " << i;
    }
    for (int i = 10; i < 26; i++) {
        std::cout << " " << i;
    }
    std::cout << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;

    // Print board
    for (int row = 0; row < 26; row++) {
        // Print row index
        std::cout << static_cast<char>('A' + row) << "|";

        for (int col = 0; col < 26; col++) {
            if (board[row][col] == nullptr) {
                std::cout << "  |";
            } else {
                if (board[row][col]->colour == 'B'){
                    std::cout << "\u001b[44m" << board[row][col]->colour << board[row][col]->shape << "\u001b[0m" << "|";
                }
                if (board[row][col]->colour == 'R'){
                    std::cout << "\u001b[41m"  << board[row][col]->colour << board[row][col]->shape << "\u001b[0m" << "|";
                }
                if (board[row][col]->colour == 'G'){
                    std::cout << "\u001b[42m" << board[row][col]->colour << board[row][col]->shape << "\u001b[0m" << "|";
                }
                if (board[row][col]->colour == 'Y'){
                    std::cout << "\u001b[43m"  << board[row][col]->colour << board[row][col]->shape << "\u001b[0m" << "|";
                }
                if (board[row][col]->colour == 'P'){
                    std::cout << "\e[45m"  << board[row][col]->colour << board[row][col]->shape << "\u001b[0m" << "|";
                }
                if (board[row][col]->colour == 'O'){
                    std::cout << "\u001b[43m"  << board[row][col]->colour << board[row][col]->shape << "\u001b[0m" << "|";
                }
            }
        }
        std::cout << std::endl;
    }
}

void GamesEngine::generateRandomTiles() {

    LinkedList* list = new LinkedList();

    char colours[6] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    
    int numOfEachTile = 2;
    for(int i = 0; i < numOfEachTile; ++i)
    {
        for (int j = 0; j < 6; j++)
        {
            for (int k = 1; k <= 6; k++)
            {
            Tile* tile = new Tile(colours[j],k);
            list->addFront(tile);
            }
        }
   }

    list = shuffleTileBag(list);
    this->tileBag = new TileBag(list);
}

std::vector<std::vector<Tile *> > GamesEngine::getBoard() {
    return this->board;
}

TileBag *GamesEngine::getTileBag() {
    return this->tileBag;
}

std::vector<Player *> GamesEngine::getPlayers() {

    std::vector<Player *> players;
    players.push_back(this->player1);
    players.push_back(this->player2);
    return players;

}

Player *GamesEngine::getCurrentPlayer() {
    return this->activePlayer;
}

Tile* GamesEngine::getTileAt(int row, int column) {
    return this->board[row][column];
}

void GamesEngine::helpMethod() 
{
    std::cout << "\n To place tile:" << std::endl;;
    std::cout << "place (your tile) at (board coordinate) e.g. place B4 at A1 \n" << std::endl;

    std::cout << "To replace tile:" << std::endl;;
    std::cout << "replace (your tile) e.g. replace R5 \n" << std::endl;

    std::cout << "To place multiple tiles enter tiles to be place between 'multiplace' and 'at':" << std::endl;;
    std::cout << "multiplace (your tile) (another tile) at (board coordinate) (board coordinate)" << std::endl;
    std::cout << "e.g multiplace B5 R5 at X4 X3 or multiplace B5 R5 Y5 at X3 X4 X5 \n" << std::endl;

    std::cout << "To save game:" << std::endl;;
    std::cout << "save (gameName) e.g. save myGame.save \n" << std::endl;

    std::cout << "To quit:" << std::endl;;
    std::cout << "quit or ^D \n" << std::endl;

}
