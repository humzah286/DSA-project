#ifndef AVL_Tree_player_H
#define AVL_Tree_player_H

#include "player.h"

class AVL_Node_player {
public:
    player* data;
    AVL_Node_player* LeftChild;
    AVL_Node_player* RightChild;
    int height;

public:
    AVL_Node_player()
    {
        height = 0;
        LeftChild = NULL;
        RightChild = NULL;
    }
};

class AVL_Tree_player
{
public:
    AVL_Node_player* root;
    AVL_Node_player* ploc;
    AVL_Node_player* loc;

public:
    AVL_Tree_player();
    bool isEmpty();
    //void preorderTraversal(AVL_Node_player*);
    //void inorderTraversal(AVL_Node_player*);
    //void postorderTraversal(AVL_Node_player*);
    //void deleteNode();
    //void destroyTree(AVL_Node_player*);
    AVL_Node_player* left_rotate(AVL_Node_player*, AVL_Node_player*);
    AVL_Node_player* right_rotate(AVL_Node_player*, AVL_Node_player*);
    //int insert(Template, AVL_Node_player*);
    int insertnode(player*, AVL_Node_player*);
    void insertNode(player*);
    void balance(AVL_Node_player*, AVL_Node_player*);
    int balance_factor(AVL_Node_player*);
    //int deletenode(Template, AVL_Node_player*);
    //void function(AVL_Node_player, AVL_Node_player);
    void checkheight(AVL_Node_player*);
    player* search_player(QString, AVL_Node_player*);
};

#endif // AVL_Tree_player_H
