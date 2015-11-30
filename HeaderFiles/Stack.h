/**
Stack class (template)
Written by: Austin Bohannon

Made to work with pointers to objects so that no data has to be copied,
it's just organized.
**/

#ifndef OUR_STACK_H
#define OUR_STACK_H

template<class T>
class Stack
{
  int count;
  struct node
  {
    T data;
    node * next;
  };
  node * head;
public:
  Stack(){count = 0; head = NULL;}
  ~Stack();

  void push(T newItem);
  bool pop(T &passedItem);

  bool getTop(T &passedItem) const;
  int getCount() const {return count;}
  bool isEmpty() const {return count == 0;}
};

template<class T>
Stack<T>::~Stack()
{
  //Create node variables
  node * temp = head, *tempNext;
  //Delete all nodes
  while(temp)
  {
    tempNext = temp;
    delete temp;
    temp = tempNext;
  }
}

template<class T>
void Stack<T>::push(T newItem)
{
  //Create node
  node * newNode = new node;
  newNode->data = newItem;
  //Put node in stack
  newNode->next = head;
  head = newNode;
  //Increase count
  count++;
}

template<class T>
bool Stack<T>::pop(T &passedItem)
{
  if(!head)
    return false;
  //Delete head
  passedItem = head->data;
  node * temp = head->next;
  delete head;
  head = temp;
  //decrease count
  count--;
  return true;
}

template<class T>
bool Stack<T>::getTop(T &passedItem) const
{
  if(!head)
    return false;
  passedItem = head->data;
  return true;
}

#endif
