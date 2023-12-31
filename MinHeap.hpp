#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @brief MinHeap class
 * 
 * @author Jonathan Ung
 */
class MinHeap {
    private:
        std::vector<int> heap;
        static int parent(int i) { return (i-1)/2; }
        static int left(int i) { return (2*i + 1); }
        static int right(int i) { return (2*i + 2); }

    public:
        MinHeap() { heap = std::vector<int>(); }
        MinHeap(std::vector<int>);
        ~MinHeap() {}
        void heapify(int);
        void insert(const int);
        int extract();
        int peek() const { return heap[0]; }
        void mergeWith(MinHeap &);
        friend MinHeap merge(const MinHeap &, const MinHeap &);
        void clear();

        void show() const;
        friend std::ostream& operator<<(std::ostream&, const MinHeap &);
};

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

void MinHeap::insert(const int val) { // O(1) to O(logb2(n))
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

void MinHeap::show() const {
    std::cout << "Heap: [";
    for (int i = 0; i < heap.size(); i++) {
        std::cout << heap[i];
        if (i < heap.size()-1) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;
}

std::ostream& operator<<(std::ostream& o, const MinHeap &mH) {
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

void MinHeap::mergeWith(MinHeap & other) {
    for (int i = 0; i < other.heap.size(); i++) {
        insert(other.heap[i]);
    }
    other.clear();
}

MinHeap merge(const MinHeap & mH1, const MinHeap & mH2) {
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