#ifndef MIN_NODE_HEAP_HPP
#define MIN_NODE_HEAP_HPP

#include "HeapNode.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
class MinNodeHeap {
    private:
        std::vector<HeapNode<T>> heap;
        int parent(int i) { return (i-1)/2; }
        int left(int i) { return (2*i + 1); }
        int right(int i) { return (2*i + 2); }

    public:
        MinNodeHeap() { heap = std::vector<HeapNode<T>>(); } 
        ~MinNodeHeap() {}
        void heapify(int);
        void insert(T, int);
        T extract();
        HeapNode<T> extractNode();
        T peek() { return heap[0].data; }
        void mergeWith(MinNodeHeap<T>);
        template <class U>
        friend MinNodeHeap<U> merge(MinNodeHeap<U>, MinNodeHeap<U>);
        void clear();


        void show();
        template <class U>
        friend std::ostream& operator<<(std::ostream&, MinNodeHeap<U>);
};

template <class T>
void MinNodeHeap<T>::heapify(int curr){
    int smallest = curr;
    if (left(curr) < heap.size() && heap[left(curr)].weight < heap[smallest].weight)
        smallest = left(curr);
    if (right(curr) < heap.size() && heap[right(curr)].weight < heap[smallest].weight)
        smallest = right(curr);
    if (smallest != curr)
    {
        std::swap(heap[curr], heap[smallest]);
        heapify(smallest);
    }
}

template <class T>
void MinNodeHeap<T>::insert(T data, int weight) { // O(1) to O(logb2(n))
    HeapNode<T> val = HeapNode<T>(data, weight);
    heap.push_back(val);
    for (int i = heap.size()-1; i > 0; i = i/2) {
        if (heap[i].weight < heap[i/2].weight) {
            std::swap(heap[i], heap[i / 2]);
        } else {
            break;
        }
    }
}

template <class T>
T MinNodeHeap<T>::extract(){
    if (heap.size() == 0) {
        throw std::invalid_argument("You cannot dequeue from an empty heap!");
    }
    T temp = heap[0].data;
    heap[0] = heap.back();
    heap.pop_back();
    heapify(0);
    return temp;
}

template <class T>
HeapNode<T> MinNodeHeap<T>::extractNode(){
    if (heap.size() == 0) {
        throw std::invalid_argument("You cannot dequeue from an empty heap!");
    }
    HeapNode<T> temp = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapify(0);
    return temp;
}

template <class T>
void MinNodeHeap<T>::show() {
    std::cout << "Heap: [";
    for (int i = 0; i < heap.size(); i++) {
        std::cout << heap[i];
        if (i < heap.size()-1) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;
}

template <class T>
std::ostream& operator<<(std::ostream& o, MinNodeHeap<T> mH) {
    o << "Heap: [";
    for (int i = 0; i < mH.heap.size(); i++) {
        o << mH.heap[i];
        if (i < mH.heap.size()-1) {
            o << ",";
        }
    }
    o << "]" << std::endl;
    return o;
}

template <class T>
void MinNodeHeap<T>::mergeWith(MinNodeHeap<T> other) {
    for (int i = 0; i < other.heap.size(); i++) {
        insert(other.heap[i]);
    }
    other.clear();
}

template <class T>
MinNodeHeap<T> merge(MinNodeHeap<T> mH1, MinNodeHeap<T> mH2) {
    MinNodeHeap<T> mergedHeap = MinNodeHeap<T>();
    for (int i = 0; i < mH1.heap.size(); i++) {
        mergedHeap.insert(mH1.heap[i]);
    }
    for (int i = 0; i < mH2.heap.size(); i++) {
        mergedHeap.insert(mH2.heap[i]);
    }
    return mergedHeap;
}

template <class T>
void MinNodeHeap<T>::clear() {
    heap.clear();
}

#endif