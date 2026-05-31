#ifndef SET_H
#define SET_H

#include "Sorter.h"

/**
 * A set is a non-duplicate container with element type T.
 */
template<class T>
class Set {
private:
    T* arr;
    int capacity;
    int size;
    void resize(int cap) {
        capacity = cap;
        T* new_arr = new T[cap];
        for (int i = 0; i < size; i++) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
    }
public:
    Set(int cap = 100) {
        arr = new T[cap];
        capacity = cap;
        size = 0;
    }
    ~Set() {
        delete[] arr;
    }
    bool has(T x) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == x) {
                return true;
            }
        }
        return false;
    }
    void add(T x) {
        if (this->has(x)) {
            return;
        }
        if (size >= capacity * 0.75) {
            resize(2 * capacity);
        }
        arr[size++] = x;
    }
    void sort() {
        Sorter<int> sorter = Sorter<int>();
        //sorter.setAlgorithm(SortConfig::Algorithm::Bubble);
        sorter.sort(arr, size);
    }
    int* toArray() {
        T* copy = new T[size];
        for (int i = 0; i < size; i++) {
            copy[i] = arr[i];
        }
        return copy;
    }

    /**
     * Return the index of element equal to x.
     * Return -1 if x is not in set.
     */
    int find(T x) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == x) {
                return i;
            }
        }
        return -1;
    }
};
#endif
