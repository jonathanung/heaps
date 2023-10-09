#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @brief MaxHeap class
 * 
 * @author Jonathan Ung
 */
class MaxHeap {
    private:
        std::vector<int> heap;
        int parent(int i) { return (i-1)/2; }
        int left(int i) { return (2*i + 1); }
        int right(int i) { return (2*i + 2); }

    public:
        MaxHeap() { heap = std::vector<int>(); }
        MaxHeap(std::vector<int>);
        ~MaxHeap() {}
        void heapify(int);
        void insert(int);
        int extract();
        int peek() { return heap[0]; }
        void mergeWith(MaxHeap);
        friend MaxHeap merge(MaxHeap, MaxHeap);
        void clear();


        void show();
        friend std::ostream& operator<<(std::ostream&, MaxHeap);
};

MaxHeap::MaxHeap(std::vector<int> v){
    heap = std::vector<int>();
    for (int i = 0; i < v.size(); i++) {
        insert(v[i]);
    }
}

void MaxHeap::heapify(int curr){
    int largest = curr;
    if (left(curr) < heap.size() && heap[left(curr)] > heap[largest])
        largest = left(curr);
    if (right(curr) < heap.size() && heap[right(curr)] > heap[largest])
        largest = right(curr);
    if (largest != curr)
    {
        std::swap(heap[curr], heap[largest]);
        heapify(largest);
    }
}

void MaxHeap::insert(int val) { // O(1) to O(logb2(n))
    heap.push_back(val);
    for (int i = heap.size()-1; i > 0; i = i/2) {
        if (heap[i] > heap[i/2]) {
            std::swap(heap[i], heap[i / 2]);
        } else {
            break;
        }
    }
}

int MaxHeap::extract(){
    if (heap.size() == 0) {
        throw std::invalid_argument("You cannot dequeue from an empty heap!");
    }
    int temp = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapify(0);
    return temp;
}

void MaxHeap::show() {
    std::cout << "Heap: [";
    for (int i = 0; i < heap.size(); i++) {
        std::cout << heap[i];
        if (i < heap.size()-1) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;
}

std::ostream& operator<<(std::ostream& o, MaxHeap mH) {
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

void MaxHeap::mergeWith(MaxHeap other) {
    for (int i = 0; i < other.heap.size(); i++) {
        insert(other.heap[i]);
    }
    other.clear();
}

MaxHeap merge(MaxHeap mH1, MaxHeap mH2) {
    MaxHeap mergedHeap = MaxHeap();
    for (int i = 0; i < mH1.heap.size(); i++) {
        mergedHeap.insert(mH1.heap[i]);
    }
    for (int i = 0; i < mH2.heap.size(); i++) {
        mergedHeap.insert(mH2.heap[i]);
    }
    return mergedHeap;
}

void MaxHeap::clear() {
    heap.clear();
}

#endif