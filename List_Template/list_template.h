#ifndef _LIST_TEMPLATE
#define _LIST_TEMPLATE

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

template <class T> class Node {
private:
    Node<T>* previous;
    Node<T>* next;
    T value;

public:
    Node(T);
    ~Node();

    //Getters
    Node<T>* getPrevious();
    Node<T>* getNext();
    T getValue();

    //Setters
    void setPrevious(Node<T>*);
    void setNext(Node<T>*);
    void setValue(T);

    //Other
    void print();
};

template <class T> class Lista {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    Lista();
    ~Lista();

    Node<T>* getHead();
    Node<T>* getTail();
    int getSize();

    //void setHead(Node<T>*);
    //void setTail(Node<T>*);

    void append(Node<T>*);
    void print();
    Lista<T>* operator + (const Lista<T>&);
};

#endif
