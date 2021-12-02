#include <iostream>
#include "Utility.h"
const int max_list = 100;

template <class Node_entry>
struct Node{
    Node_entry entry;
    Node<Node_entry> *next;
    Node();
    Node(Node_entry, Node<Node_entry> *link = NULL);
    int position;
};

template <class Node_entry>
Node<Node_entry>::Node(){
    next = NULL;
};

template <class Node_entry>
Node<Node_entry>::Node(Node_entry, Node<Node_entry> *link = NULL){
    entry = Node_entry;
    link = next;
};

template <class List_entry>
class List {
public:
//  methods of the List ADT
   List();
   ~List();
   List(const List<List_entry> &origin); //copy constructor
   void traverse(void (*visit)(List_entry &));
   Error_code insert(int position, const List_entry &x);
   Error_code retrieve(int position, List_entry &x) const;
   Error_code replace(int position, List_entry &x);
   Error_code remove(int position);
   bool empty() const;
   bool full() const;
   void clear();
   int size();
   void operator = (const List<List_entry> &origin);  // overload assignment
protected:
//  data members for a contiguous list implementation
   int count;
   Node<List_entry> *head;
   Node<List_entry> *set_position(int position) const;
};

template <class List_entry>
List<List_entry>::List()
/*
Post: List initialized.
*/
{
    count = 0;
    head = NULL;
}

template <class List_entry>
List<List_entry>::List(const List<List_entry> &origin)
/*
Post: List initialized by copying from origin list
*/
{
    count = origin.count;
    Node<List_entry> *new_node, *old_node = origin.head;
    if(old_node == NULL) head = NULL;
    else {
        new_node = head = new Node<List_entry>(old_node->entry)
        while (old_node->next != NULL)
        {
            old_node = old_node->next;
            new_node->next = new Node<List_entry>(old_node->entry);
            new_node = new_node->next;
        }
    }

}
template <class List_entry>
void List<List_entry>::operator = (const List<List_entry> &origin)
/*
Post: The list assigned to copy a parameter
*/
{
    List new_copy(origin);
    clear();
    count = new_copy.count;
    head = new_copy.head;
    new_copy.count = 0;
    new_copy.head = NULL;
}

template <class List_entry>
List<List_entry>::~List()
/*
Post: The list is empty: all entries have been removed
*/
{
    clear();
}

template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry &x)
/*
Post: a Node contains the value of x linked at the last position in the list
*/
{
    Error_code result;
    Node<List_entry> *node = new Node();
    node->entry = x;
    if(count >= max_list)
        result = overflow;
    else if(count == 0){
        head = node;
        node->position = count;
        count++;
        result = success;
    }
    else {
        set_position(count)->next = node;
        node->position = count;
        count++;
        result = success;
    }
    return result;
};

template <class List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry &x) const
/*
Post: value stored in the node whose position matches is assigned to x
*/
{
    Error_code result;
    Node<List_entry> *current;
    if(position < 0 || position >= count)
        result = range_error;
    else {
        current = set_position(position);
        x = current->entry;
        result = success;
    }
    return result;
};

template <class List_entry>
int List<List_entry>::size()
/*
Post: return an integer stand for how many entries are inside of the list
*/
{
    int result;
    result = count;
    return result;
};

template <class List_entry>
bool List<List_entry>::empty() const
/*
Post:   return bollean value, true means no entry is inside of the list
        false means there is at least 1 entry inside of the list
*/
{
    return count <= 0;
};

template <class List_entry>
bool List<List_entry>::full() const
/*
Post:   return bollean value, true means the number of entries inside of the list
        is the max number of the list, false means not
*/
{
    return false;
};

template <class List_entry>
void List<List_entry>::clear()
/*
Pre:    this list holds some data
Post:   list is cleared
*/
{
    Node<List_entry> *p, *q;
    for(p = head; p; q = p){
        q = p->next;
        delete p;
    }
    count = 0;
    head = NULL;
};

template <class List_entry>
Error_code List<List_entry>::replace(int position, List_entry &x)
/*
Post: if 0 <= position <= count, the entry located in the postion is
      replaced by x, otherwise return an error code of range_error
*/
{
    Node<List_entry> *current;
    if(position < 0 || position >= count) return range_error;
    else {
        current = set_position(position);
        current->entry = x;
        return success;
    }
}

template <class List_entry>
Error_code List<List_entry>::remove(int position)
/*
Post: if 0 <= position <= count, the entry located in the postion is
      removed and entries after this position move forward for 1 position,
      otherwise return an error code of range_error
*/
{
    Node<List_entry> *prior, *current;
    if(count == 0) return fail;
    if(position < 0 || position >= count) return range_error;
    if(position > 0){
        prior = set_position(position - 1);
        current = prior->next;
        prior->next = current->next;
    }
    else {
        current = head;
        head = head->next;
    }
    x = current->entry;
    delete current;
    count--;
    return success;
}

template <class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &))

{
    Node<List_entry> *q;
    for(q = head; q; q = q->next)
        (*visit)(q->entry);
}