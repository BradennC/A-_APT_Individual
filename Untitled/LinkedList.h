
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include "Tile.h"

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    int size();
    Tile* get(int index);


    void addFront(Tile* tile);
    void addBack(Tile* tile);

    void deleteFront();
    void deleteBack();
    void deleteAtIndex(int index);
    void deleteAtIndex2(int index);

    void printAll();

    // added for use in replaceTile in GamesEngine, may not be needed once replaceTile
    // in implemented in Player class
    int getIndex(Tile* tile);

    //------ below methods already written, but may not be needed.
    //------ Once program is complete, delete any of these that haven't been used.

    void clear();
    Node *getHead();
    void setHead(Node* node);
    bool contains(const Tile &tile);
    void addAtIndex(Tile* tile, int index);
    bool isEmpty();

private:
    Node* head;
    Node* tail;
    int numNodes;
};

#endif // ASSIGN2_LINKEDLIST_H
