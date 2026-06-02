#ifndef HEAP_H
#define HEAP_H

template <class T>
class Heap {
private:
    T* arr;
    int capacity;
    int size;

    int getLeft() {

    }
public:
    Heap(int cap = 100): size(0), capacity(cap) {
        arr = new T[cap];
    }

    ~Heap() {
        delete[] arr;
    }

    void insert(T x) {
        size++;
    }

    void delete(int index) {
        size--;
    }

    void resize(int cap) {
        // Not implemented.
    }
};

#endif