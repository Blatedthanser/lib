#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include "ISort.h"

/**
 * Not stable.
 * θ(N²).
 * Space complexity: θ(1)
 */
template <class T>
class SelectionSort : public ISort<T> {
public:
    using ISort<T>::swap;
    void sort(T* arr, int size) override {
        for (int i = 0; i < size; i++) {
            int min_i = i;
            for  (int j = i; j < size; j++) {
                if (arr[j] < arr[min_i]) {
                    min_i = j;
                }
            }
            swap(arr, i, min_i);
        }
    }
};

#endif