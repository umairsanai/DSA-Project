
#pragma once

#include<iostream>
using namespace std;

template<class K, class V>
class HashMap;

template<class T>
class Stack;

enum VEHICLE_TYPE {
    TRAIN = 100, BUS = 50, VAN = 10, CAR = 4
};

struct Vehicle {
    string name;
    string id;
    VEHICLE_TYPE type;
    Vehicle(string name = "", string id = "", VEHICLE_TYPE type = CAR) {
        this->name = name;
        this->id = id;
        this->type = type;
    }
};

// Forward declaration of add_history to use it before including history.h
void add_history(Stack<string>&history, string s);

// Include history.h after Vehicle struct definition to avoid circular dependency
#include"history.h"

void insert_and_remove_vehicle(HashMap<Vehicle,int>&vehicles, Stack<string>&history, Stack<Vehicle>&vehicles_history){
    cout << "\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                      VEHICLE REGISTRY                           |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                                                                  |\n";
    cout << "  |   [1]  Add Vehicle                                               |\n";
    cout << "  |   [2]  Remove Vehicle                                            |\n";
    cout << "  |                                                                  |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "\n  >> Enter operation: ";
    int operation;
    cin>>operation;
    cin.ignore();

    Vehicle v;
    cout<<"\nEnter vehicle id: ";
    cin>>v.id;
    cin.ignore();
    cout<<"Enter vehicle name: ";
    getline(cin , v.name);

    if(operation == 1){
        // cout<<v.id<<" "<<v.name<<endl;
        vehicles.insert(v,1);
        cout<<"\n  [OK] Vehicle Added Successfully!\n";
        string s = "+3" + v.name + "-" + v.id + " added";
        add_history(history, s);
    }
    else{
        if(vehicles.containsKey(v)){
            vehicles.remove(v);
            cout<<"\n  [OK] Vehicle Removed Successfully!\n";
            string s = "-3" + v.name + "-" + v.id + " removed";
            add_history(history, s);
        } else{
            cout<<"\n  [X] Vehicle Not Found!\n";
        }
    }

    vehicles_history.push(v);
}

Vehicle search_vehicle(HashMap<Vehicle,int>&vehicles, string &id){
    Vehicle v;
    v.id = id;
    return vehicles.get(v);
}
