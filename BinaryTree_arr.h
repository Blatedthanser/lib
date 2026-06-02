#ifndef BINARYTREE_ARR_H
#define BINARYTREE_ARR_H

#include <iostream> // For std::cerr
#include <stdexcept> // For throw
#include <queue> // For levelOrder()
#include <vector> // For leverOrder()
using namespace std; // For vector and queue and print

template <class T, class NodeType> class BinaryTree_arr;

namespace tree_details {
    /**
     * Binary tree node with index, left, right and value(type T).
     * Empty left or right child is represented as -1.
     */
    template <class T>
    class BTNode {
    protected:
        int left;
        int right;
        T value;
        int inDegree = 0;
        bool existed = false;
        /**
         * Returns if this node is leaf node.
         */
        bool isLeaf() const {
            return left == -1 && right == -1;
        }
    public:
        BTNode(int l = -1, int r = -1, T v = T()) :
            left(l), right(r), value(v) {
        }
        /**
         * We don't have copy constructor currently.
         * If T is some weird object, then we're cooked.
         */

        template <class U, class V>
        friend class ::BinaryTree_arr;
    };
}


/**
 * Binary tree with element type T.
 * Requires only one root (node with 0 in-degree)
 * and continuous indexing starting from 0.
 */
template <class T, class NodeType = tree_details::BTNode<T>>
class BinaryTree_arr {
protected:

    int capacity;
    NodeType* tree;

    /**
     * Get the Node of a given index.
     * Able to mutate.
     * Should not be public.
     */
    NodeType& get(int index) const {
        if (index < 0 || index >= capacity) {
            std::cerr << "Index out of range [0, cap("
                << capacity << ")), accessing index: "
                << index << endl;
            throw std::out_of_range("");
        }
        return tree[index];
    }

    void resize(int cap) {
        NodeType* new_tree = new NodeType[cap];
        for (int i = 0; i < size; i++) {
            new_tree[i] = tree[i]; // No copy constructor
        }
        tree = new_tree;
    }

public:

    int size;
    BinaryTree_arr(int cap = 100) : size(0), capacity(cap) {
        tree = new NodeType[cap];
    }
    ~BinaryTree_arr() { // I really don't need polymorphyism
        delete[] tree;
    }
    /**
     * Insert a node into the tree.
     * Index must be non-negative and less than capacity.
     * Empty left or right child is represented as -1.
     */
    virtual void insert(int _index, int _left = -1, int _right = -1, T _value = T()) {
        if (_index < 0 || _index >= capacity) {
            std::cerr << "Insertion index out of range [0, cap("
                << capacity << ")), inserting at: "
                << _index << endl;
            throw std::out_of_range("");
        }
        if (size >= capacity * 0.75) {
            resize(2 * capacity);
        }
        // if (size >= capacity) {
        //     std::cerr << "No extra space. Insertion failed." << endl;
        //     throw std::length_error("");
        // }
        NodeType& current = tree[_index];
        current.left = _left;
        current.right = _right;
        current.value = _value;
        current.existed = true;
        if (_left != -1) {
            tree[_left].existed = true;
            tree[_left].inDegree++;
        }
        if (_right != -1) {
            tree[_right].existed = true;
            tree[_right].inDegree++;
        }
        size++;
    }

    /**
     * Get the index of root (node with 0 in-degree).
     * Return -1 if no root exists.
     */
    int getRoot() const {
        for (int i = 0; i < capacity; i++) {
            if (tree[i].existed && tree[i].inDegree == 0) return i;
        }
        std::cerr << "No root exists." << endl;
        return -1;
    }

    /**
     * Get the value of given index.
     */
    T getValue(int index) const {
        T copy = tree[index];
        return copy;
    }

    /**
     * Calculate the size of the subtree with given node as root.
     */
    int subtreeSize(int index) const {
        if (index == -1) return 0;
        NodeType& current = get(index);
        if (!current.existed) return 0;
        int subSize = 1;
        subSize += subtreeSize(current.left);
        subSize += subtreeSize(current.right);
        return subSize;
    }

    /**
     * Level Order.
     */
    vector<vector<int>> levelOrder() const {
        vector<vector<int>> result;
        int root = getRoot();
        if (root == -1) return result;

        queue<int> que;
        que.push(root);

        while (!que.empty()) {
            int currentLevelSize = que.size();
            vector<int> currentLevel;

            for (int i = 0; i < currentLevelSize; i++) {
                int node = que.front();
                que.pop();
                currentLevel.push_back(node);
                if (get(node).left != -1) {
                    que.push(get(node).left);
                }
                if (get(node).right != -1) {
                    que.push(get(node).right);
                }
            }
            result.push_back(currentLevel);
        }
        return result;
    }

    void print() const {
        vector<vector<int>> order = levelOrder();
        for (const auto& level : order) {
            cout << "[ ";
            for (int val : level) {
                cout << val << " ";
            }
            cout << "]" << endl;
        }
    }
};

#endif