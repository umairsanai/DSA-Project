#pragma once

#include<iostream>
#include"queue.h"
#include"stack.h"
using namespace std;

struct passenger{
    string name;
};

// Forward declaration of add_history to use it before including history.h
void add_history(Stack<string>&history, string s);

// Include history.h after passenger struct definition to avoid circular dependency
#include"history.h"

void passenger_ticketing(Queue<passenger>&passengers, Stack<string>&history, Stack<passenger>&passenger_history){
    passenger p;
    int operation;
    cout<<"\n1. Add passenger\n";
    cout<<"2. Remove passenger\n";
    cout<<"Enter operation: ";
    cin>>operation;
    cin.ignore();

    if(operation == 1){
        cout<<"\nEnter passenger name: ";
        getline(cin , p.name);
        passengers.enqueue(p);
        cout<<"Passenger has been added!"<<endl;
        string s = "+2" + p.name + " added";
        add_history(history, s);
        passenger_history.push(p);
    }
    else{
        if(!passengers.isEmpty()){
            p = passengers.queueFront();
            passengers.dequeue();
            cout<<"Passenger "<<p.name<<" has been removed!"<<endl;
            string s = "-2" + p.name + " removed";
            add_history(history, s);
            passenger_history.push(p);
        } else{
            cout<<"No passengers available!\n\n";
        }
    }
}