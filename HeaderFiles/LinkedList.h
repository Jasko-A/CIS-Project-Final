/**
LinkedList Class
Written by: Austin Bohannon

Made to work with pointers to Food objects so that no data has to be copied,
it's just organized.
**/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Food.h"

class LinkedList
{
  int count;
  struct node
  {
    Food * data;
    node * next, * back;
  };
  node * head, * tail;
public:
  LinkedList();
  ~LinkedList();

  bool addItem(Food * newFood);
  bool deleteItem(int &id);
  bool itemExists(int &id);
  bool search(int &id, Food *& returnedItem);
  void visitAll(void visit(Food *));
  void printAll();
  int getCount() const {return count;}
};

#endif
