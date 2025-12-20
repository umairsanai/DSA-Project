#include <iostream>
#include "queue.h"
#include "avl_trees.h"
#include "hashmap.h"
#include "priority_queue.h"
#include "stack.h"
#include "sorting_functions.h"
#include "vector.h"
#include "passenger.h"
#include "vehicle.h"
#include "ticket.h"
#include "helper_functions.h"
#include "graph.h"

using namespace std;

void show_menu(){
    cout << "\n=== ITNMS Main Menu ===" << endl;
    cout << "1. Network Management (Graph Operations)" << endl;
    cout << "2. Vehicle Registry (Hash Table Operations)" << endl;
    cout << "3. Edit Tickets (Array Operations)" << endl;
    cout << "4. Passenger Ticketing (Queue Operations)" << endl;
    cout << "5. Navigation History (Stack Operations)" << endl;
    cout << "6. Algorithm Benchmarking (Sorting/Searching)" << endl;
    cout << "7. Exit" << endl;
    cout<<"Enter your choice: ";
}

int main(){
    Queue<passenger>passengers;
    HashMap<Vehicle,int>vehicles;
    Stack<string>history;
    Graph stations;
    Stack<passenger>passenger_history;
    Stack<Vehicle>vehicles_history;
    Stack<Route_Info>routes_history;
    Stack<string>stations_history;
    string choice_str;
    int choice = 0;
    unordered_map<string, Ticket> tickets;     // <id, Ticket>
    tickets["856E"] = Ticket("Hala", "Karachi", "Economy", "856E", "1234GL", 20, 300);
    tickets["124E"] = Ticket("Karachi", "Hala", "AC Standard", "124E",  "1234GL", 30, 120);
    tickets["65AC"] = Ticket("Karachi", "Nawabshah", "Business", "65AC",  "4532RB", 19, 1080); 

    while(choice != 7){
        show_menu();
        cin >> choice_str;
        cin.ignore();

        if (!isValidOption(choice_str, 1, 7))
            continue;

        choice = stoi(choice_str);

        switch(choice){
            case 1:
                graphOperations(stations, history, routes_history, stations_history);
                break;      

            case 2:
                insert_and_remove_vehicle(vehicles, history, vehicles_history);
                break;

            case 3:
                ticketOperations(stations, tickets, vehicles);
                break;

            case 4:
                passenger_ticketing(passengers, history, passenger_history);
                break;

            case 5:
                history_operations(history, passenger_history, vehicles_history, stations_history, routes_history, stations, passengers, vehicles);
                break;

            case 6:
                sortingOperations(stations);
                break;

            default:
                cout << "Invalid choice! Enter between (1-7)!" << "\n";
                break;
        }
    }
    cout<<"Exiting Application.....\n\n";
    return 0;
}