#ifndef BINARYTREE_LINK_H
#define BINARYTREE_LINK_H

#include <queue>
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class BinaryTree_link {
private:
    class Node {
    public:
        T value;
        Node* left;
        Node* right;
        Node(T v = T(), Node* l = nullptr, Node* r = nullptr) :
            value(v), left(l), right(r) {}
    };

    Node* root;

    void clear(Node* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    friend class BinaryTreeTester;
public:
    int size;

    BinaryTree_link() : size(0), root(nullptr) {}

    ~BinaryTree_link() {
        clear();
    }

    void clear() {
        clear(root);
        size = 0;
        root = nullptr;
    }

    void createTree(T emptyNotation) {
        queue<Node*> que;
        if (size != 0) {
            cerr << "Please clear tree before creation." << endl;
            return;
        }
        cout << "Please enter the root node: ";
        T v;
        cin >> v;
        // Hopefully you don't need my deletion
        root = new Node(v);
        size++;
        que.push(root);
        cout << "Represent empty child as " << emptyNotation << endl;
        while (!que.empty()) {
            Node* tmp = que.front();
            que.pop();
            cout << "Please enter left and right child of Node {"
                 << tmp->value << "} : ";
            T leftValue, rightValue;
            cin >> leftValue >> rightValue;
            if (leftValue != emptyNotation) {
                que.push(tmp->left = new Node(leftValue));
                size++;
            }
            if (rightValue != emptyNotation) {
                que.push(tmp->right = new Node(rightValue));
                size++;
            }
        }
        cout << "Creation completed!" << endl;
    }

    vector<Node*> preOrder(Node* node) const {
        vector<Node*> vec;
        vec.push_back(node);
        if (node->left != nullptr) {
            vector<Node*> leftVec = preOrder(node->left);
            vec.insert(vec.end(), leftVec.begin(), leftVec.end());
        }
        if (node->right != nullptr) {
            vector<Node*> rightVec = preOrder(node->right);
            vec.insert(vec.end(), rightVec.begin(), rightVec.end());
        }
        return vec;
    }

    vector<Node*> midOrder(Node* node) const {
        vector<Node*> vec;
        if (node->left != nullptr) {
            vector<Node*> leftVec = midOrder(node->left);
            vec.insert(vec.end(), leftVec.begin(), leftVec.end());
        }
        vec.push_back(node);
        if (node->right != nullptr) {
            vector<Node*> rightVec = midOrder(node->right);
            vec.insert(vec.end(), rightVec.begin(), rightVec.end());
        }
        return vec;
    }

    vector<Node*> postOrder(Node* node) const {
        vector<Node*> vec;
        if (node->left != nullptr) {
            vector<Node*> leftVec = postOrder(node->left);
            vec.insert(vec.end(), leftVec.begin(), leftVec.end());
        }
        if (node->right != nullptr) {
            vector<Node*> rightVec = postOrder(node->right);
            vec.insert(vec.end(), rightVec.begin(), rightVec.end());
        }
        vec.push_back(node);
        return vec;
    }
 
};

#endif