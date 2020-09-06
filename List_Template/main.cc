#include <cstdio>
#include <cstdlib>
#include "list_template.h"

using namespace std;

//NODE ---------------------------------------------------------------------
template<class T> Node<T>::Node(T t) {
    previous = NULL;
    next = NULL;
    value = t;
}

template<class T> Node<T>::~Node() {
    delete &value;
}

template<class T> Node<T>* Node<T>::getPrevious() {
    return previous;
}

template<class T> Node<T>* Node<T>::getNext() {
    return next;
}

template<class T> T Node<T>::getValue() {
    return value;
}

template<class T> void Node<T>::setPrevious(Node<T>* p) {
    previous = p;
}

template<class T> void Node<T>::setNext(Node<T>* n) {
    next = n;
}

template<class T> void Node<T>::setValue(T v) {
    value = v;
}

template<class T> void Node<T>::print() {
    cout << value << '\n';
}

//LISTA ---------------------------------------------------------------------
template<class T> Lista<T>::Lista() {
    head = NULL;
    tail = NULL;
    size = 0;
}

template<class T> Lista<T>::~Lista() {
    Node<T>* aux = tail;
    while(aux) {
        aux = aux->getPrevious();
        delete aux->getNext();
    }

    size = 0;
}

template<class T> Node<T>* Lista<T>::getHead() {
    return head;
}

template<class T> Node<T>* Lista<T>::getTail() {
    return tail;
}
template<class T> int Lista<T>::getSize() {
    return size;
}

template<class T> void Lista<T>::append(Node<T>* node) {
    if (size == 0) {
        head = node;
        tail = node;
        size = 1;
    } else {
        while (node) {
            tail->setNext(node);
            node->setPrevious(tail);
            tail = node;
            node = node->getNext();
            size++;
        }
    }
}

template<class T> void Lista<T>::print() {
    Node<T>* aux = head;

    std::cout << '\n';
    while(aux) {
        aux->print();
        aux = aux->getNext();
    }
}

//MAIN -------------------------------------------------------
int main() {

    Node<char>* number1 = new Node<char>('a');
    Node<char>* number2 = new Node<char>('b');
    Lista<char>* lista_numeros = new Lista<char>();

    lista_numeros->append(number1);
    lista_numeros->append(number2);

    lista_numeros->print();

    return 0;
}
