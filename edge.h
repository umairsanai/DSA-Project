#pragma once
#include <iostream>
using namespace std;

class Edge {
    public:
        string src;
        string dest;
        int weight;
        Edge(string src = "", string dest = "",  int weight = 0) {
            this->src = src;
            this->dest = dest;
            this->weight = weight;
        }
};