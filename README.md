# Integrated Transport Network Management System (ITNMS)

A comprehensive C++ application demonstrating various Data Structures and Algorithms through a real-world transport management system. This project implements a complete transportation network management solution with station management, route planning, vehicle registry, ticket management, and passenger queuing.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Data Structures Implemented](#data-structures-implemented)
- [Algorithms Implemented](#algorithms-implemented)
- [Project Structure](#project-structure)
- [Compilation & Execution](#compilation--execution)
- [Usage Guide](#usage-guide)
- [Technical Details](#technical-details)

## 🎯 Overview

ITNMS is a console-based application that manages a transportation network system. It allows users to:
- Manage stations and routes in a network
- Register and manage vehicles
- Create and manage tickets
- Handle passenger queuing and ticketing
- Track operation history with undo functionality
- Benchmark various sorting algorithms

The project serves as a practical demonstration of fundamental data structures and algorithms in C++.

## ✨ Features

### 1. Network Management (Graph Operations)
- Add/Delete stations
- Add/Delete routes between stations
- Find best routes (by cost or time)
- Display all stations
- Display all routes
- Find round trips in the network

### 2. Vehicle Registry (Hash Table Operations)
- Add vehicles to the registry
- Remove vehicles from the registry
- Efficient lookup using hash table implementation

### 3. Ticket Management (Array Operations)
- Create new tickets with route information
- Delete existing tickets
- View all available tickets
- Ticket details include: origin, destination, seat number, duration, class, ticket ID, and vehicle ID

### 4. Passenger Ticketing (Queue Operations)
- Add passengers to the queue
- Process passengers in FIFO order
- Automatic ticket assignment to passengers
- Queue-based passenger management

### 5. Navigation History (Stack Operations)
- View complete operation history
- Undo recent operations
- Track all changes made to the system

### 6. Algorithm Benchmarking (Sorting/Searching)
- Sort routes by cost or time
- Implementations of 6 sorting algorithms:
  - Bubble Sort
  - Selection Sort
  - Insertion Sort
  - Merge Sort
  - Quick Sort (with Hoare partition and median-of-three)
  - Heap Sort

## 🏗️ Data Structures Implemented

| Data Structure | File | Purpose |
|---------------|------|---------|
| **Graph** | `graph.h` | Network representation (stations and routes) |
| **Hash Table** | `hashmap.h` | Vehicle registry with O(1) average lookup |
| **Queue** | `queue.h` | Passenger queuing (FIFO) |
| **Stack** | `stack.h` | Operation history and undo functionality |
| **Array/Vector** | `vector.h` | Dynamic array for route storage |
| **AVL Tree** | `avl_trees.h` | Self-balancing binary search tree |
| **Priority Queue** | `priority_queue.h` | Heap-based priority queue |

## 🔢 Algorithms Implemented

### Sorting Algorithms
- **Bubble Sort** - O(n²) time complexity
- **Selection Sort** - O(n²) time complexity
- **Insertion Sort** - O(n²) time complexity
- **Merge Sort** - O(n log n) time complexity
- **Quick Sort** - O(n log n) average, O(n²) worst case
- **Heap Sort** - O(n log n) time complexity

### Graph Algorithms
- **Bellman-Ford Algorithm** - Shortest path finding
- **DFS (Depth-First Search)** - Cycle detection and station traversal
- **Round Trip Detection** - Finding circular routes

## 📁 Project Structure

```
DSA-Project/
│
├── main.cpp                    # Main application entry point
│
├── Core Data Structures/
│   ├── graph.h                 # Graph implementation (428 lines)
│   ├── hashmap.h               # Hash table implementation (92 lines)
│   ├── queue.h                 # Queue implementation (89 lines)
│   ├── stack.h                 # Stack implementation (87 lines)
│   ├── vector.h                # Dynamic array implementation (71 lines)
│   ├── avl_trees.h             # AVL tree implementation (164 lines)
│   └── priority_queue.h        # Priority queue implementation (55 lines)
│
├── Application Logic/
│   ├── ticket.h                # Ticket management (169 lines)
│   ├── passenger.h             # Passenger operations (62 lines)
│   ├── vehicle.h               # Vehicle operations (68 lines)
│   ├── history.h                # History and undo operations (131 lines)
│   └── helper_functions.h       # Utility functions (41 lines)
│
├── Algorithms/
│   ├── sorting_functions.h     # Sorting algorithms (258 lines)
│   └── searching_functions.h   # Searching algorithms (23 lines)
│
├── Supporting Files/
│   └── edge.h                  # Edge structure for graph (14 lines)
│
└── output/
    └── main.exe                # Compiled executable

Total: 1,863 lines of code
```

## 🚀 Compilation & Execution

### Prerequisites
- C++ compiler with C++11 or later support (GCC, Clang, or MSVC)
- Windows/Linux/MacOS operating system

### Compilation

**Windows (PowerShell/Command Prompt):**
```bash
cd DSA-Project
g++ -o output/main.exe main.cpp
```

**Linux/MacOS:**
```bash
cd DSA-Project
g++ -o output/main main.cpp
```

### Execution

**Windows:**
```bash
.\output\main.exe
```

**Linux/MacOS:**
```bash
./output/main
```

## 📖 Usage Guide

### Main Menu Options

1. **Network Management** - Manage stations and routes
   - Add/Delete stations
   - Add/Delete routes with cost and time
   - Find best routes between stations
   - View all stations and routes
   - Discover round trips

2. **Vehicle Registry** - Manage vehicles
   - Add vehicles with ID and name
   - Remove vehicles from registry

3. **Edit Tickets** - Ticket operations
   - Create tickets for routes
   - Delete tickets
   - View all tickets

4. **Passenger Ticketing** - Queue management
   - Add passengers to queue
   - Process passengers (FIFO)
   - Automatic ticket assignment

5. **Navigation History** - Operation tracking
   - View complete operation history
   - Undo last operation

6. **Algorithm Benchmarking** - Sorting algorithms
   - View all routes
   - Sort routes by cost (cheapest first)
   - Sort routes by time (fastest first)
   - Choose from 6 different sorting algorithms

7. **Exit** - Close the application

### Example Workflow

1. **Set up the network:**
   - Go to Network Management
   - Add stations (e.g., "Karachi", "Lahore", "Islamabad")
   - Add routes between stations with cost and time

2. **Register vehicles:**
   - Go to Vehicle Registry
   - Add vehicles with unique IDs

3. **Create tickets:**
   - Go to Edit Tickets
   - Create tickets for available routes

4. **Process passengers:**
   - Go to Passenger Ticketing
   - Add passengers to queue
   - Remove passengers (they get tickets automatically)

5. **View history:**
   - Go to Navigation History
   - View all operations or undo last action

## 🔧 Technical Details

### Key Features

- **Template-based Implementation**: All data structures use C++ templates for type safety and reusability
- **Memory Management**: Proper use of copy constructors and assignment operators
- **Error Handling**: Input validation and error messages
- **History System**: Complete undo/redo functionality using stacks
- **Efficient Algorithms**: Optimized implementations of classic algorithms

### Design Patterns

- **Template Pattern**: Generic data structures
- **RAII**: Resource management through constructors/destructors
- **Encapsulation**: Private members with public interfaces

### Complexity Analysis

| Operation | Data Structure | Time Complexity |
|----------|---------------|----------------|
| Insert Station | Graph | O(1) |
| Find Route | Graph | O(1) |
| Shortest Path | Graph (Bellman-Ford) | O(V×E) |
| Vehicle Lookup | Hash Table | O(1) average |
| Enqueue/Dequeue | Queue | O(1) |
| Push/Pop | Stack | O(1) |
| Sort Routes | Various | O(n log n) to O(n²) |

## 📊 Statistics

- **Total Lines of Code**: 1,863
- **Number of Files**: 16
- **Data Structures**: 7
- **Sorting Algorithms**: 6
- **Graph Algorithms**: 3

## 🎓 Educational Value

This project demonstrates:
- Implementation of fundamental data structures from scratch
- Real-world application of algorithms
- Software engineering principles (modularity, encapsulation)
- C++ best practices (templates, memory management)
- Problem-solving using appropriate data structures

## 👨‍💻 Development

### Code Style
- Consistent naming conventions
- Clear function documentation
- Modular design with separate header files
- ASCII-based user interface for cross-platform compatibility

## 📝 Notes

- The application uses console-based I/O
- All data is stored in memory (no persistent storage)
- The history system allows undoing operations
- Input validation ensures data integrity

## 🔮 Future Enhancements

Potential improvements:
- File I/O for data persistence
- GUI implementation
- Database integration
- Multi-threading support
- Advanced graph algorithms (Dijkstra, A*)
- Performance metrics and benchmarking

## 📄 License

This project is created for educational purposes as part of a Data Structures and Algorithms course.

---

**Developed with ❤️ using C++**

*For questions or contributions, please refer to the project documentation or contact the development team.*

