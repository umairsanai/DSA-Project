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

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printHeader() {
    cout << "\n";
    cout << "  +====================================================================+\n";
    cout << "  |                                                                    |\n";
    cout << "  |   ##### #######  #   #  #     #   ####                             |\n";
    cout << "  |     #      #     ##  #  ##   ##  #                                 |\n";
    cout << "  |     #      #     # # #  # # # #   ###                              |\n";
    cout << "  |     #      #     #  ##  #  #  #      #                             |\n";
    cout << "  |   #####    #     #   #  #     #  ####                              |\n";
    cout << "  |                                                                    |\n";
    cout << "  |        Integrated Transport Network Management System              |\n";
    cout << "  |                                                                    |\n";
    cout << "  +====================================================================+\n";
}

void show_menu(){
    cout << "\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                          MAIN MENU                               |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                                                                  |\n";
    cout << "  |   [1]  Network Management      (Graph Operations)                |\n";
    cout << "  |   [2]  Vehicle Registry        (Hash Table Operations)           |\n";
    cout << "  |   [3]  Edit Tickets            (Array Operations)                |\n";
    cout << "  |   [4]  Passenger Ticketing     (Queue Operations)                |\n";
    cout << "  |   [5]  Navigation History      (Stack Operations)                |\n";
    cout << "  |   [6]  Algorithm Benchmarking  (Sorting/Searching)               |\n";
    cout << "  |   [7]  Exit                                                      |\n";
    cout << "  |                                                                  |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "\n  >> Enter your choice: ";
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
    Stack<Ticket>tickets_history;
    // tickets["856E"] = Ticket("Hala", "Karachi", "Economy", "856E", "1234GL", 20, 300);
    // tickets["124E"] = Ticket("Karachi", "Hala", "AC Standard", "124E",  "1234GL", 30, 120);
    // tickets["65AC"] = Ticket("Karachi", "Nawabshah", "Business", "65AC",  "4532RB", 19, 1080); 

    printHeader();

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
                ticketOperations(stations, tickets, vehicles, tickets_history, history);
                break;

            case 4:
                passenger_ticketing(passengers, history, passenger_history, tickets_history, tickets);
                break;

            case 5:
                history_operations(history, passenger_history, vehicles_history, stations_history, routes_history, stations, passengers, vehicles, tickets_history, tickets);
                break;

            case 6:
                sortingOperations(stations);
                break;

            case 7:
                break;

            default:
                cout << "Invalid choice! Enter between (1-7)!" << "\n";
                break;
        }
    }
    cout << "\n";
    cout << "  +====================================================================+\n";
    cout << "  |                                                                    |\n";
    cout << "  |          Thank you for using ITNMS! Goodbye!                       |\n";
    cout << "  |                                                                    |\n";
    cout << "  +====================================================================+\n";
    cout << "\n";
    return 0;
}