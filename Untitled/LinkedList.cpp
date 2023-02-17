#include <iostream>

#include "LinkedList.h"
#include "Node.h"

LinkedList::LinkedList(){
    this->head = nullptr;
    this->tail = nullptr;
    this->numNodes = 0;
}

LinkedList::~LinkedList(){
    this->clear();
}

int LinkedList::size(){
    return numNodes;
}

void LinkedList::clear(){
    while(numNodes > 0){
      deleteFront();
    }
}

Tile* LinkedList::get(int i){

    Tile* tile = nullptr;
    if(numNodes > 0){
        if(i == 0){
            tile = head->tile;
        } else {
            Node* currentNode = head;
            Node* nextNode = head->next;
            for(int j = 0; j < i; ++j){
                // find the node equal to i
                currentNode = nextNode;
                nextNode = nextNode->next;
            }

            // return the tile
            tile = currentNode->tile;
            
        }
    }
    return tile;
}

void LinkedList::addFront(Tile* tile){
    Node* newNode = new Node(tile, head);
    head = newNode;
    ++numNodes;
    if(numNodes == 1){
        tail = newNode;
    }
}

void LinkedList::addBack(Tile* tile){
    Node* newNode = new Node(tile, nullptr);
    if(numNodes == 0){
        head = newNode;
    } else {
        Node* currentNode = head;
        Node* nextNode = head->next;
        //find the last node
        while(nextNode != nullptr){
            currentNode = nextNode;
            nextNode = nextNode->next;
        }
        // make the last node point to the new node (which already points to null)
        currentNode->next = newNode;
    }
    ++numNodes;
    tail = newNode;
}

void LinkedList::addAtIndex(Tile* tile, int index){
    if (this->head == nullptr || index > this->numNodes) {
    return;
    } 
    // Defines node which will be replaced with new node
    Node* temp = this->head;
    Node* newNode = new Node(tile, nullptr);
    int i = 0;
    while(i < index) {
        temp = temp->next;
        i++;
    }
    // Defines previous node to repoint to the new node 
    Node* prev = this->head;
    i = 0;
    while(i < (index - 1)) {
        prev = prev->next;
        i++;
    }
    // point previous node to newnode and point new node to the next
    prev->next = newNode;
    newNode->next = temp;
    numNodes++;

}

int LinkedList::getIndex(Tile* tile)
{
    Node* temp = this->head;

    int i = -1;
    int iterator = 0;
    bool foundTile = false;

    while(temp != nullptr && !foundTile)
    {
        if (temp->tile->colour == tile->colour && temp->tile->shape == tile->shape)
        {
            i = iterator;
            foundTile = true;
        }
        
        temp = temp->next;
        iterator++;
    }
    return i;
}

void LinkedList::deleteFront(){
    if(numNodes > 0){
        Node* nextNode = head->next;
        delete head;
        head = nextNode;
        --numNodes;
    }
}

void LinkedList::deleteBack(){
    // check for empty list
    if(numNodes > 0){
        // check or singly populated list
        if(numNodes == 1){
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            Node* currentNode = head;
            int i = 1;
            while(currentNode->next != tail){
                currentNode = currentNode->next;
                ++i;
            }
            delete tail;
            tail = currentNode;
            currentNode->next = nullptr;
        }
        --numNodes;
    }
}

void LinkedList::deleteAtIndex(int index){

    // check list not empty or index out of bounds
    if (this->head == nullptr || index >= this->numNodes) {
        return;
    } 

    Node* current = this->head;
    Node* next = head->next;

    if(index == 0){
        deleteFront();
    }
    else if(index == numNodes - 1){
        deleteBack();
    }
    else {
        int i = 0;
        while(i < index - 1){
            next = next->next;
            current = current->next;
            ++i;
        }
        current->next = next->next;
        delete next;
        --numNodes;
    }   
}

void LinkedList::printAll()
{
    Node* temp = this->head;

    if (temp == nullptr){
        std::cout << "List empty" << std::endl;
    }

    else
    {
        while (temp != nullptr)
        {
            std::cout <<"Colour: " << temp->tile->colour <<" Shape: " <<  temp->tile->shape << std::endl;
            temp = temp->next;
        }
    }
}

bool LinkedList::isEmpty() {
    //bool to track if list is empty
    bool isEmpty = true;

    //Check if num nodes >= 1
     if (numNodes >= 1){

        //set is Empty to false if true
        isEmpty = false;
     } 
    //return isEmpty
     return isEmpty;
}

Node *LinkedList::getHead() {
    return this->head;
}

void LinkedList::setHead(Node* node) {
     this->head = node;
}

bool LinkedList::contains(const Tile &tile) {
    Node *current = head;
    bool contains = false;

    while (current != nullptr) {

        if (current->tile->shape == tile.shape && current->tile->colour == tile.colour) {

            contains = true;

        }

        current = current->next;
    }
    return contains;
}

