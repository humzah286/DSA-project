#include "AVL_Tree_NC.h"

//start of AVL_Tree implementation for a club or country

AVL_Tree_NC::AVL_Tree_NC()
{
    root = NULL;
    ploc = NULL;
    loc = NULL;
}

bool AVL_Tree_NC::isEmpty()
{
    return (root == NULL);
}

void AVL_Tree_NC::checkheight(AVL_Node_NC* ptr)
{
    if (ptr == NULL) return;

    int temp1 = -1, temp2 = -1;

    if (ptr->LeftChild != NULL) temp1 = ptr->LeftChild->height;
    if (ptr->RightChild != NULL) temp2 = ptr->RightChild->height;

    if (temp1 > temp2) ptr->height = temp1 + 1;
    else ptr->height = temp2 + 1;
}

int AVL_Tree_NC::insertnode(QString val, AVL_Node_NC* ptr)
{
    //int temp01 = -1; int temp02 = -1;

    if (ptr == NULL)
    {
        loc = NULL;
        if (ptr == root) { ploc = NULL; insertNode(val); }
        return 1;
    }

    //QString::compare(val->name, ptr->data->name, Qt::CaseInsensitive);

    if (QString::compare(val, ptr->data, Qt::CaseInsensitive) > 0)
    {
        if (insertnode(val, ptr->RightChild) == 1)
        {
            ploc = ptr;
            insertNode(val);
        }

        checkheight(ptr);

        balance(ptr, ptr->RightChild);
        if (ptr == root) balance(NULL, ptr);
    }
    else if (QString::compare(val, ptr->data, Qt::CaseInsensitive) < 0)
    {
        if (insertnode(val, ptr->LeftChild) == 1)
        {
            ploc = ptr;
            insertNode(val);
        }

        checkheight(ptr);

        balance(ptr, ptr->LeftChild);
        if (ptr == root) balance(NULL, ptr);
    }
    else if (QString::compare(val, ptr->data, Qt::CaseInsensitive) == 0)
    {
        loc = ptr;
        return 0;
    }

    return 0;
}

void AVL_Tree_NC::insertNode(QString value)
{
    if (loc != NULL)
        return;

    AVL_Node_NC* newnode = new AVL_Node_NC;
    newnode->data = value;

    if (ploc == NULL)
        root = newnode;
    else
    {
        if (QString::compare(value, ploc->data, Qt::CaseInsensitive) > 0)
            ploc->RightChild = newnode;
        else
            ploc->LeftChild = newnode;
    }
}

//start of balancing

void AVL_Tree_NC::balance(AVL_Node_NC* Parent_ptr, AVL_Node_NC* ptr)
{
    AVL_Node_NC* temp1;

    int balanceFactor = balance_factor(ptr);

    if (balanceFactor == 2)
    {
        int temp = balance_factor(ptr->RightChild);

        if (temp == -1)
        {
            ptr->RightChild = right_rotate(ptr->RightChild, ptr->RightChild->LeftChild);
        }
        else if (temp == -2 || temp == 2) return;

        temp1 = left_rotate(ptr, ptr->RightChild);
    }
    else if (balanceFactor == -2)
    {
        int temp = balance_factor(ptr->LeftChild);

        if (temp == 1)
        {
            ptr->LeftChild = left_rotate(ptr->LeftChild, ptr->LeftChild->RightChild);
        }
        else if (temp == -2 || temp == 2) return;

        temp1 = right_rotate(ptr, ptr->LeftChild);
    }
    else
        return;

    if (Parent_ptr != NULL)
    {
        if (Parent_ptr->LeftChild == ptr) Parent_ptr->LeftChild = temp1;
        else if (Parent_ptr->RightChild == ptr) Parent_ptr->RightChild = temp1;
    }
    else if (root == ptr) root = temp1;

    checkheight(Parent_ptr);
}

int AVL_Tree_NC::balance_factor(AVL_Node_NC* ptr)
{
    //balance factor = right tree height - left tree height

    if (ptr == NULL) return 0;

    if (ptr->LeftChild == NULL && ptr->RightChild == NULL)
    {
        return 0;
    }
    else if (ptr->LeftChild == NULL && ptr->RightChild != NULL)
    {
        if (ptr->RightChild->height >= 1)
            return 2;
        else
            return 1;
    }
    else if (ptr->LeftChild != NULL && ptr->RightChild == NULL)
    {
        if (ptr->LeftChild->height >= 1)
            return -2;
        else
            return -1;
    }
    else if (ptr->LeftChild != NULL && ptr->RightChild != NULL)
    {
        return (ptr->RightChild->height - ptr->LeftChild->height);
    }
}

AVL_Node_NC* AVL_Tree_NC::right_rotate(AVL_Node_NC* x, AVL_Node_NC* y)
{
    x->LeftChild = y->RightChild;
    y->RightChild = x;

    checkheight(x);
    checkheight(y);

    return y;
}

AVL_Node_NC* AVL_Tree_NC::left_rotate(AVL_Node_NC* x, AVL_Node_NC* y)
{
    x->RightChild = y->LeftChild;
    y->LeftChild = x;

    checkheight(x);
    checkheight(y);

    return y;
}

AVL_Node_NC* AVL_Tree_NC::search_NC(QString A, AVL_Node_NC* ptr)
{
    //QString::compare(val->name, ptr->data->name, Qt::CaseInsensitive);

    if (ptr == NULL) return NULL;

    if (QString::compare(A, ptr->data, Qt::CaseInsensitive) > 0)
    {
        return search_NC(A, ptr->RightChild);
    }
    else if (QString::compare(A, ptr->data, Qt::CaseInsensitive) < 0)
    {
        return search_NC(A, ptr->LeftChild);
    }
    else if (QString::compare(A, ptr->data, Qt::CaseInsensitive) == 0)
    {
        return ptr;
    }

    return NULL;

}

//end of AVL_Tree implementation for a club or country
