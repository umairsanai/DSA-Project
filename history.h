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

void history_operations(Stack<string>&history, Stack<passenger>&passenger_history, Stack<Vehicle>&vehicles_history, Stack<string>&stations_history, Stack<Route_Info>&routes_history, Graph &stations, Queue<passenger>&passengers, HashMap<Vehicle,int>&vehicles, Stack<Ticket>&tickets_history, unordered_map<string,Ticket>&tickets){
    int operation;
    cout << "\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                     NAVIGATION HISTORY                          |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                                                                  |\n";
    cout << "  |   [1]  View History                                              |\n";
    cout << "  |   [2]  Undo Operation                                            |\n";
    cout << "  |                                                                  |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "\n  >> Enter your operation: ";
    cin>>operation;

    if(operation == 1) show_history(history);
    else{
        if(!history.isEmpty()){
            string top = history.stackTop();
            history.pop();
            if(top[0] == '+'){
                if(top[1] == '1'){
                    string top_station = stations_history.stackTop();
                    stations_history.pop();
                    stations.deleteNode(top_station);
                } else if(top[1] == '2'){
                    int n = passengers.length();
                    // cout<<"n: "<<n<<endl;
                    passenger temp[n];
                    int i = 0;
                    while(!passengers.isEmpty()){
                        temp[i++] = passengers.queueFront();
                        passengers.dequeue();
                    }
                    for(i=0 ; i<n-1 ; i++){
                        passengers.enqueue(temp[i]);
                    }
                    passenger_history.pop();
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
                    int n = passengers.length();
                    passenger temp[n];
                    int i = 0;
                    while(!passengers.isEmpty()){
                        temp[i++] = passengers.queueFront();
                        passengers.dequeue();
                    }
                    passengers.enqueue(top_pass);
                    for(i=0 ; i<n ; i++){
                        passengers.enqueue(temp[i]);
                    }
                    if(top_pass.hasTicket){
                        tickets[top_pass.ticket.ticketID] = top_pass.ticket;
                        tickets_history.pop();
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
    }
}