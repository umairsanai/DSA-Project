
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

string getVehicleTypeName(VEHICLE_TYPE type) {
    switch(type) {
        case TRAIN: return "Train";
        case BUS: return "Bus";
        case VAN: return "Van";
        case CAR: return "Car";
        default: return "Unknown";
    }
}

void displayAllVehicles(HashMap<Vehicle,int>& vehicles) {
    cout << "\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                         ALL VEHICLES                            |\n";
    cout << "  +------------------------------------------------------------------+\n";
    
    Array<Vehicle> allVehicles = vehicles.getAllKeys();
    
    if (allVehicles.length() == 0) {
        cout << "\n    [!] No vehicles registered\n\n";
        return;
    }
    
    cout << "\n";
    for (int i = 0; i < allVehicles.length(); i++) {
        Vehicle v = allVehicles[i];
        cout << "    " << (i + 1) << ". ";
        cout << "ID: " << v.id;
        cout << " | Name: " << v.name;
        cout << "\n";
    }
    cout << "\n";
}

void insert_and_remove_vehicle(HashMap<Vehicle,int>&vehicles, Stack<string>&history, Stack<Vehicle>&vehicles_history){
    cout << "\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                      VEHICLE REGISTRY                           |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                                                                  |\n";
    cout << "  |   [1]  Add Vehicle                                               |\n";
    cout << "  |   [2]  Remove Vehicle                                            |\n";
    cout << "  |   [3]  Display All Vehicles                                      |\n";
    cout << "  |   [4]  Go Back                                                   |\n";
    cout << "  |                                                                  |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "\n  >> Enter operation: ";
    int operation;
    cin>>operation;
    cin.ignore();

    if(operation == 3){
        displayAllVehicles(vehicles);
        return;
    }
    
    if(operation == 4){
        return;
    }

    Vehicle v;
    cout<<"\nEnter vehicle id: ";
    cin>>v.id;
    cin.ignore();
    cout<<"Enter vehicle name: ";
    getline(cin , v.name);

    if(operation == 1){
        // Check if vehicle with this ID already exists
        if(vehicles.containsKey(v)){
            cout<<"\n  [X] Error: A vehicle with this ID already exists!\n";
            return;
        }
        // cout<<v.id<<" "<<v.name<<endl;
        vehicles.insert(v,1);
        cout<<"\n  [OK] Vehicle Added Successfully!\n";
        string s = "+3" + v.name + "-" + v.id + " added";
        add_history(history, s);
        vehicles_history.push(v);
    }
    else if(operation == 2){
        if(vehicles.containsKey(v)){
            vehicles.remove(v);
            cout<<"\n  [OK] Vehicle Removed Successfully!\n";
            string s = "-3" + v.name + "-" + v.id + " removed";
            add_history(history, s);
            vehicles_history.push(v);
        } else{
            cout<<"\n  [X] Vehicle Not Found!\n";
        }
    }
    else {
        cout << "\n  [!] Invalid operation!\n";
    }
}

Vehicle search_vehicle(HashMap<Vehicle,int>&vehicles, string &id){
    Vehicle v;
    v.id = id;
    return vehicles.get(v);
}
