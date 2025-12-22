#include <iostream>
using namespace std;
#include "vector.h"

template<class T>
class Heap {
private:
    Array<T> v;  // max heap

    // heapify from index i downwards
    void heapify(int i) {
        int n = v.length();
        int largest = i;

        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && v[left] > v[largest]) largest = left;
        if (right < n && v[right] > v[largest]) largest = right;

        if (largest != i) {
            T temp = v[i];
            v[i] = v[largest];
            v[largest] = temp;
            heapify(largest);
        }
    }

public:
    // insert element
    void push(T x) {
        v.push_back(x);
        int i = v.length() - 1;
        // move up by comparing with parent
        while (i > 0 && v[i] > v[(i - 1) / 2]) {
            T temp = v[i];
            v[i] = v[(i - 1) / 2];
            v[(i - 1) / 2] = temp;
            i = (i - 1) / 2;
        }
    }

    // delete max (root)
    void pop() {
        int n = v.length();
        if (n == 0) return;
        T temp = v[0];
        v[0] = v[n - 1];
        v.pop_back();
        heapify(0);
    }

    // build heap from array
    void heapify(T a[], int size) {
        v = Array<T>(); // clear
        for (int i = 0; i < size; i++) v.push_back(a[i]);
        for (int i = v.length() / 2 - 1; i >= 0; i--) heapify(i);
    }

    void display() {
        for (int i = 0; i < v.length(); i++) cout << v[i] << " ";
        cout << endl;
    }
};