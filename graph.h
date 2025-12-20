#pragma once
#include <iostream>
#include "helper_functions.h"
#include "vector.h"
#include "edge.h"

// Forward declaration for add_history
template<class T>
class Stack;
void add_history(Stack<string>&history, string s);

enum SORT_BY {TIME, COST};

// Forward declaration for Graph (used later)
class Graph;

class Route {
public:
    int cost, time;
    Array<string> vehicles;
    Route(int cost = 0, int time = 0, Array<string> vehicles = {}) {
        this->cost = cost;
        this->time = time;
        this->vehicles = vehicles;
    }
    
    // Copy constructor
    Route(const Route& other) {
        cost = other.cost;
        time = other.time;
        vehicles = other.vehicles;
    }
    
    // Copy assignment operator
    Route& operator=(const Route& other) {
        if (this == &other) {
            return *this;  // Self-assignment check
        }
        cost = other.cost;
        time = other.time;
        vehicles = other.vehicles;
        return *this;
    }
};

class Route_Info{
public:
    Route route;
    string from;
    string to;
    
    // Default constructor
    Route_Info() : route(), from(""), to("") {}
    
    // Parameterized constructor
    Route_Info(string from, string to, Route route) : route(route), from(from), to(to) {}
    
    // Copy constructor
    Route_Info(const Route_Info& other) : route(other.route), from(other.from), to(other.to) {}
    
    // Copy assignment operator
    Route_Info& operator=(const Route_Info& other) {
        if (this == &other) {
            return *this;  // Self-assignment check
        }
        from = other.from;
        to = other.to;
        route = other.route;
        return *this;
    }
};

class Graph {
    private:
        int nodes;
        int edges;
    public:
        unordered_map<string, unordered_map<string, Route>> map;
        unordered_map<string,int> stations_record;
        Graph() {
            nodes = edges = 0;
        }
        void insertNode(string station) {
            stations_record[station] = 1;
            map[station] = {};
            nodes++;
        }
        void deleteNode(string station) {
            nodes--;
            stations_record[station] = 0;
        }
        void insertEdge(string source, string dest, Route route) {
            if (stations_record[source] == 1) {
                map[source].insert({dest, route});
            } else {
                return;
            }
            edges++;
        }
        void deleteEdge(string source, string dest) {
            if (stations_record[source] == 0) 
                return;
            map[source].erase(dest);
            edges--;
        }
        bool hasNode(string node) {
            return stations_record[node];
        }
        bool hasEdge(string from, string to) {
            return stations_record[from] && map[from].count(to);
        }
        unordered_map<string, int> getShortestPath(string src, SORT_BY option) {
            Array<Edge> edgeList = this->getEdgeList(option);
            return bellmanFord(nodes, edgeList, src);
        }
        void printRoundTrips() {
            cout << "\n";
            cout << "  +------------------------------------------------------------------+\n";
            cout << "  |                        ROUND TRIPS                              |\n";
            cout << "  +------------------------------------------------------------------+\n\n";

            Array<string> cycle;
            Array<int> cost, time;
            Array<Array<string>> roundTrips;
            unordered_set<string> vis, recStack;

            for (auto& node: map) {
                if (!vis.count(node.first)) {
                    dfsForRoundTrips(node.first, vis, recStack, cycle, roundTrips, cost, time);
                }
            }

            for (int i = 0; i < roundTrips.length(); i++) {
                roundTrips[i].push_back(roundTrips[i].front());
                int n = roundTrips[i].length();

                cout << "    " << i+1 << ". ";
                for (int j = 0; j < n; j++) {
                    cout << roundTrips[i][j];
                    if (j < n-1)
                        cout << " -> ";
                }

                cout << "\n       Cost: " << cost[i]
                     << "  Time: " << time[i] << "\n\n";
            }

            if (!roundTrips.length()) {
                cout << "    [!] There are no round trips\n";
            }
            cout << "\n";
        }
        void printAllStations() {
            cout << "\n";
            cout << "  +------------------------------------------------------------------+\n";
            cout << "  |                        ALL STATIONS                             |\n";
            cout << "  +------------------------------------------------------------------+\n\n";
            unordered_set<string> vis;
            for (auto& node : map) {
                if (!vis.count(node.first)) {
                    dfsForPrintStations(node.first, vis);
                }
            }
            cout << "\n";
        }
        void printAllRoutes() {
            cout << "\n";
            cout << "  +------------------------------------------------------------------+\n";
            cout << "  |                         ALL ROUTES                              |\n";
            cout << "  +------------------------------------------------------------------+\n\n";
            for (auto& source : this->map) {
                for (auto& dest : source.second) {
                    cout << "    " << source.first << " -> " << dest.first << "\t" 
                         << "Cost: " << dest.second.cost << "\t"
                         << "Time: " << dest.second.time << "\n";
                }
            }
            cout << "\n";
        }


        Array<Edge> getEdgeList(SORT_BY option) {
            Array<Edge> edgeList;
            for (auto& src : map) {
                for (auto& dst: src.second) {
                    if (option == COST)
                        edgeList.push_back({src.first, dst.first, dst.second.cost});
                    if (option == TIME)
                        edgeList.push_back({src.first, dst.first, dst.second.time});
                }                
            }
            return edgeList;
        }
private:
        void dfsForPrintStations(string curr, unordered_set<string>& vis) {
            if (!stations_record[curr] || vis.count(curr)) return;
            vis.insert(curr);
            cout << "    * " << curr << "\n";
            for (auto& neighbour : map[curr]) {
                dfsForPrintStations(neighbour.first, vis);
            }
        }
        void dfsForRoundTrips(string curr, unordered_set<string>& vis, 
                unordered_set<string>& recStack, Array<string>& cycle, 
                Array<Array<string>>& roundTrips, Array<int>& cost, 
                Array<int>& time) 
        {

            if (recStack.count(curr)) {
                int c, t;
                roundTrips.push_back(extractCycleAndWeight(cycle, curr, c, t));
                cost.push_back(c);
                time.push_back(t);
                return;
            }

            vis.insert(curr);
            cycle.push_back(curr);
            recStack.insert(curr);

            for (auto i : map[curr]) {
                dfsForRoundTrips(i.first, vis, recStack, cycle, roundTrips, cost, time);
            }

            recStack.erase(curr);
            cycle.pop_back();
        }
        Array<string> extractCycleAndWeight(Array<string>& path, string& startingPosition, int& cost, int& time) {
            Array<string> cycle;
            string end = path[path.length()-1];

            cost = map[end][startingPosition].cost;
            time = map[end][startingPosition].time;

            for (int i = path.length()-1; i >= 0; i--) {
                cycle.push_back(path[i]);
                if (path[i] == startingPosition) {
                    break;
                } else {
                    cost += map[path[i-1]][path[i]].cost;
                    time += map[path[i-1]][path[i]].time;
                }
            }

            cycle.reverse();
            return cycle;
        }
        unordered_map<string, int> bellmanFord(int V, Array<Edge>& edges, string src) {
    
            unordered_map<string, int> dist;
            
            for (int i = 0; i < edges.length(); i++) {

                if (!dist.count(edges[i].src)) 
                    dist[edges[i].src] = 1e9;

                if (!dist.count(edges[i].dest)) 
                    dist[edges[i].dest] = 1e9;

            }

            dist[src] = 0;
          
            for (int i = 0; i < V-1; i++) {                
                for (int j = 0; j < edges.length(); j++) {
                    string u = edges[j].src;
                    string v = edges[j].dest;
                    int wt = edges[j].weight;

                    if (dist[u] != 1e9 && dist[u] < dist[v] - wt) {
                        dist[v] = dist[u] + wt;
                    }
                }
            }
        
            return dist;
        }
};



// Forward declaration of add_history to use it before including history.h
template<class T>
class Stack;
void add_history(Stack<string>&history, string s);

// main.cpp functions for editing graph (adding/deleting/statistics):

string showNetworkManagementMenu() {
    string option;
    cout << "\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                    NETWORK MANAGEMENT                           |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                                                                  |\n";
    cout << "  |   [1]  Add Station                                               |\n";
    cout << "  |   [2]  Add Route                                                 |\n";
    cout << "  |   [3]  Delete Station                                            |\n";
    cout << "  |   [4]  Delete Route                                              |\n";
    cout << "  |   [5]  Find Best Route                                           |\n";
    cout << "  |   [6]  Show All Round Trips                                      |\n";
    cout << "  |   [7]  Show All Stations                                         |\n";
    cout << "  |   [8]  Go Back                                                   |\n";
    cout << "  |                                                                  |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "\n  >> Enter your operation: ";
    cin >> option;
    return option;
}

bool isValidOption(string inp, int start, int end) {
    for (int i = start; i <= end; i++) {
        if (to_string(i) == inp) {
            return true;
        }
    }
    return false;
}

void registerStation(Graph& stations, Stack<string>&history, Stack<string>&station_history) {
    string station;
    cout << "Station Name: "; cin >> station;

    if (stations.hasNode(station)) {
        cout << "\n  [X] Error: This station already exists!\n";
        return;
    }

    stations.insertNode(station);
    cout << "\n  [OK] Station added successfully!\n";
    add_history(history, "+1" + station + " added");      
    station_history.push(station); 
    return;
}
void deleteStation(Graph& stations, Stack<string>&history, Stack<string>&station_history) {
    string station;
    cout << "Station Name: "; cin >> station;

    if (!stations.hasNode(station)) {
        cout << "\n  [X] Error: This station doesn't exist!\n";
        return;
    }

    stations.deleteNode(station);
    cout << "\n  [OK] Station removed successfully!\n";
    add_history(history, "-1" + station + " removed");     
    station_history.push(station);       
    return;
}

void registerRoute(Graph& stations, Stack<string>&history, Stack<Route_Info>&routes_history) {
    string from, to, cost, time;
    int cost_int, time_int;
    string vehicles;
    vector<string> vehicles_vector;
    Array<string> vehicles_array;

    cout << "From: "; cin >> from;
    cout << "To: "; cin >> to;

    if (!stations.hasNode(from) || !stations.hasNode(to)) {
        cout << "\n  [X] Error: Some of these stations don't exist!\n";
        return;
    }

    cout << "Cost: "; cin >> cost;
    cout << "Time: "; cin >> time;

    if (!isValidOption(cost, 1, 10000) || !isValidOption(time, 1, 2880)) {
        cout << "\n  [X] Error: Invalid Cost or time!\n";
        return;
    }

    cost_int = stoi(cost);
    time_int = stoi(time);

    getline(cin, vehicles);
    vehicles_vector = split(vehicles, " ");

    for (string veh : vehicles_vector) {
        vehicles_array.push_back(trim(veh));
    }

    stations.insertEdge(from, to, Route(cost_int, time_int, vehicles_array));
    cout << "\n  [OK] Route added successfully!\n";
    add_history(history, "+4route from " + from + " to " + to + " added");
    routes_history.push(Route_Info(from, to, Route(cost_int, time_int, vehicles_array)));
    return;
}
void deleteRoute(Graph& stations, Stack<string>&history, Stack<Route_Info>&routes_history) {
    string from, to;

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

    // Get the route BEFORE deleting it (copy constructor will be used here)
    Route temp_route = stations.map[from][to];
    stations.deleteEdge(from, to);
    cout << "\n  [OK] Route removed successfully!\n";
    add_history(history, "-4route from " + from + " to " + to + " removed");
    routes_history.push(Route_Info(from, to, temp_route));
    return;
}

void findBestRoute(Graph& stations) {
    string from, to, option;

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
        cout << "\n  Sort by:\n";
        cout << "    [1] Cost\n";
        cout << "    [2] Time\n";
        cout << "  >> Choose: ";
        cin >> option;
    } while (!isValidOption(option, 1, 2));

    unordered_map<string, int> bestRoutes = stations.getShortestPath(from, option == "1" ? COST : TIME);
    
    cout << "\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                        BEST ROUTE                               |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "    " << from << " -> " << to << "\n";
    cout << "    " << (option == "1" ? "Total Cost: " : "Total Time: ") << bestRoutes[to] << "\n\n";
}
void graphOperations(Graph& stations, Stack<string>&history, Stack<Route_Info>&routes_history, Stack<string>&station_history) {
    
    int choice;
    do {
        string option = showNetworkManagementMenu();

        if (!isValidOption(option, 1, 8)) 
            continue;

        choice = stoi(option);

        switch (choice) {
            case 1:
                registerStation(stations, history, station_history);
                break;
            case 2: 
                registerRoute(stations, history, routes_history);
                break;
            case 3: 
                deleteStation(stations, history, station_history);
                break;
            case 4:
                deleteRoute(stations, history, routes_history);            
                break;
            case 5:
                findBestRoute(stations);
                break;
            case 6: 
                stations.printRoundTrips();
                break;
            case 7: 
                stations.printAllStations();
                break;
            default:
                break;
        }
    } while (choice != 8);
}

// Include history.h after Graph class and all function definitions to avoid circular dependency
#include"history.h"