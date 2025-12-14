#pragma once
#include<iostream>
using namespace std;

template <typename T>
class Array{
    private:
        int size;
        int capacity;
        T *arr;
    public:
        Array(int size=1){
            this->size = 0;
            this->capacity = size;
            arr = new T[this->capacity];
        }

        Array(const Array& other) {
            size = other.size;
            capacity = other.capacity;
            arr = new T[capacity];
            for (int i = 0; i < size; i++)
                arr[i] = other.arr[i];
        }

        Array& operator=(const Array& other) {
            if (this == &other) return *this;  // self-assignment check

            delete[] arr;  // free old memory

            size = other.size;
            capacity = other.capacity;
            arr = new T[capacity];
            for (int i = 0; i < size; i++)
                arr[i] = other.arr[i];

            return *this;
        }

        void push_back(T x){
            if(this->size < this->capacity){
                arr[size++] = x;
            } else{
                T *temp = new T[this->capacity*2];
                for(int i=0 ; i<this->size ; i++){
                    temp[i] = arr[i];
                }
                delete []arr;
                arr = temp;
                temp = nullptr;
                arr[size++] = x;
                this->capacity *= 2;
            }
        }

        void pop_back(){
            if(size > 0) size--;
        }

        T& front() {
            return arr[0];
        }

        T& operator[](int index){
            if(index>=0 && index<size){
                return arr[index];
            }
            throw out_of_range("Index out of range...");
        }

        int length() const { 
            return this->size; 
        }

        void reverse() {
            for (int i = 0; i < size/2; i++) {
                swap(arr[i], arr[size-i-1]);
            }
        }

        ~Array(){
            delete []arr;
        }
};