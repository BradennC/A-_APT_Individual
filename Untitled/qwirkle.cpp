#include "TileCodes.h"
#include "RulesEngine.h"
#include "GamesEngine.h"
#include "Player.h"
#include <iostream>

#define EXIT_SUCCESS    0

// Tests
void testLinkedList();

/**
   * @brief main
   *
   * Main method, creates our game engine and initiates gameplay
   * Deletes games engine on close
   * 
   * @param void colour of tile to be defined
   */
int main(void) {
   
   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;

   // Games engine will run game loop and game logic
   GamesEngine* engine = new GamesEngine();
   // Main menu method holds gameplay loop
   engine->mainMenu();

   // Cleanup
   delete engine;

   return EXIT_SUCCESS;
}

/**
   * @brief Linked list tester
   *
   * Will create and test basic linkedlist functions
   * 
   */
void testLinkedList()
{
  LinkedList myList;

  Tile* t1 = new Tile(RED, DIAMOND);
  Tile* t2 = new Tile(RED, CIRCLE);
  Tile* t3 = new Tile(RED, STAR_4);
  Tile* t4 = new Tile(RED, STAR_6);
  Tile* t5 = new Tile(RED, CLOVER);

  myList.addFront(t1);
  myList.addBack(t2);
  myList.addBack(t3);

  std::cout << "Added 3 tiles via addFront and addBack" << std::endl;
  myList.printAll();

  myList.deleteFront();
  myList.deleteBack();

  std::cout << "Removed front and back tiles" << std::endl;
  myList.printAll();

  myList.addBack(t4);
  myList.addBack(t5);
  myList.printAll();

  myList.deleteAtIndex(2);
  std::cout << "Deleting at index 2" << std::endl;
  myList.printAll();

  myList.addAtIndex(new Tile(YELLOW, CLOVER), 2);
  std::cout << "Adding at index 2" << std::endl;
  myList.printAll();
  delete t1;
  delete t2;
  delete t3;
  delete t4;
  delete t5;
}

