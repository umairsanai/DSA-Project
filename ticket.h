#pragma once
#include <iostream>
#include "vehicle.h"
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
};

string showTicketOperationsMenu() {
    string option;
    cout << "\n" 
         << "1. Add Ticket" << "\n"
         << "2. Delete Ticket" << "\n"
         << "3. View All Tickets" << "\n"
         << "4. Go Back" << "\n"
         << "Enter your operation: ";
    cin >> option;
    return option;
}

void printTicket(Ticket& ticket) {
    cout << "\tFrom: " << ticket.from << "\n"
         << "\tTo: " << ticket.to << "\n"
         << "\tSeat No: " << ticket.seat << "\n"
         << "\tDuration: " << ticket.duration << " (minutes)" << "\n"
         << "\tClass: " << ticket.comfort << "\n"
         << "\tTicket ID: " << ticket.ticketID << "\n"
         << "\tVehicle Number: " << ticket.vehicleID << "\n\n\n";
}


void addTicket(Graph& stations, unordered_map<string, Ticket>& tickets, HashMap<Vehicle,int>& vehicles) {
    string from, to, class_choice, ticketID, vehicleID, seats, duration;

    cout << "From: "; cin >> from;
    cout << "To: "; cin >> to;

    if (!stations.hasNode(from) || !stations.hasNode(to)) {
        cout << "Error: Some of these stations don't exist!";
        return;
    }
    if (!stations.hasEdge(from, to)) {
        cout << "Error: There is no route from " << from << " to " << to << "\n";
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
        cout << "Error: A ticket with this ID already exists!" << "\n";
        return;
    }

    if (!vehicles.containsKey(Vehicle("", vehicleID))) {
        cout << "Error: No such vehicle exists!" << "\n";
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
    cout << "\n ~~~~~ Ticket Added Successfully ~~~~~ \n";
    printTicket(tickets[ticketID]);
    cout << "\n";
    return;
}

void deleteTicket(unordered_map<string, Ticket>& tickets) {
    string ticketID;
    cout << "Ticket ID: "; cin >> ticketID;    
    if (!tickets.count(ticketID)) {
        cout << "Error: No ticket exists with this Ticket ID\n";
        return;
    }
    tickets.erase(ticketID);
    cout <<"~~~~~ Ticket Deleted Successfully ~~~~~\n";
    return;
}

void showAllTickets(unordered_map<string, Ticket>& tickets) {
    for (auto [ticketID, ticket] : tickets) {
        printTicket(ticket);
    }
}

void ticketOperations(Graph& stations, unordered_map<string, Ticket>& tickets, HashMap<Vehicle,int>& vehicles) {
    int choice;
    do {
        string option = showTicketOperationsMenu();

        if (!isValidOption(option, 1, 4)) 
            continue;

        choice = stoi(option);

        switch (choice) {
            case 1:
                addTicket(stations, tickets, vehicles);
                break;
            case 2: 
                deleteTicket(tickets);
                break;
            case 3: 
                showAllTickets(tickets);
                break;
            default:
                break;
        }
    } while (choice != 4);
}