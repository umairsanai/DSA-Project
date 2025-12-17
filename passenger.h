#pragma once

#include<iostream>
#include"queue.h"
#include"stack.h"
#include"ticket.h"
using namespace std;

struct passenger{
    string name;
    Ticket ticket;
    bool hasTicket;
};

// Forward declaration of add_history to use it before including history.h
void add_history(Stack<string>&history, string s);

// Include history.h after passenger struct definition to avoid circular dependency
#include"history.h"

void passenger_ticketing(Queue<passenger>&passengers, Stack<string>&history, Stack<passenger>&passenger_history, Stack<Ticket>&tickets_history, unordered_map<string,Ticket>&tickets){
    passenger p;
    int operation;
    cout << "\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                     PASSENGER TICKETING                         |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                                                                  |\n";
    cout << "  |   [1]  Add Passenger                                             |\n";
    cout << "  |   [2]  Remove Passenger                                          |\n";
    cout << "  |                                                                  |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "\n  >> Enter operation: ";
    cin>>operation;
    cin.ignore();

    if(operation == 1){
        cout<<"\nEnter passenger name: ";
        getline(cin , p.name);
        p.hasTicket = false;
        passengers.enqueue(p);
        cout<<"\n  [OK] Passenger has been added!"<<endl;
        string s = "+2" + p.name + " added";
        add_history(history, s);
        passenger_history.push(p);
    }
    else{
        if(!passengers.isEmpty()){
            p = passengers.queueFront();
            passengers.dequeue();
            cout<<"\n  [OK] Passenger "<<p.name<<" has been removed!"<<endl;
            string s = "-2" + p.name + " removed";

            if(tickets.size()) cout<<"  [+] Passenger has been assigned ticket!"<<endl;
            else cout<<"  [!] No ticket to be assigned!"<<endl;

            for(auto &[ticket_id , ticket] : tickets){
                p.ticket = ticket;
                tickets_history.push(ticket);
                p.hasTicket = true;
                tickets.erase(ticket_id);
                break;
            }

            add_history(history, s);
            passenger_history.push(p);
        } else{
            cout<<"\n  [!] No passengers available!\n\n";
        }
    }
}