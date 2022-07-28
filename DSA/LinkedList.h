#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "player.h"

class ListNode {
public:
    player* data;
    ListNode* next;
};


class LinkedList {
public:
    ListNode* start; // special variable which stores address of the head node.
    ListNode* last; // special variable which stores address of the last node.
    ListNode* PredLoc_; //to be used by Search(value) method to store address of logical predecessor of value in a list.
    ListNode* Loc_; //to be used by Search(value) method to store address of the node containing the searched value in a list. If it is not found it contains NULL.

    LinkedList();
    bool isEmpty();
    void InsertAtFront(player*);
    void InsertAtEnd(player*);
    /*void printList();
    void Search(player*);
    void InsertSorted(player*);
    void Delete(player*);
    void DestroyList();*/
};


#endif // LINKEDLIST_H
