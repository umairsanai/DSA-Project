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