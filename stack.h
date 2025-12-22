#pragma once
#include <iostream>
using namespace std;

template <class T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* top;
    int count;  // to keep track of number of elements

public:
    Stack() {
        top = nullptr;
        count = 0;
    }

    // Deep copy constructor
    Stack(const Stack& other) {
        top = nullptr;
        count = 0;
        
        if (other.top == nullptr) {
            return;
        }
    
        T* tempArray = new T[other.count];
        Node* current = other.top;
        int index = 0;
        
        // Copy all elements to array
        while (current != nullptr) {
            tempArray[index++] = current->data;
            current = current->next;
        }
        
        // Push elements in reverse order to maintain stack order
        for (int i = other.count - 1; i >= 0; i--) {
            push(tempArray[i]);
        }
        
        delete[] tempArray;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void push(T value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        count++;   // increment count
    }

    T pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return T();
        }
        Node* temp = top;
        T value = temp->data;
        top = top->next;
        delete temp;
        count--;   // decrement count
        return value;
    }

    T stackTop() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return T();
        }
        return top->data;
    }

    int length() {
        return count;   // return number of elements
    }

    void display() {
        Node* temp = top;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~Stack() {
        while (!isEmpty()) pop();
    }
};