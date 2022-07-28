#ifndef AVL_TREE_NC_H
#define AVL_TREE_NC_H

#include "LinkedList.h"


class AVL_Node_NC {
public:
    QString data;
    LinkedList* list;
    AVL_Node_NC* LeftChild;
    AVL_Node_NC* RightChild;
    int height;

public:
    AVL_Node_NC()
    {
        list = new LinkedList;
        height = 0;
        LeftChild = NULL;
        RightChild = NULL;
    }
};

class AVL_Tree_NC
{
public:
    AVL_Node_NC* root;
    AVL_Node_NC* ploc;
    AVL_Node_NC* loc;

public:
    AVL_Tree_NC();
    bool isEmpty();
    //void preorderTraversal(AVL_Node_NC*);
    //void inorderTraversal(AVL_Node_NC*);
    //void postorderTraversal(AVL_Node_NC*);
    //void deleteNode();
    //void destroyTree(AVL_Node_NC*);
    AVL_Node_NC* left_rotate(AVL_Node_NC*, AVL_Node_NC*);
    AVL_Node_NC* right_rotate(AVL_Node_NC*, AVL_Node_NC*);
    //int insert(Template, AVL_Node_player*);
    int insertnode(QString, AVL_Node_NC*);
    void insertNode(QString);
    void balance(AVL_Node_NC*, AVL_Node_NC*);
    int balance_factor(AVL_Node_NC*);
    //int deletenode(Template, AVL_Node_player*);
    //void function(AVL_Node_NC, AVL_Node_NC);
    void checkheight(AVL_Node_NC*);
    ////player* search_player(QString, AVL_Node_NC*);
    AVL_Node_NC* search_NC(QString A, AVL_Node_NC* ptr);
};


#endif // AVL_TREE_NC_H
