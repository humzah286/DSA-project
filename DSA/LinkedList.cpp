#include "LinkedList.h"


LinkedList::LinkedList()
{
    start = NULL;
    last = NULL;
    PredLoc_ = NULL;
    Loc_ = NULL;
}


bool LinkedList::isEmpty()		//definition of funtion
{
    if (start == NULL)		//if start is NULL, that means List doesn't exists
        return true;
    else
        return false;
}


void LinkedList::InsertAtFront(player* value)	//definition of function
{
    ListNode* newnode = new ListNode();		//creating a new node for entering in front

    newnode->data = value;	//assigning value to newnode's data


    if (isEmpty())			//checking if List is empty or not
    {
        start = newnode;
        last = newnode;
    }
    else       //if List is not empty, newnode will be added to start
    {
        newnode->next = start;
        start = newnode;
    }
}

void LinkedList::InsertAtEnd(player* value)	//definition of function
{
    ListNode* newnode = new ListNode();		//creating a newnode for entering at the end

    newnode->data = value;			//assigning value to newnode's data

    if (isEmpty())			//checking if List is empty or not
    {
        start = newnode;
        last = newnode;
    }
    else                     //if List is not Empty, then adding the newnode at the end
    {
        last->next = newnode;
        last = newnode;
    }
}

/*void LinkedList::printList()		//definition of funtion
{
    if (!isEmpty())		//following block will only run if List is not empty
    {
        ListNode* temp = start;		//temporary ListNode pointer

        while (temp != NULL)		//printing till the end of List
        {
            cout << temp->data << "\t";
            temp = temp->next;
        }

    }
    else               //printing “List is empty” if condition fails
    {
        cout << "List is Empty!" << endl;
    }

}


void LinkedList::Search(Template value)		//definition of function
{
    Loc_ = start;			//assigning Loc_ as start and PredLoc_ as NULL to obtain a starting point

    PredLoc_ = NULL;

    if (isEmpty()) {		//if List is Empty, no need for search, hence returning the function
        return;
    }

    while (Loc_ != NULL && Loc_->data < value)		//if Loc_ is NULL, that means Loc_ has reached end of List, hence need to break the loop
    {
        PredLoc_ = Loc_;			//advancing the Loc_ and PredLoc_ pointers to next nodes

        Loc_ = Loc_->next;
    }

    if (Loc_ != NULL && Loc_->data != value)		//if Loc_'s data is not equal to value, assigning Loc_ as NULL as an indication
        Loc_ = NULL;
}


void LinkedList::InsertSorted(Template value)	//definition of function
{
    Search(value);			//to obtain the nearest value to "value", using PredLoc_ and Loc_

    if (Loc_ == NULL)		//if Loc_ is NULL, that means value was not found using Search()
    {
        if (PredLoc_ == NULL)		//if PredLoc_ is NULL, value is to be inserted at front
            InsertAtFront(value);
        else                        //else value is to be inserted in somewhere middle, using PredLoc_ pointer
        {
            ListNode* newnode = new ListNode();		//creating a new node that is to be added.

            newnode->data = value;									//assigning value to newnodes's data

            newnode->next = PredLoc_->next;								//reassigning pointer next of newnode

            PredLoc_->next = newnode;									//assigninng PredLoc_ to newnode pointer

            if (PredLoc_ == last)		//if PredLoc_ was of the last node, then we have to update the "last" pointer.
                last = newnode;
        }
    }
    else                   //if Loc_ is not NULL, then value is already present in List, and duplication is not allowed.
    {
        cout << value << " already exists in List!" << endl;
    }
}




void LinkedList::Delete(Template value)		//definition of function
{
    if (isEmpty())	//if List is Empty, then we cant delete a value.
    {
        cout << "List is already Empty, can not delete the specified element!" << endl;
    }

    Search(value);			//using Search() function to locate the position of value that we want to delete

    if (Loc_ != NULL && Loc_->data == value)		//Loc_ has to be non-null for the value to exist in List
    {
        if (PredLoc_ == NULL)			//if PredLoc_ is NULL, it means first value has to be deleted
        {
            ListNode* temp;		//temporary variable of Listnode.
            temp = start->next;			//assigning value of start->next to temp

            delete start;				//deleting 1st node
            start = temp;				//assigning temp to start. hence now 2nd node is now the first one
        }
        else                  //if value is somewhere between the List, following code will run
        {
            PredLoc_->next = Loc_->next;	//updating previous node of Loc_ (PredLoc_) then deleting Loc_
            delete Loc_;
        }
    }
    else                  //if Loc_ is NULL, it means value does not exists in the List.
    {
        cout << "value does not exists in the list!" << endl;
    }
}


void LinkedList::DestroyList()		//definition of function
{
    if (isEmpty())			//if List is Empty, List doesn't needs to be destroyed.
        cout << "List is already Empty!" << endl;

    PredLoc_ = NULL;		//initializing PredLoc_ to NULL and Loc_ to start, run a complete cycle in List

    Loc_ = start;

    do {		//deleting each and every node in List

        PredLoc_ = Loc_;			//advancing Loc_ and PredLoc_
        Loc_ = Loc_->next;

        delete PredLoc_;		//using delete operator

    } while (Loc_ != NULL);			//if Loc_ is NULL, it means every node from the List has been deleted


    start = NULL;		//assigning NULL to start and last pointers
    last = NULL;
}*/



