#ifndef AVLTREE_H
#define AVLTREE_H

#include "BinaryTree.h"
#include <cmath>
#include <algorithm>

template <class T> class AVLTree;

namespace tree_details {
    template <class T>
    class AVLNode : public BTNode<T> {
    private:
        int height = 0;
    public:
        using BTNode<T>::BTNode; // Use constructor with params
        template <class U>
        friend class ::AVLTree;
    };
}

/**
 * AVLTree derived from BinaryTree. Element type is T.
 * Inherit all requirements of BinaryTree.
 */
template <class T>
class AVLTree : public BinaryTree<T, tree_details::AVLNode<T>> {
private:
    using Node = tree_details::AVLNode<T>; // Alias

    void updateHeight() {
        calculateHeight(this->getRoot());
    }
    /** Helper function for recursion. */
    int calculateHeight(int index) {

        // We need to do two things: update .height and return it.
        Node& current = this->get(index);
        if (current.isLeaf()) {
            return current.height = 1; // Compact syntax
        }
        // We cannot reuse existed .height because it is out of date.
        int leftHeight = 0, rightHeight = 0;
        if (current.left != -1) leftHeight = calculateHeight(current.left);
        if (current.right != -1) rightHeight = calculateHeight(current.right);
        return current.height = max(leftHeight, rightHeight) + 1; // Compact syntax
    }

    /**
     * Check if one node is the root of a balanced tree.
     */
    bool isBalanced(int index) {
        if (index == -1) return true;

        Node& current = this->get(index);
        int leftHeight = current.left == -1 ?
             0 : this->get(current.left).height;
        int rightHeight = current.right == -1 ?
             0 : this->get(current.right).height;
        if (abs(leftHeight - rightHeight) <= 1) {
            return isBalanced(current.left) && isBalanced(current.right);
        }
        return false;
    }

public:
    AVLTree(int cap = 100) : BinaryTree<T, Node>(cap) {
        this->tree = new Node[cap];
    }
    void insert(int _index, int _left, int _right, T _value = T()) override {
        BinaryTree<T, Node>::insert(_index, _left, _right, _value);
        updateHeight();
    }

    /** 
     * Return the total number of balanced nodes in tree including leaf node.
     */
    int numBalanced() const {
        int num = 0;
        for (int i = 0; i < this->capacity; i++) {
            Node& current = this->get(i);
            if (!current.existed) continue;

            if (current.isLeaf()) {
                num++;
                continue;
            }

            int leftHeight = 0, rightHeight = 0;
            if (current.left != -1) leftHeight = this->get(current.left).height;
            if (current.right != -1) rightHeight = this->get(current.right).height;
            if (abs(leftHeight - rightHeight) <= 1) num++;
        }
        return num;
    }

    int biggestBalancedSubTree() {
        int maxSize = 0;
        for (int i = 0; i < this->capacity; i++) {
            if (!this->get(i).existed) continue;
            if (isBalanced(i)) {
                maxSize = max(maxSize, this->subtreeSize(i));
            }
        }
        return maxSize;
    }

};

#endif