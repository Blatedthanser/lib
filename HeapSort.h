#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "ISort.h"
#include "MaxHeap.h"

/**
 * Not stable.
 * Best case: θ(N), worst case: θ(NlogN)
 * Space complexity: θ(1)
 * Note: Bad cache performance.
 */
template <class T>
class HeapSort : public ISort<T> {
public:
    void sort(T* arr, int size) override {
        MaxHeap heap = MaxHeap(size);
        heap.buildHeap(arr, size);
        int* new_arr = heap.getArray();
        for (int i = 0; i < size; i++) {
            heap.putMaxToEnd();
        }
        for (int i = 0; i < size; i++) {
            arr[i] = new_arr[i];
        }
        delete[] new_arr;
    }
};
#endif