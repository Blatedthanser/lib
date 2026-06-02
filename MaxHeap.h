#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <cmath>
#include <algorithm>
using namespace std;
class MaxHeap {

private:
    int* arr;
    int capacity;

    void resize(int cap) {
        int* new_arr = new int[cap + 1];
        for (int i = 1; i <= size; i++) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
        capacity = cap;
    }
    void swap(int i, int j) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
    void percolateUp(int index) {
        if (index <= 1) return;
        if (arr[index] > arr[index / 2]) {
            swap(index, index / 2);
            percolateUp(index / 2);
        }
    }
    void percolateDown(int index) {
        if (index > size / 2) {
            return;
        }
        int left = 2 * index, right = 2 * index + 1;
        int biggestIndex = index;

        if (left <= size && arr[left] > arr[biggestIndex]) {
            biggestIndex = left;
        }
        if (right <= size && arr[right] > arr[biggestIndex]) {
            biggestIndex = right;
        }
        if (biggestIndex != index) {
            swap(index, biggestIndex);
            percolateDown(biggestIndex);
        }
    }

protected:

    int* getArray() {
        return arr;
    }
    void putMaxToEnd() {
        int max = arr[1];
        arr[1] = arr[size--];
        percolateDown(1);
        arr[size + 1] = max;
    }

    template <class T>
    friend class HeapSort;

public:
    int size;
    MaxHeap(int cap = 100) : capacity(cap), size(0) {
        arr = new int[cap + 1];
        arr[0] = 0; // Abandon arr[0]
    };
    ~MaxHeap() {
        delete[] arr;
    }
    void push(int x) {
        if (size >= capacity * 0.75) {
            resize(2 * capacity);
        }
        arr[++size] = x;
        percolateUp(size); // Size has incremented by 1
    }

    int getMax() {
        return arr[1];
    }

    void pop() {
        arr[1] = arr[size--];
        percolateDown(1);
    }

    /**
     * Use _arr to build a MaxHeap.
     * Doesn't mutate _arr
     */
    void buildHeap(int* _arr, int _size) {
        size = _size;
        resize(size + 1);
        
        for (int i = 0; i < _size; i++) {
            arr[i + 1] = _arr[i];
        }
        for (int i = size / 2; i > 0; i--) {
            percolateDown(i);
        }
    }

};

#endif