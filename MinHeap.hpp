#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <iostream>
#include <vector>
#include <algorithm>

class MinHeap {
    private:
        std::vector<int> heap;
        int parent(int i) { return (i-1)/2; }
        int left(int i) { return (2*i + 1); }
        int right(int i) { return (2*i + 2); }

    public:
        MinHeap();
        MinHeap(std::vector<int>);
        void heapify(int);
        void insert(int);
        int extract();
        int peek() { return heap[0]; }
        void mergeWith(MinHeap);
        friend MinHeap merge(MinHeap, MinHeap);
        void clear();

        void show();
        friend std::ostream& operator<<(std::ostream&, MinHeap);
};

MinHeap::MinHeap(){
    heap = std::vector<int>();
}

MinHeap::MinHeap(std::vector<int> v){
    heap = std::vector<int>();
    for (int i = 0; i < v.size(); i++) {
        insert(v[i]);
    }
}

void MinHeap::heapify(int curr){
    int smallest = curr;
    if (left(curr) < heap.size() && heap[left(curr)] < heap[smallest])
        smallest = left(curr);
    if (right(curr) < heap.size() && heap[right(curr)] < heap[smallest])
        smallest = right(curr);
    if (smallest != curr)
    {
        std::swap(heap[curr], heap[smallest]);
        heapify(smallest);
    }
}

void MinHeap::insert(int val) { // O(1) to O(logb2(n))
    heap.push_back(val);
    for (int i = heap.size()-1; i > 0; i = i/2) {
        if (heap[i] < heap[i/2]) {
            std::swap(heap[i], heap[i / 2]);
        } else {
            break;
        }
    }
}

int MinHeap::extract(){
    if (heap.size() == 0) {
        throw std::invalid_argument("You cannot dequeue from an empty heap!");
    }
    int temp = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapify(0);
    return temp;
}

void MinHeap::show() {
    std::cout << "Heap: [";
    for (int i = 0; i < heap.size(); i++) {
        std::cout << heap[i];
        if (i < heap.size()-1) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;
}

std::ostream& operator<<(std::ostream& o, MinHeap mH) {
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

void MinHeap::mergeWith(MinHeap other) {
    for (int i = 0; i < other.heap.size(); i++) {
        insert(other.heap[i]);
    }
    other.clear();
}

MinHeap merge(MinHeap mH1, MinHeap mH2) {
    MinHeap mergedHeap = MinHeap();
    for (int i = 0; i < mH1.heap.size(); i++) {
        mergedHeap.insert(mH1.heap[i]);
    }
    for (int i = 0; i < mH2.heap.size(); i++) {
        mergedHeap.insert(mH2.heap[i]);
    }
    return mergedHeap;
}

void MinHeap::clear() {
    heap.clear();
}

#endif