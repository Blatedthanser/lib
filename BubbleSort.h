#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "ISort.h"

/**
 * Stable.
 * θ(N²).
 * Space complexity: θ(1).
 * Note: The most primitive sorting algorithm.
 */
template<class T>
class BubbleSort : public ISort<T> {
private:
    void bubbleSort(T* arr, int size) {
        for (int i = 1; i < size; i++) {
            int j = i;
            while (j > 0 && arr[j - 1] > arr[j]) {
                ISort<T>::swap(arr, j - 1, j);
                j--;
            }
        }
    }
    void bubbleSortForLoop(T* arr, int size) {
        for (int i = 0; i < size; i++) {
            for (int j = i; j > 0; j--) {
                if (arr[j - 1] > arr[j]) {
                    ISort<T>::swap(arr, j - 1, j);
                }
            }
        }
    }
public:
    void sort(T* arr, int size) override {
        bubbleSortForLoop(arr, size);
    }
};

#endif
