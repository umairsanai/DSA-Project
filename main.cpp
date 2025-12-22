#include <iostream>
#include <unordered_set>
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
    Queue<passenger> passengers;
    HashMap<Vehicle,int> vehicles;
    Stack<string> history;
    Graph stations;
    Stack<passenger> passenger_history;
    Stack<Vehicle> vehicles_history;
    Stack<Route_Info> routes_history;
    Stack<string> stations_history;
    string choice_str;
    int choice = 0;

    unordered_map<string, Ticket> tickets;     // <id, Ticket>
    Queue<passenger> ticketQueue;              // FIFO ticket request queue
    unordered_map<string, unordered_set<int>> occupiedSeats; // vehicleID -> occupied seats
    Stack<Ticket> tickets_history;

    // =========================================================
    // HARDCODED SETUP (for smooth presentation/demo)
    // =========================================================

    // ---- Stations (nodes) ----
    stations.insertNode("Islamabad");
    stations.insertNode("Lahore");
    stations.insertNode("Peshawar");
    stations.insertNode("Multan");
    stations.insertNode("Faisalabad");
    stations.insertNode("Karachi");

    // ---- Routes (edges) ----
    // NOTE: Graph is directed in your code, so insert both directions if you want "two-way" travel
    stations.insertEdge("Islamabad", "Lahore", Route(1500, 240));
    stations.insertEdge("Lahore", "Islamabad", Route(1500, 240));

    stations.insertEdge("Islamabad", "Peshawar", Route(800, 180));
    stations.insertEdge("Peshawar", "Islamabad", Route(800, 180));

    stations.insertEdge("Lahore", "Faisalabad", Route(500, 120));
    stations.insertEdge("Faisalabad", "Lahore", Route(500, 120));

    stations.insertEdge("Faisalabad", "Multan", Route(900, 180));
    stations.insertEdge("Multan", "Faisalabad", Route(900, 180));

    stations.insertEdge("Lahore", "Multan", Route(1200, 210));
    stations.insertEdge("Multan", "Lahore", Route(1200, 210));

    stations.insertEdge("Karachi", "Lahore", Route(3500, 900));
    stations.insertEdge("Lahore", "Karachi", Route(3500, 900));

    // ---- Vehicles (HashMap<Vehicle,int>) ----
    // Using int=1 just as stored value placeholder
    vehicles.insert(Vehicle("Daewoo Bus", "V01", BUS), 1);
    vehicles.insert(Vehicle("Hiace Van",  "V02", VAN), 1);
    vehicles.insert(Vehicle("AC Coach",   "V03", TRAIN), 1);
    vehicles.insert(Vehicle("City Car",   "V04", CAR), 1);

    // ---- Tickets (available tickets pool) ----
    // Seats are within 1–5 (your ticketing constraint)
    tickets["T101"] = Ticket("Islamabad", "Lahore",    "Economy",     "T101", "V01", 1, 240);
    tickets["T102"] = Ticket("Islamabad", "Lahore",    "Business",    "T102", "V01", 2, 240);
    tickets["T103"] = Ticket("Lahore",    "Multan",    "AC Standard", "T103", "V02", 1, 210);
    tickets["T104"] = Ticket("Peshawar",  "Islamabad", "Economy",     "T104", "V03", 3, 180);
    tickets["T105"] = Ticket("Karachi",   "Lahore",    "Business",    "T105", "V03", 4, 900);

    // ---- Optional: Preload passenger ticket request queue for quick demo ----
    // These passengers are already waiting in FIFO order
    passenger p1("Ali");
    passenger p2("Ahmed");
    passenger p3("Sara");

    passengers.enqueue(p1); ticketQueue.enqueue(p1);
    passengers.enqueue(p2); ticketQueue.enqueue(p2);
    passengers.enqueue(p3); ticketQueue.enqueue(p3);

    // =========================================================

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
                passenger_ticketing(passengers, ticketQueue, history, passenger_history,
                                    tickets_history, tickets, occupiedSeats);
                break;

            case 5:
                history_operations(history, passenger_history, vehicles_history,
                                   stations_history, routes_history,
                                   stations, passengers, vehicles,
                                   tickets_history, tickets);
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
