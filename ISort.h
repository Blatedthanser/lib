#ifndef ISORT_H
#define ISORT_H

template<class T>
class ISort {
protected:
    /**
     * Swap the i-th and j-th element in arr.
     */
    void swap(T* arr, int i, int j) {
        T temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
public:
    virtual ~ISort() = default;
    virtual void sort(T* arr, int size) = 0;
};

#endif

