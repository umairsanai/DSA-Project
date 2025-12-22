#include <iostream>
using namespace std;

template <class T>
class AVLNode {
public:
    T data;
    AVLNode *left;
    AVLNode *right;
    int height;

    AVLNode(T value) {
        data = value;
        left = right = nullptr;
        height = 1;
    }
};

template <class T>
class AVLTree {
private:
    AVLNode<T>* root;

    int height(AVLNode<T>* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode<T>* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    AVLNode<T>* rightRotate(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    AVLNode<T>* leftRotate(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    AVLNode<T>* insertNode(AVLNode<T>* node, T key) {
        if (!node) return new AVLNode<T>(key);

        if (key < node->data)
            node->left = insertNode(node->left, key);
        else if (key > node->data)
            node->right = insertNode(node->right, key);
        else
            return node; // no duplicates

        node->height = 1 + max(height(node->left), height(node->right));
        return balanceNode(node, key);
    }

    AVLNode<T>* minValueNode(AVLNode<T>* node) {
        AVLNode<T>* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    AVLNode<T>* deleteNode(AVLNode<T>* node, T key) {
        if (!node) return node;

        if (key < node->data)
            node->left = deleteNode(node->left, key);
        else if (key > node->data)
            node->right = deleteNode(node->right, key);
        else {
            // Node with 1 or 0 child
            if (!node->left || !node->right) {
                AVLNode<T>* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else
                    *node = *temp; // copy content
                delete temp;
            } else {
                // Node with 2 children
                AVLNode<T>* temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        if (!node) return node;

        node->height = 1 + max(height(node->left), height(node->right));
        return balanceNodeAfterDeletion(node);
    }

    AVLNode<T>* balanceNode(AVLNode<T>* node, T key) {
        int balance = getBalance(node);

        // Left Left
        if (balance > 1 && key < node->left->data)
            return rightRotate(node);

        // Right Right
        if (balance < -1 && key > node->right->data)
            return leftRotate(node);

        // Left Right
        if (balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left
        if (balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode<T>* balanceNodeAfterDeletion(AVLNode<T>* node) {
        int balance = getBalance(node);

        // Left heavy
        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);

        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right heavy
        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);

        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorderTraversal(AVLNode<T>* node) {
        if (!node) return;
        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }

    void preorderTraversal(AVLNode<T>* node) {
        if (!node) return;
        cout << node->data << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }

    void postorderTraversal(AVLNode<T>* node) {
        if (!node) return;
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        cout << node->data << " ";
    }

public:
    AVLTree() { root = nullptr; }

    void insert(T key) {
        root = insertNode(root, key);
    }

    void remove(T key) {
        root = deleteNode(root, key);
    }

    void inorder() {
        inorderTraversal(root);
        cout << endl;
    }

    void preorder() {
        preorderTraversal(root);
        cout << endl;
    }

    void postorder() {
        postorderTraversal(root);
        cout << endl;
    }
};