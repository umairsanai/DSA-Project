#pragma once

#include <iostream>
#include <string>
#include "queue.h"
#include "stack.h"
#include "ticket.h"
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct passenger {
    string name;
    Ticket ticket;
    string ticketID;   // ✅ store ONLY ticketID (not full Ticket)
    bool hasTicket;

    passenger(string n = "") {
        name = n;
        ticketID = "";
        hasTicket = false;
    }
};

// Forward declaration of add_history to use it before including history.h
void add_history(Stack<string>& history, string s);

// Include history.h after passenger struct definition to avoid circular dependency
#include "history.h"

// ✅ helper: display queue WITHOUT losing order
static void displayPassengerQueue(Queue<passenger>& q) {
    if (q.isEmpty()) {
        cout << "\n  [!] Queue is empty!\n";
        return;
    }

    Queue<passenger> temp;
    cout << "\n  Current Ticket Request Queue (FIFO):\n";
    cout << "  --------------------------------------------------\n";

    int pos = 1;
    while (!q.isEmpty()) {
        passenger p = q.queueFront();
        q.dequeue();

        cout << "  " << pos++ << ") " << p.name;
        if (p.hasTicket) cout << "  [has ticket: " << p.ticketID << "]";
        cout << "\n";

        temp.enqueue(p);
    }
    cout << "  --------------------------------------------------\n";

    // restore original queue
    while (!temp.isEmpty()) {
        q.enqueue(temp.queueFront());
        temp.dequeue();
    }
}

void passenger_ticketing(
    Queue<passenger>& passengers,                 // ✅ main passenger queue (FIFO)
    Stack<string>& history,
    Stack<passenger>& passenger_history,
    Stack<Ticket>& tickets_history,
    unordered_map<string, Ticket>& tickets,       // ticket pool (ticketID -> Ticket)
    unordered_map<string, unordered_set<int>>& occupiedSeats // ✅ vehicleID -> occupied seat set
) {
    int operation = 0;

    while (true) {
        cout << "\n";
        cout << "  +------------------------------------------------------------------+\n";
        cout << "  |                 PASSENGER TICKETING SYSTEM (FIFO)                |\n";
        cout << "  +------------------------------------------------------------------+\n";
        cout << "  |  [1]  Enter Passenger                                             |\n";
        cout << "  |  [2]  Display ticket request queue                                |\n";
        cout << "  |  [3]  Process next passenger (assign ticket)                      |\n";
        cout << "  |  [4]  Go Back                                                     |\n";
        cout << "  +------------------------------------------------------------------+\n";
        cout << "\n  >> Enter operation: ";
        cin >> operation;
        cin.ignore();

        if (operation == 4) break;

        // ------------------------------------------------------------
        // [1] Passenger enters queue
        // ------------------------------------------------------------
        if (operation == 1) {
            passenger p;
            cout << "\n  Enter passenger name: ";
            getline(cin, p.name);

            p.hasTicket = false;
            p.ticketID = "";

            // ✅ Main passengers queue (FIFO)
            passengers.enqueue(p);

            cout << "\n  [OK] Passenger added to queue!\n";
            add_history(history, "+2passenger " + p.name + " entered ticket queue");
            passenger_history.push(p);
        }

        // ------------------------------------------------------------
        // [2] Display passenger queue
        // ------------------------------------------------------------
        else if (operation == 2) {
            displayPassengerQueue(passengers);
        }

        // ------------------------------------------------------------
        // [3] Process next passenger (FIFO) and assign ticket by ID
        // ------------------------------------------------------------
        else if (operation == 3) {
            if (passengers.isEmpty()) {
                cout << "\n  [!] No passengers waiting in queue!\n";
                continue;
            }

            passenger p = passengers.queueFront();
            passengers.dequeue();

            cout << "\n  Serving (FIFO): " << p.name << "\n";

            if (tickets.empty()) {
                cout << "  [!] No tickets available to assign!\n";
                add_history(history, "-2no tickets available for " + p.name);
                passenger_history.push(p);
                continue;
            }

            // Show tickets so passenger can choose by ID
            cout << "\n  Available Tickets:\n";
            cout << "  --------------------------------------------------\n";
            for (auto& entry : tickets) {
                const Ticket& t = entry.second;
                cout << "  TicketID: " << entry.first
                     << " | " << t.from << " -> " << t.to
                     << " | Seat: " << t.seat
                     << " | Vehicle: " << t.vehicleID
                     << " | Class: " << t.comfort
                     << "\n";
            }
            cout << "  --------------------------------------------------\n";

            string chosenID;
            while (true) {
                cout << "\n  Enter Ticket ID to assign (or type 0 to skip): ";
                cin >> chosenID;

                if (chosenID == "0") {
                    p.hasTicket = false;
                    p.ticketID = "";
                    cout << "  [OK] Skipped ticket assignment.\n";
                    add_history(history, "-2" + p.name + " skipped ticket assignment");
                    passenger_history.push(p);
                    break;
                }

                auto it = tickets.find(chosenID);
                if (it == tickets.end()) {
                    cout << "  [!] Invalid Ticket ID. Try again.\n";
                    continue;
                }

                Ticket t = it->second; // snapshot (for history/undo)

                // ✅ Seat clash prevention
                if (occupiedSeats[t.vehicleID].count(t.seat)) {
                    cout << "  [!] Seat " << t.seat << " already occupied on vehicle "
                         << t.vehicleID << ". Choose another ticket.\n";
                    continue;
                }

                // ✅ Assign by storing ticketID and full ticket object in passenger
                p.ticketID = chosenID;
                p.ticket = t;  // Store full ticket for undo functionality
                p.hasTicket = true;

                // Mark seat as taken
                occupiedSeats[t.vehicleID].insert(t.seat);

                // Save ticket snapshot for undo/history
                tickets_history.push(t);

                // Remove ticket from pool so it can't be reused
                tickets.erase(it);

                cout << "  [OK] Ticket assigned to passenger!\n";
                add_history(history, "+2ticket " + chosenID + " assigned to " + p.name);

                passenger_history.push(p);
                break;
            }
        }

        else {
            cout << "\n  [!] Invalid option!\n";
        }
    }
}
