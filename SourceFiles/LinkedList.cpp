LinkedList::LinkedList()
{
  count = 0;
  
  head = new node;
  tail = new tail;
  
  head.data = NULL;
  head.next = tail;
  head.back = tail;
  
  tail.data = NULL;
  tail.next = head;
  tail.back = head;
}

LinkedList::~LinkedList()
{
  node temp = head, tempNext;
  while (temp != tail)
  {
    tempNext = temp.next;
    delete temp;
    temp = tempNext;
  }
  delete tail;
}

void LinkedList::addItem(Food * newFood)
{
  node newNode = new node;
  newNode.data = newFood;
  
  node temp = head;
  while(temp.next != tail && newFood.getKey() > temp.data->getKey())
    temp = temp.next;
  newNode.next = temp.next;
  temp.next = newNode;
}

bool LinkedList::deleteItem(int &id)
{

}

bool LinkedList::itemExists(int &id)
{

}

bool LinkedList::search(int &id, Food * returnedItem)
{

}
