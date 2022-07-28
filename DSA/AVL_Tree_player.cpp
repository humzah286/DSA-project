#include "AVL_Tree_player.h"

//start of AVL_Tree implementation for player

AVL_Tree_player::AVL_Tree_player()
{
    root = NULL;
    ploc = NULL;
    loc = NULL;
}

bool AVL_Tree_player::isEmpty()
{
    return (root == NULL);
}

void AVL_Tree_player::checkheight(AVL_Node_player* ptr)
{
    if (ptr == NULL) return;

    int temp1 = -1, temp2 = -1;

    if (ptr->LeftChild != NULL) temp1 = ptr->LeftChild->height;
    if (ptr->RightChild != NULL) temp2 = ptr->RightChild->height;

    if (temp1 > temp2) ptr->height = temp1 + 1;
    else ptr->height = temp2 + 1;
}

int AVL_Tree_player::insertnode(player* val, AVL_Node_player* ptr)
{
    //int temp01 = -1; int temp02 = -1;

    if (ptr == NULL)
    {
        loc = NULL;
        if (ptr == root) { ploc = NULL; insertNode(val); }
        return 1;
    }

    //QString::compare(val->name, ptr->data->name, Qt::CaseInsensitive);

    if (QString::compare(val->name, ptr->data->name, Qt::CaseInsensitive) > 0)
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
    else if (QString::compare(val->name, ptr->data->name, Qt::CaseInsensitive) < 0)
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
    else if (QString::compare(val->name, ptr->data->name, Qt::CaseInsensitive) == 0)
    {
        loc = ptr;
        return 0;
    }

    return 0;
}

void AVL_Tree_player::insertNode(player* value)
{
    if (loc != NULL)
        return;

    AVL_Node_player* newnode = new AVL_Node_player;
    newnode->data = value;

    if (ploc == NULL)
        root = newnode;
    else
    {
        if (QString::compare(value->name, ploc->data->name, Qt::CaseInsensitive) > 0)
            ploc->RightChild = newnode;
        else
            ploc->LeftChild = newnode;
    }
}


//start of balancing


void AVL_Tree_player::balance(AVL_Node_player* Parent_ptr, AVL_Node_player* ptr)
{
    AVL_Node_player* temp1;

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


int AVL_Tree_player::balance_factor(AVL_Node_player* ptr)
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


AVL_Node_player* AVL_Tree_player::right_rotate(AVL_Node_player* x, AVL_Node_player* y)
{
    x->LeftChild = y->RightChild;
    y->RightChild = x;

    checkheight(x);
    checkheight(y);

    return y;
}


AVL_Node_player* AVL_Tree_player::left_rotate(AVL_Node_player* x, AVL_Node_player* y)
{
    x->RightChild = y->LeftChild;
    y->LeftChild = x;

    checkheight(x);
    checkheight(y);

    return y;
}

//end of balancing

player* AVL_Tree_player::search_player(QString A, AVL_Node_player* ptr)
{
    //QString::compare(val->name, ptr->data->name, Qt::CaseInsensitive);

    if (ptr == NULL) return NULL;

    if (QString::compare(A, ptr->data->name, Qt::CaseInsensitive) > 0)
    {
        return search_player(A, ptr->RightChild);
    }
    else if (QString::compare(A, ptr->data->name, Qt::CaseInsensitive) < 0)
    {
        return search_player(A, ptr->LeftChild);
    }
    else if (QString::compare(A, ptr->data->name, Qt::CaseInsensitive) == 0)
    {
        return ptr->data;
    }

    return NULL;

}

/*
void AVL_Tree_player::preorderTraversal(AVL_Node_player* temp)
{
    if (temp != NULL)
    {
        cout << temp->data << " " << temp->height << endl;
        preorderTraversal(temp->LeftChild);
        preorderTraversal(temp->RightChild);
    }
}


void AVL_Tree_player::inorderTraversal(AVL_Node_player* temp)
{
    if (temp != NULL)
    {
        inorderTraversal(temp->LeftChild);
        cout << temp->data << " " << temp->height << endl;
        inorderTraversal(temp->RightChild);
    }
}


void AVL_Tree_player::postorderTraversal(AVL_Node_player* temp)
{
    if (temp != NULL)
    {
        postorderTraversal(temp->LeftChild);
        postorderTraversal(temp->RightChild);
        cout << temp->data << " ";
    }
}

///start of delete function


void AVL_Tree_player::function(AVL_Node_player* temp1, AVL_Node_player* temp)
{
    if (temp != NULL && temp->RightChild != NULL)
    {
        function(temp, temp->RightChild);
    }

    int temp01 = -1; int temp02 = -1;

    if (temp1->LeftChild != NULL) temp01 = temp1->LeftChild->height;
    if (temp1->RightChild != NULL) temp02 = temp1->RightChild->height;

    if (temp01 > temp02) temp1->height = temp01 + 1;
    else temp1->height = temp02 + 1;
}


void AVL_Tree_player::deleteNode()
{
    if (isEmpty())
        return;

    if (loc == NULL)
        return;

    if (loc->LeftChild == NULL && loc->RightChild == NULL)
    {
        if (ploc == NULL)
        {
            delete loc;
            root = NULL;
            return;
        }

        if (ploc->LeftChild == loc)
            ploc->LeftChild = NULL;
        else if (ploc->RightChild == loc)
            ploc->RightChild = NULL;

        delete loc;
        return;
    }
    else if (loc->LeftChild == NULL && loc->RightChild != NULL)
    {
        if (ploc == NULL)
        {
            root = loc->RightChild;
            delete loc;
            return;
        }

        if (ploc->LeftChild == loc)
            ploc->LeftChild = loc->RightChild;


        if (ploc->RightChild == loc)
            ploc->RightChild = loc->RightChild;

        delete loc;
    }
    else if (loc->LeftChild != NULL && loc->RightChild == NULL)
    {
        if (ploc == NULL)
        {
            root = loc->LeftChild;
            delete loc;
            return;
        }

        if (ploc->LeftChild == loc)
            ploc->LeftChild = loc->LeftChild;


        if (ploc->RightChild == loc)
            ploc->RightChild = loc->LeftChild;

        delete loc;
    }
    else if (loc->LeftChild != NULL && loc->RightChild != NULL)
    {
        AVL_Node_player* temp = loc->LeftChild->RightChild;
        AVL_Node_player* temp1 = loc->LeftChild;

        while (temp != NULL && temp->RightChild != NULL)
        {
            temp1 = temp;
            temp = temp->RightChild;
        }

        if (temp == NULL)
            temp = temp1;

        //replacement node is temp

        if (temp == loc->LeftChild && temp->LeftChild != NULL)
        {
            loc->LeftChild = temp->LeftChild;
        }
        else if (temp == loc->LeftChild && temp->LeftChild == NULL)
        {
            loc->LeftChild = NULL;
        }
        else if (temp->LeftChild != NULL)
        {
            temp1->RightChild = temp->LeftChild;
        }

        if (ploc == NULL)
        {
            temp->RightChild = root->RightChild;
            temp->LeftChild = root->LeftChild;
            root = temp;
        }
        else
        {
            if (ploc->LeftChild == loc)
                ploc->LeftChild = temp;
            else if (ploc->RightChild == loc)
                ploc->RightChild = temp;

            temp->RightChild = loc->RightChild;
            temp->LeftChild = loc->LeftChild;
        }

        delete loc;

        if (temp->LeftChild != NULL)
        {
            AVL_Node_player* temp2 = temp->LeftChild->RightChild;
            AVL_Node_player* temp1 = temp->LeftChild;

            function(temp1, temp2);
        }

        int temp01 = -1; int temp02 = -1;

        checkheight(temp);
    }
}


int AVL_Tree_player::deletenode(Template val, AVL_Node_player* ptr)
{
    int temp01 = -1; int temp02 = -1;

    if (ptr == NULL)
        return 0;

    if (val > ptr->data)
    {
        if (deletenode(val, ptr->RightChild) == 1)
        {
            ploc = ptr;
            deleteNode();
        }

        checkheight(ptr);

        balance(ptr, ptr->RightChild);
        if (ptr == root) balance(NULL, ptr);
    }
    else if (val < ptr->data)
    {
        if (deletenode(val, ptr->LeftChild) == 1)
        {
            ploc = ptr;
            deleteNode();
        }

        checkheight(ptr);

        balance(ptr, ptr->LeftChild);
        if (ptr == root) balance(NULL, ptr);
    }
    else if (val == ptr->data)
    {
        loc = ptr;
        return 1;
    }

    return 0;
}
*/
///end of delete function

//end of AVL_Tree implementation for player
