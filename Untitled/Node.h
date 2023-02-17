
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {
public:

   /**
   * @brief constructor
   *
   * @param tile tile to be set on construction
   * @param next value of next node in linked list
   * 
   */
   Node(Tile* tile, Node* next);
   /**
   * @brief copy constructor
   *
   * @param other reference to node which requires copy
   * 
   */
   Node(Node& other);

   // object member variables of node class
   // Non private for easy access
   Tile* tile;
   Node* next;

};

#endif // ASSIGN2_NODE_H
