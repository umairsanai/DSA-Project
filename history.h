#pragma once

#include<iostream>
#include"stack.h"
#include"queue.h"
#include"vector.h"  // for Array class
#include"hashmap.h"
using namespace std;

// Forward declarations (will be resolved when vehicle.h/passenger.h/graph.h are included)
struct passenger;
struct Vehicle;
class Graph;
class Route;
class Ticket;

// Include full definitions - these files include history.h after struct/class definitions
// so #pragma once prevents circular dependency issues
#include"vehicle.h"
#include"passenger.h"
// Note: graph.h includes history.h at the end, so we don't include it here to avoid circular dependency

void show_history(Stack<string>history){
    string temp[history.length()];
    cout << "\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                      OPERATION HISTORY                          |\n";
    cout << "  +------------------------------------------------------------------+\n";
    int i=0;
    while(!history.isEmpty()){
        temp[i] = history.stackTop();
        history.pop();
        cout<<"    "<<i+1<<". "<<temp[i].substr(2)<<endl;
        i++;
    }
    if(i == 0) cout << "    (No history available)\n";
    cout << "\n";
}

void add_history(Stack<string>&history, string s){
    history.push(s);
}

// Include graph.h after add_history is defined so Graph and Route are available
// graph.h includes history.h at the end, but #pragma once prevents circular dependency
#include"graph.h"
#include"ticket.h"

void history_operations(Stack<string>&history, Stack<passenger>&passenger_history, Stack<Vehicle>&vehicles_history, Stack<string>&stations_history, Stack<Route_Info>&routes_history, Graph &stations, Queue<passenger>&passengers, HashMap<Vehicle,int>&vehicles, Stack<Ticket>&tickets_history, unordered_map<string,Ticket>&tickets, unordered_map<string, unordered_set<int>>& occupiedSeats){
    int operation;
    cout << "\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                     NAVIGATION HISTORY                           |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                                                                  |\n";
    cout << "  |   [1]  View History                                              |\n";
    cout << "  |   [2]  Undo Operation                                            |\n";
    cout << "  |                                                                  |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "\n  >> Enter your operation: ";
    cin>>operation;

    if(operation == 1) show_history(history);
    else if(operation == 2){
        if(!history.isEmpty()){
            string top = history.stackTop();
            history.pop();
            if(top[0] == '+'){
                if(top[1] == '1'){
                    string top_station = stations_history.stackTop();
                    stations_history.pop();
                    stations.deleteNode(top_station);
                } else if(top[1] == '2'){
                    passenger top_pass = passenger_history.stackTop();
                    passenger_history.pop();
                    // Undo \"+2\":
                    // - If passenger has ticket: they were removed from queue when ticket was assigned,
                    //   so add them back to the FRONT and restore ticket to hashmap.
                    // - If passenger has no ticket: they were added to queue, so remove them from queue.
                    if(top_pass.hasTicket){
                        // Add passenger back to FRONT of queue (without ticket)
                        passenger restored_pass = top_pass;
                        restored_pass.hasTicket = false;
                        restored_pass.ticketID = "";
                        restored_pass.ticket = Ticket();
                        
                        int n = passengers.length();
                        passenger temp[n];
                        int i = 0;
                        while(!passengers.isEmpty()){
                            temp[i++] = passengers.queueFront();
                            passengers.dequeue();
                        }
                        passengers.enqueue(restored_pass);
                        for(int j = 0; j < n; j++){
                            passengers.enqueue(temp[j]);
                        }
                        // Restore ticket to hashmap and free the seat
                        if(!tickets_history.isEmpty()){
                            Ticket temp_ticket = tickets_history.stackTop();
                            tickets_history.pop();
                            tickets[temp_ticket.ticketID] = temp_ticket;
                            // Free the seat
                            occupiedSeats[temp_ticket.vehicleID].erase(temp_ticket.seat);
                        }
                    } else{
                        // Remove this passenger from queue (they were just added)
                        int n = passengers.length();
                        passenger temp[n];
                        int i = 0;
                        while(!passengers.isEmpty()){
                            passenger p = passengers.queueFront();
                            passengers.dequeue();
                            if(p.name != top_pass.name){
                                temp[i++] = p;
                            }
                        }
                        for(int j = 0; j < i; j++){
                            passengers.enqueue(temp[j]);
                        }
                    }
                } else if(top[1] == '3'){
                    Vehicle top_veh = vehicles_history.stackTop();
                    vehicles_history.pop();
                    vehicles.remove(top_veh);
                } else if(top[1] == '4'){
                    Route_Info temp_route = routes_history.stackTop();
                    routes_history.pop();
                    stations.deleteEdge(temp_route.from, temp_route.to);
                } else if(top[1] == '5'){
                    Ticket temp_ticket = tickets_history.stackTop();
                    tickets_history.pop();
                    tickets.erase(temp_ticket.ticketID);
                }
            } else{
                if(top[1] == '1'){
                    string top_station = stations_history.stackTop();
                    stations_history.pop();
                    stations.insertNode(top_station);
                } else if(top[1] == '2'){
                    passenger top_pass = passenger_history.stackTop();
                    passenger_history.pop();
                    // Undo \"-2\" (passenger was removed from FRONT of queue):
                    // Always add passenger back to FRONT of queue.
                    int n = passengers.length();
                    passenger temp[n];
                    int i = 0;
                    while(!passengers.isEmpty()){
                        temp[i++] = passengers.queueFront();
                        passengers.dequeue();
                    }
                    passengers.enqueue(top_pass);
                    for(int j = 0; j < n; j++){
                        passengers.enqueue(temp[j]);
                    }
                    // If passenger had a ticket, restore it to hashmap as well,
                    // but re-queued passenger should not keep the ticket.
                    if(top_pass.hasTicket && !tickets_history.isEmpty()){
                        Ticket temp_ticket = tickets_history.stackTop();
                        tickets_history.pop();
                        tickets[temp_ticket.ticketID] = temp_ticket;
                        // Free the seat
                        occupiedSeats[temp_ticket.vehicleID].erase(temp_ticket.seat);
                        top_pass.hasTicket = false;
                        top_pass.ticketID.clear();
                        top_pass.ticket = Ticket();
                    }
                } else if(top[1] == '3'){
                    Vehicle top_veh = vehicles_history.stackTop();
                    vehicles_history.pop();
                    vehicles.insert(top_veh, 1);
                } else if(top[1] == '4'){
                    Route_Info temp_route = routes_history.stackTop();
                    routes_history.pop();
                    stations.insertEdge(temp_route.from, temp_route.to, temp_route.route);
                } else if(top[1] == '5'){
                    Ticket temp_ticket = tickets_history.stackTop();
                    tickets_history.pop();
                    tickets[temp_ticket.ticketID] = temp_ticket;
                }
            }
            cout<<"\n  [OK] Operation Undo Done\n\n";
        } else cout<<"\n  [!] No operations done yet!\n\n";
    } else {
        cout<<"\n  [!] Invalid Operation!\n\n";
    }
}