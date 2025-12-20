#pragma once
#include <iostream>
#include "vehicle.h"
#include "history.h"
using namespace std;

class Ticket {
public:
    int seat, duration; // duration: in minutes
    string from, to, comfort, ticketID, vehicleID;
    Ticket(string from = "", string to = "", string comfort = "", string ticketID = "0000", string vehicleID = "1111", int seat = 1, int duration = 60) {
        this->from = from;
        this->to = to;
        this->comfort = comfort;
        this->ticketID = ticketID;
        this->vehicleID = vehicleID;
        this->seat = seat;
        this->duration = duration;
    }

    // Copy constructor
    Ticket(const Ticket& other) {
        this->from = other.from;
        this->to = other.to;
        this->comfort = other.comfort;
        this->ticketID = other.ticketID;
        this->vehicleID = other.vehicleID;
        this->seat = other.seat;
        this->duration = other.duration;
    }

    // Copy assignment operator
    Ticket& operator=(const Ticket& other) {
        if (this != &other) {
            this->from = other.from;
            this->to = other.to;
            this->comfort = other.comfort;
            this->ticketID = other.ticketID;
            this->vehicleID = other.vehicleID;
            this->seat = other.seat;
            this->duration = other.duration;
        }
        return *this;
    }
};

string showTicketOperationsMenu() {
    string option;
    cout << "\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                      TICKET OPERATIONS                          |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                                                                  |\n";
    cout << "  |   [1]  Add Ticket                                                |\n";
    cout << "  |   [2]  Delete Ticket                                             |\n";
    cout << "  |   [3]  View All Tickets                                          |\n";
    cout << "  |   [4]  Go Back                                                   |\n";
    cout << "  |                                                                  |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "\n  >> Enter your operation: ";
    cin >> option;
    return option;
}

void printTicket(Ticket& ticket) {
    cout << "\n";
    cout << "    +------------------------------------------+\n";
    cout << "    |             TICKET DETAILS               |\n";
    cout << "    +------------------------------------------+\n";
    cout << "    |  From:        " << ticket.from << string(27 - ticket.from.length(), ' ') << "|\n";
    cout << "    |  To:          " << ticket.to << string(27 - ticket.to.length(), ' ') << "|\n";
    cout << "    |  Seat No:     " << ticket.seat << string(27 - to_string(ticket.seat).length(), ' ') << "|\n";
    cout << "    |  Duration:    " << ticket.duration << " min" << string(23 - to_string(ticket.duration).length(), ' ') << "|\n";
    cout << "    |  Class:       " << ticket.comfort << string(27 - ticket.comfort.length(), ' ') << "|\n";
    cout << "    |  Ticket ID:   " << ticket.ticketID << string(27 - ticket.ticketID.length(), ' ') << "|\n";
    cout << "    |  Vehicle:     " << ticket.vehicleID << string(27 - ticket.vehicleID.length(), ' ') << "|\n";
    cout << "    +------------------------------------------+\n";
}


void addTicket(Graph& stations, unordered_map<string, Ticket>& tickets, HashMap<Vehicle,int>& vehicles, Stack<Ticket>&tickets_history, Stack<string>&history) {
    string from, to, class_choice, ticketID, vehicleID, seats, duration;

    cout << "From: "; cin >> from;
    cout << "To: "; cin >> to;

    if (!stations.hasNode(from) || !stations.hasNode(to)) {
        cout << "\n  [X] Error: Some of these stations don't exist!\n";
        return;
    }
    if (!stations.hasEdge(from, to)) {
        cout << "\n  [X] Error: There is no route from " << from << " to " << to << "\n";
        return;
    }
    do {
        cout << "Class: " << "\n"
             << "\t1. Economy\n"
             << "\t2. AC Standard\n"
             << "\t3. Business\n";
        cin >> class_choice;
    } while (!isValidOption(class_choice, 1, 3));

    cout << "Ticket ID: "; cin >> ticketID;
    cout << "Vehicle ID: "; cin >> vehicleID;

    if (tickets.count(ticketID)) {
        cout << "\n  [X] Error: A ticket with this ID already exists!\n";
        return;
    }

    if (!vehicles.containsKey(Vehicle("", vehicleID))) {
        cout << "\n  [X] Error: No such vehicle exists!\n";
        return;
    }

    do {
        cout << "Seats: "; cin >> seats;        
    } while (!isValidOption(seats, 1, 5));
    do {
        cout << "Duration: "; cin >> duration;    
    } while (!isValidOption(seats, 1, 2880)); // 2 days

    if (class_choice == "1") 
        class_choice = "Economy";
    if (class_choice == "2") 
        class_choice = "AC Standard";
    if (class_choice == "3") 
        class_choice = "Business";

    tickets[ticketID] = Ticket(from, to, class_choice, ticketID, vehicleID, stoi(seats), stoi(duration));
    tickets_history.push(tickets[ticketID]);
    add_history(history, "+5ticket from "+from+" to "+to+" added");
    cout << "\n  [OK] Ticket Added Successfully!\n";
    printTicket(tickets[ticketID]);
    return;
}

void deleteTicket(unordered_map<string, Ticket>& tickets, Stack<Ticket>&tickets_history, Stack<string>&history) {
    string ticketID;
    cout << "Ticket ID: "; cin >> ticketID;    
    if (!tickets.count(ticketID)) {
        cout << "\n  [X] Error: No ticket exists with this Ticket ID\n";
        return;
    }
    tickets_history.push(tickets[ticketID]);
    add_history(history, "-5ticket from "+tickets[ticketID].from+" to "+tickets[ticketID].to+" removed");
    tickets.erase(ticketID);
    cout <<"\n  [OK] Ticket Deleted Successfully!\n\n";
    return;
}

void showAllTickets(unordered_map<string, Ticket>& tickets) {
    cout << "\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                         ALL TICKETS                             |\n";
    cout << "  +------------------------------------------------------------------+\n";
    if (tickets.empty()) {
        cout << "\n    [!] No tickets available\n\n";
        return;
    }
    for (auto [ticketID, ticket] : tickets) {
        printTicket(ticket);
    }
}

void ticketOperations(Graph& stations, unordered_map<string, Ticket>& tickets, HashMap<Vehicle,int>& vehicles, Stack<Ticket>&tickets_history, Stack<string>&history) {
    int choice;
    do {
        string option = showTicketOperationsMenu();

        if (!isValidOption(option, 1, 4)) 
            continue;

        choice = stoi(option);

        switch (choice) {
            case 1:
                addTicket(stations, tickets, vehicles, tickets_history, history);
                break;
            case 2: 
                deleteTicket(tickets, tickets_history, history);
                break;
            case 3: 
                showAllTickets(tickets);
                break;
            default:
                break;
        }
    } while (choice != 4);
}