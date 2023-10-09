#ifndef MAX_NODE_HEAP_HPP
#define MAX_NODE_HEAP_HPP

#include "HeapNode.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @brief MaxNodeHeap class
 * 
 * @author Jonathan Ung
 */
template <class T>
class MaxNodeHeap {
    private:
        std::vector<HeapNode<T>> heap;
        static int parent(int i) { return (i-1)/2; }
        static int left(int i) { return (2*i + 1); }
        static int right(int i) { return (2*i + 2); }

    public:
        MaxNodeHeap() { heap = std::vector<HeapNode<T>>(); }
        ~MaxNodeHeap() {}
        void heapify(int);
        void insert(const T, const int);
        T extract();
        HeapNode<T> extractNode();
        T peek() const { return heap[0].data; }
        void mergeWith(MaxNodeHeap<T> &);
        template <class U>
        friend MaxNodeHeap<U> merge(const MaxNodeHeap<U>&, const MaxNodeHeap<U>&);
        void clear();

        void show() const;
        template <class U>
        friend std::ostream& operator<<(std::ostream&, const MaxNodeHeap<U>&);
};

template <class T>
void MaxNodeHeap<T>::heapify(int curr){
    int largest = curr;
    if (left(curr) < heap.size() && heap[left(curr)].weight > heap[largest].weight)
        largest = left(curr);
    if (right(curr) < heap.size() && heap[right(curr)].weight > heap[largest].weight)
        largest = right(curr);
    if (largest != curr)
    {
        std::swap(heap[curr], heap[largest]);
        heapify(largest);
    }
}

template <class T>
void MaxNodeHeap<T>::insert(const T data, const int weight) { // O(1) to O(logb2(n))
    HeapNode<T> val = HeapNode<T>(data, weight);
    heap.push_back(val);
    for (int i = heap.size()-1; i > 0; i = i/2) {
        if (heap[i].weight > heap[i/2].weight) {
            std::swap(heap[i], heap[i / 2]);
        } else {
            break;
        }
    }
}

template <class T>
T MaxNodeHeap<T>::extract(){
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
HeapNode<T> MaxNodeHeap<T>::extractNode(){
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
void MaxNodeHeap<T>::show() const{
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
std::ostream& operator<<(std::ostream& o, const MaxNodeHeap<T> & mH) {
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
void MaxNodeHeap<T>::mergeWith(MaxNodeHeap<T> & other) {
    for (int i = 0; i < other.heap.size(); i++) {
        insert(other.heap[i]);
    }
    other.clear();
}

template <class T>
MaxNodeHeap<T> merge(const MaxNodeHeap<T> & mH1, const MaxNodeHeap<T> & mH2) {
    MaxNodeHeap<T> mergedHeap = MaxNodeHeap<T>();
    for (int i = 0; i < mH1.heap.size(); i++) {
        mergedHeap.insert(mH1.heap[i]);
    }
    for (int i = 0; i < mH2.heap.size(); i++) {
        mergedHeap.insert(mH2.heap[i]);
    }
    return mergedHeap;
}

template <class T>
void MaxNodeHeap<T>::clear() {
    heap.clear();
}

#endif