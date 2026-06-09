#ifndef SORTER_H
#define SORTER_H

#include "InsertionSort.h"
#include "BubbleSort.h"
#include "QuickSort.h"
#include "SelectionSort.h"
#include "HeapSort.h"

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
         * Note: The most primitive sorting algorithm.
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
         * Stable.
         * Not implemented.
         */
        Merge,

        /**
         * Not stable.
         * Best case: θ(N), worst case: θ(NlogN)
         * Space complexity: θ(1)
         * Note: Bad cache performance.
         */
        Heap,

        /**
         * Not stable.
         * θ(N²)
         * Space complexity: θ(1)
         */
        Selection,

        // === === === θ(N) algorithms === === === //
        /**
         * Sleep sort: Items have to be non-negative numbers.
         *  The operating systems will slow down the execution.
         * 
         * Counting sort: Stable.
         * Requires finite numbers of kinds of items.
         *  Great when the number of kinds is smaller than the size of alphabet.
         *  (If the items are numbers, the size of alphabet is the max number.)
         * 
         * Radix sort: LSD is stable.
         * Items have to be numbers.
         *  Great when the numbers are larger than number of numbers.
         *  The underlying sorting algorithm has to be stable.
         * NOTICE: MSD needs partition&recursion
         * 
         */
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
        case SortConfig::Algorithm::Heap:
            iSort = new HeapSort<T>();
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