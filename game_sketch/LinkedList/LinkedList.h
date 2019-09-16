#ifndef LinkedList_hpp
#define LinkedList_hpp

#include <Arduino.h>

template <class T>
class ListNode {
  public:
    T element;
    ListNode* next;
    ListNode* prev;

    ListNode(T element, ListNode* prev, ListNode* next) : element(element)
    {
      this->next = next;
      this->prev = prev;
    };
};

template <class T>
class LinkedList  {
  private:
    int length;
    ListNode<T>* head;
    ListNode<T>* tail;
    ListNode<T>* curr;
  public:
    LinkedList();
    LinkedList(const LinkedList<T>&);
    ~LinkedList();
    T& getCurrent();
    T& First() const;
    T& Last() const;
    int getLength();
    void Append(T);
    void DeleteLast();
    void DeleteFirst();
    void DeleteCurrent();
    bool next();
    bool moveToStart();
    bool prev();
    void Delete(T&);
    bool Search(T);
    void Clear();
    void PutFirstToLast();
    void Update(T elem);
    LinkedList& operator = (const LinkedList<T>&);
};

#include <LinkedList.h>

template <class T>
LinkedList<T>::LinkedList() {
    length = 0;
    head = NULL;
    tail = NULL;
    curr = NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> & list) {
    length = 0;
    head = NULL;
    tail = NULL;
    curr = NULL;

    ListNode<T> * temp = list.head;

    while(temp != NULL)
    {
        Append(temp->element);
        temp = temp->next;
    }
}

template <class T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T> & list)
{
    Clear();

    ListNode<T> * temp = list.head;

    while(temp != NULL)
    {
        Append(temp->element);
        temp = temp->next;
    }

    return *this;
}

template <class T>
LinkedList<T>::~LinkedList() {
    Clear();
}

template<class T>
T& LinkedList<T>::getCurrent()
{
  return curr->element;
}

template<class T>
T& LinkedList<T>::First() const
{
  return head->element;
}

template<class T>
T& LinkedList<T>::Last() const
{
  return tail->element;
}

template<class T>
int LinkedList<T>::getLength()
{
  return length;
}

template <class T>
void LinkedList<T>::Append(T element)
{
    ListNode<T> * node = new ListNode<T>(element, tail, NULL);

    if(length == 0)
        curr = tail = head = node;
    else {
        tail->next = node;
        tail = node;
    }

    length++;

}

template <class T>
void LinkedList<T>::DeleteLast()
{
    if(length == 0)
      return;
    curr = tail;
    DeleteCurrent();
}

template <class T>
void LinkedList<T>::DeleteFirst()
{
    if(length == 0)
      return;
    curr = head;
    DeleteCurrent();
}

template <class T>
bool LinkedList<T>::next()
{
    if(length == 0)
        return false;

    if(curr->next == NULL)
        return false;

    curr = curr->next;
    return true;
}

template <class T>
bool LinkedList<T>::moveToStart()
{
    curr = head;
    return length != 0;
}

template<class T>
bool LinkedList<T>::prev()
{
    if(length == 0)
        return false;

    if(curr->prev != NULL)
        return false;

    curr = curr->prev;
    return true;
}

template <class T>
void LinkedList<T>::Delete(T & elem)
{
    if(Search(elem))
        DeleteCurrent();
}

template <class T>
void LinkedList<T>::DeleteCurrent()
{
    if(length == 0)
        return;
    length--;
    ListNode<T> * temp = curr;

    if(temp->prev != NULL)
        temp->prev->next = temp->next;
    if(temp->next != NULL)
        temp->next->prev = temp->prev;

    if(length == 0)
        head = curr = tail = NULL;
    else if(curr == head)
        curr = head = head->next;
    else if(curr == tail)
        curr = tail = tail->prev;
    else
        curr = curr->prev;

     delete temp;
}

template <class T>
bool LinkedList<T>::Search(T elem)
{
    if(length == 0)
        return false;
    if(moveToStart())
        do {
            if(curr->element == elem)
                return true;
        } while (next());
    return false;
}

template <class T>
void LinkedList<T>::PutFirstToLast()
{
  if(length < 2)
    return;
  ListNode<T>* temp = head->next;
  head->next->prev = NULL;
  head->next = NULL;
  head->prev = tail;
  tail->next = head;
  tail = head;
  head = temp;
}

template <class T>
void LinkedList<T>::Update(T elem)
{
    if(Search(elem))
        curr->element = elem;
}

template <class T>
void LinkedList<T>::Clear()
{
    if(length == 0)
        return;
    ListNode<T> * temp = head;

    while(temp != NULL)
    {
        head = head->next;
        delete temp;
        temp = head;
    }

    head = curr = tail = NULL;

}

#endif
