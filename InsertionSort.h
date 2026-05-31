#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "ISort.h"

/**
 * Stable.
 * Best case: θ(N), worst case: θ(N²)
 * Space complexity: θ(1)
 * Note: Time is proportional to numbers of inversions.
 */
template<class T>
class InsertionSort : public ISort<T> {
public:
    void sort(T* arr, int size) override {
        int sortedIndex = 0;
        for (; sortedIndex < size - 1; sortedIndex++) {
            int traveller = sortedIndex + 1;
            while (traveller > 0 && arr[traveller - 1] > arr[traveller]) {
                ISort<T>::swap(arr, traveller - 1, traveller);
                traveller--;
            }
        }
    }
};

#endif