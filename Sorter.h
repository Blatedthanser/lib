#ifndef SORTER_H
#define SORTER_H

#include "InsertionSort.h"
#include "BubbleSort.h"
#include "QuickSort.h"
#include "SelectionSort.h"

namespace SortConfig {
    enum class Algorithm {
        /**
         * Stable.
         * Best case: θ(N), worst case: θ(N²)
         * Space complexity: θ(1)
         * Note: Time is proportional to numbers of inversions.
         */
        Insertion,
        /**
         * Stable.
         * θ(N²).
         * Space complexity: θ(1).
         */
        Bubble,
        /**
         * Not stable.
         * On average θ(NlogN).
         * Space complexity: θ(logN).
         * Note: the fastest sorting algorithm.
         */
        Quick,
        /**
         * Not implemented.
         */
        Merge,
        /**
         * Stable.
         * Not implemented.
         */
        Heap,
        /**
         * Not stable.
         * θ(N²).
         * Space complexity: θ(1)
         */
        Selection
    };
}

template<class T>
class Sorter {
private:
    ISort<T>* iSort = new InsertionSort<T>();
public:
    void sort(T* arr, int size) {
        iSort->sort(arr, size);
    }
    /**
     * Set the sorting algorithm to algo(ENUM).
     * Use insertionSort if chosen algo is not implemented.
     */
    void setAlgorithm(SortConfig::Algorithm algo) {
        delete iSort;
        switch (algo) {
        case SortConfig::Algorithm::Insertion:
            iSort = new InsertionSort<T>();
            break;
        case SortConfig::Algorithm::Bubble:
            iSort = new BubbleSort<T>();
            break;
        case SortConfig::Algorithm::Quick:
            iSort = new QuickSort<T>();
            break;
        case SortConfig::Algorithm::Selection:
            iSort = new SelectionSort<T>();
            break;
        default:
            iSort = new InsertionSort<T>();
            break;
        }
    }
    ~Sorter() {
        delete iSort;
    }
};

#endif