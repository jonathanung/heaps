#ifndef HEAP_NODE_HPP
#define HEAP_NODE_HPP

#include <iostream>

template <class T>
/**
 * @brief HeapNode class
 * 
 * @author Jonathan Ung
 */
class HeapNode{
    public:
        T data;
        int weight;
        HeapNode(T, int);
        void show();

        template <class U>
        friend std::ostream& operator<<(std::ostream &, HeapNode<U>);
};

template <class T>
HeapNode<T>::HeapNode(T d, int w) {
    data = d;
    weight = w;
}

template <class T>
void HeapNode<T>::show() {
    std::cout << "{" << data << ", " << weight << "}";
}

template <class T>
std::ostream& operator<<(std::ostream& o, HeapNode<T> hN) {
    o << "{" << hN.data << ", " << hN.weight << "}";
    return o;
}
#endif