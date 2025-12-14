#pragma once
#include <iostream>
using namespace std;

template <class T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* front;
    Node* rear;
    int count;

    // helper to copy from another queue
    void copyFrom(const Queue& other) {
        Node* temp = other.front;
        while (temp != nullptr) {
            enqueue(temp->data);
            temp = temp->next;
        }
    }

public:
    Queue() {
        front = rear = nullptr;
        count = 0;
    }

    // 🟢 COPY CONSTRUCTOR
    Queue(const Queue& other) {
        front = rear = nullptr;
        count = 0;
        copyFrom(other);
    }

    // 🟢 COPY ASSIGNMENT OPERATOR
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            while (!isEmpty())
                dequeue();
            copyFrom(other);
        }
        return *this;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void enqueue(T value) {
        Node* temp = new Node{value, nullptr};

        if (isEmpty()) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }
        count++;
    }

    T dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return T();
        }

        Node* temp = front;
        T value = temp->data;
        front = front->next;

        if (front == nullptr)
            rear = nullptr;

        delete temp;
        count--;
        return value;
    }

    T queueFront() const {
        if (isEmpty()) return T();
        return front->data;
    }

    int length() const {
        return count;
    }

    void display() const {
        Node* p = front;
        while (p != nullptr) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

    // 🟢 DESTRUCTOR
    ~Queue() {
        while (!isEmpty())
            dequeue();
    }
};
