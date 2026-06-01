#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "ISort.h"

/**
 * Not stable.
 * On average θ(NlogN).
 * Space complexity: θ(logN).
 * Note: the fastest sorting algorithm.
 */
template <class T>
class QuickSort : public ISort<T> {
private:
    using ISort<T>::swap;

    /**
     * Not in place. 
     * Space is θ(N) on average.
     * Slower than mergeSort.
     */
    void naivePartition(T* arr, int size) {
        if (size <= 1) return;
        T pivot = arr[0];
        T* tmp_arr = new T[size];
        int front = 0, rear = size - 1;
        for (int i = 1; i < size; i++) {
            if (arr[i] < pivot) tmp_arr[front++] = arr[i];
            else if (arr[i] > pivot) tmp_arr[rear--] = arr[i];
        }
        int mid = front;
        for (int i = 0; i < size; i++) {
            if (!(arr[i] < pivot) && !(arr[i] > pivot)) {
                tmp_arr[mid++] = arr[i];
            }
        }
        for (int i = 0; i < size; i++) {
            arr[i] = tmp_arr[i];
        }
        delete[] tmp_arr;
        naivePartition(arr, front);
        naivePartition(arr + rear + 1, size - rear - 1);
    }

    /**
     * In place. 
     * Space is θ(logN).
     * Quicker than mergeSort.
     */
    void hoarePartition(T* arr, int size) {
        if (size <= 1) return;
        T pivot = arr[0];
        int L = -1, G = size; // L has to be -1 to prevent L going all the way down and exceeding size
        while (true) {
            do { L++; } while (arr[L] < pivot);
            do { G--; } while (arr[G] > pivot);
            // if multiple pivots appear continuously, while() {} is gonna fall into infinite loop
            if (L >= G) break;
            swap(arr, L, G);
        }
        hoarePartition(arr, G + 1);
        hoarePartition(arr + G + 1, size - G - 1);
    }
public:
    void sort(T* arr, int size) override {
        if (size <= 1) return;
        hoarePartition(arr, size);
    }
};

#endif