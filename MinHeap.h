#ifndef MINHEAP_H
#define MINHEAP_H

#include <cmath>
#include <algorithm>
using namespace std;
class MinHeap {

private:
    int* arr;
    int capacity;


    void resize(int cap) {
        int* new_arr = new int[cap + 1];
        for (int i = 1; i <= size; i++) {
            new_arr[i] = arr[i];
        }
        arr = new_arr;
        delete[] new_arr;
        capacity = cap;
    }
    void swap(int i, int j) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
    void percolateUp(int index) {
        if (index <= 1) return;
        if (arr[index] < arr[index / 2]) {
            swap(index, index / 2);
            percolateUp(index / 2);
        }
    }
    void percolateDown(int index) {
        if (index > size / 2) {
        return;
        }
        int left = 2 * index + 1, right = left + 1;
        int smallestIndex = index;

        if (left <= size && arr[left] < arr[smallestIndex]) {
            smallestIndex = left;
        }
        if (right <= size && arr[right] < arr[smallestIndex]) {
            smallestIndex = right;
        }
        if (smallestIndex != index) {
            swap(index, smallestIndex);
            percolateDown(smallestIndex);
        }
    }

public:
    int size;
    MinHeap(int cap = 100) : capacity(cap), size(0) {
        arr = new int[cap + 1];
        arr[0] = 0; // Abandon arr[0]
    };
    ~MinHeap() {
        delete[] arr;
    }
    void push(int x) {
        if (size >= capacity * 0.75) {
            resize(2 * capacity);
        }
        arr[++size] = x;
        percolateUp(size); // Size has incremented by 1
    }

    int getMin() {
        return arr[1];
    }

    void pop() {
        arr[1] = arr[size--];
        percolateDown(1);
    }

};

#endif