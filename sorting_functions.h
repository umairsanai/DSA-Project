#pragma once
#include<iostream>
#include"vector.h"
#include "edge.h"
#include "graph.h"
using namespace std;

enum SORT {BUBBLE, SELECTION, INSERTION, MERGE, QUICK, HEAP};

Array<Edge> selectionSort(Graph& g, SORT_BY option);
Array<Edge> insertionSort(Graph& g, SORT_BY option);
Array<Edge> bubbleSort(Graph& g, SORT_BY option);
Array<Edge> mergeSort(Graph& g, SORT_BY option);
Array<Edge> quickSort(Graph& g, SORT_BY option);
Array<Edge> heapSort(Graph& g, SORT_BY option);

void heapify(Array<Edge>& edgeList, int n, int i);
void merge(Array<Edge>& v, int left, int mid, int right);
void mergeSortHelper(Array<Edge>& v, int left, int right);
void quickSortHelper(Array<Edge>& v, int low, int high);
int medianOfThree(Array<Edge>& v, int low, int high);
int hoarePartition(Array<Edge>& v, int low, int high);


/* ================= HELPER ================= */

template <typename T>
void mySwap(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}

/* ================= BUBBLE SORT ================= */

Array<Edge> bubbleSort(Graph& g, SORT_BY option) {
    Array<Edge> edgeList = g.getEdgeList(option);
    int n = edgeList.length();

    for(int i = 0; i < n-1; i++){
        bool swapped = false;
        for(int j = 0;j < n-1-i; j++){
            if (edgeList[j].weight > edgeList[j+1].weight){
                mySwap(edgeList[j], edgeList[j+1]);
                swapped = true;
            }
        }
        if(!swapped) break;
    }
    return edgeList;
} 


/* ================= INSERTION SORT ================= */

Array<Edge> insertionSort(Graph& g, SORT_BY option) {
    Array<Edge> edgeList = g.getEdgeList(option);
    int n = edgeList.length();

    for(int i = 1; i < n; i++){
        Edge x = edgeList[i];
        int j = i-1;
        while(j >= 0 && edgeList[j].weight > x.weight){
            edgeList[j+1] = edgeList[j];
            j--;
        }
        edgeList[j+1] = x;
    }
    return edgeList;
}

/* ================= SELECTION SORT ================= */

Array<Edge> selectionSort(Graph& g, SORT_BY option) {
    Array<Edge> edgeList = g.getEdgeList(option);
    int n = edgeList.length();

    for(int i = 0; i < n-1; i++){
        int k = i;
        for(int j = i+1; j < n; j++){
            if(edgeList[j].weight < edgeList[k].weight)
                k = j;
        }
        mySwap(edgeList[i], edgeList[k]);
    }
    return edgeList;
}

/* ================= QUICK SORT (Median + Hoare) ================= */

Array<Edge> quickSort(Graph& g, SORT_BY option) {
    Array<Edge> edgeList = g.getEdgeList(option);
    quickSortHelper(edgeList, 0, edgeList.length()-1);
    return edgeList;
}

void quickSortHelper(Array<Edge>& v, int low, int high) {
    if(low < high){
        int partitionIndex = hoarePartition(v, low, high);
        quickSortHelper(v, low, partitionIndex);
        quickSortHelper(v, partitionIndex+1, high);
    }
}

int hoarePartition(Array<Edge>& v, int low, int high) {
    int m = medianOfThree(v, low, high);
    Edge pivot = v[m];

    int i = low - 1;
    int j = high + 1;

    while(true){

        do { i++; } while(v[i].weight < pivot.weight);
        do { j--; } while(v[j].weight > pivot.weight);

        if(i >= j) return j;

        mySwap(v[i], v[j]);
    }
}

int medianOfThree(Array<Edge>& v, int low, int high) {
    int mid = low + (high - low)/2;

    if(v[low].weight > v[mid].weight) mySwap(v[low], v[mid]);
    if(v[low].weight > v[high].weight) mySwap(v[low], v[high]);
    if(v[mid].weight > v[high].weight) mySwap(v[mid], v[high]);

    return mid;
}


/* ================= MERGE SORT ================= */

Array<Edge> mergeSort(Graph& g, SORT_BY option) {
    Array<Edge> edgeList = g.getEdgeList(option);
    mergeSortHelper(edgeList, 0, edgeList.length()-1);
    return edgeList;
}

void mergeSortHelper(Array<Edge>& v, int left, int right) {
    if(left < right){
        int mid = left + (right - left)/2;
        mergeSortHelper(v, left, mid);
        mergeSortHelper(v, mid+1, right);
        merge(v, left, mid, right);
    }
}

void merge(Array<Edge>& v, int left, int mid, int right) {
    int leftSize = mid - left + 1, rightSize = right - mid;

    Array<Edge> Left(leftSize), Right(rightSize);

    for(int i=0;i< leftSize;i++) Left[i] = v[left+i];
    for(int j=0;j< rightSize;j++) Right[j] = v[mid+j+1];

    int i = 0, j = 0, k = left;

    while(i < leftSize && j < rightSize){
        if(Left[i].weight <= Right[j].weight) v[k++] = Left[i++];
        else v[k++] = Right[j++];
    }

    while(i < leftSize) v[k++] = Left[i++];
    while(j < rightSize) v[k++] = Right[j++];

}


/* ================= HEAP SORT ================= */

Array<Edge> heapSort(Graph& g, SORT_BY option) {
    Array<Edge> edgeList = g.getEdgeList(option);
    int n = edgeList.length();

    for(int i= n/2-1; i >= 0; i--)
        heapify(edgeList, n, i);

    for(int i = n-1; i > 0; i--){
        mySwap(edgeList[0], edgeList[i]);
        heapify(edgeList, i, 0);
    }
    return edgeList;
}

void heapify(Array<Edge>& edgeList, int n, int i) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < n && edgeList[left].weight > edgeList[smallest].weight)
        smallest = left;

    if(right < n && edgeList[right].weight > edgeList[smallest].weight)
        smallest = right;

    if(smallest != i){
        mySwap(edgeList[i], edgeList[smallest]);
        heapify(edgeList, n, smallest);
    }
}



string showSortingOperationsMenu() {
    string option;
    cout << "\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                    ALGORITHM BENCHMARKING                       |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |                                                                  |\n";
    cout << "  |   [1]  Show All Routes                                           |\n";
    cout << "  |   [2]  Find Cheapest Routes                                      |\n";
    cout << "  |   [3]  Find Fastest Routes                                       |\n";
    cout << "  |   [4]  Back                                                      |\n";
    cout << "  |                                                                  |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "\n  >> Enter your choice: ";
    cin >> option;
    return option;
}

SORT getSort() {
    string option;

    do {
        cout << "\n";
        cout << "  +------------------------------------------------------------------+\n";
        cout << "  |                   SELECT SORTING ALGORITHM                      |\n";
        cout << "  +------------------------------------------------------------------+\n";
        cout << "  |                                                                  |\n";
        cout << "  |   [1]  Bubble Sort                                               |\n";
        cout << "  |   [2]  Selection Sort                                            |\n";
        cout << "  |   [3]  Insertion Sort                                            |\n";
        cout << "  |   [4]  Merge Sort                                                |\n";
        cout << "  |   [5]  Quick Sort                                                |\n";
        cout << "  |   [6]  Heap Sort                                                 |\n";
        cout << "  |                                                                  |\n";
        cout << "  +------------------------------------------------------------------+\n";
        cout << "\n  >> Select algorithm: ";
        cin >> option;
    } while (!isValidOption(option, 1, 6));

    if (option == "1")
        return BUBBLE;
    if (option == "2")
        return SELECTION;
    if (option == "3")
        return INSERTION;
    if (option == "4")
        return MERGE;
    if (option == "5")
        return QUICK;
    return HEAP;
}

void printEdgeList(Array<Edge>& edgeList, SORT_BY option) {
    for (int i = 0; i < edgeList.length(); i++) {
        cout << "    " << edgeList[i].src << " -> " << edgeList[i].dest << "\t" 
             << (option == COST ? "Cost: " : "Time: ") << edgeList[i].weight << "\n";
    }
}

void sortRoutes(Graph& stations, SORT_BY option) {
    SORT sort = getSort();
    Array<Edge> edgeList;
    
    if (sort == BUBBLE)
       edgeList = bubbleSort(stations, option);
    if (sort == SELECTION)
       edgeList = selectionSort(stations, option);
    if (sort == INSERTION)
       edgeList = insertionSort(stations, option);
    if (sort == MERGE)
       edgeList = mergeSort(stations, option);
    if (sort == QUICK)
       edgeList = quickSort(stations, option);
    if (sort == HEAP)
       edgeList = heapSort(stations, option);
    
    if (!edgeList.length()) {
        cout << "\n  [!] No Routes Found\n";
        return;
    }

    cout << "\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  |           " << (option == COST ? "CHEAPEST" : "FASTEST ") << " ROUTES (Sorted)                          |\n";
    cout << "  +------------------------------------------------------------------+\n\n";
    printEdgeList(edgeList, option);    
}


void sortingOperations(Graph& stations) {
    int choice;
    do {
        string option = showSortingOperationsMenu();

        if (!isValidOption(option, 1, 4)) 
            continue;

        choice = stoi(option);

        switch (choice) {
            case 1:
                stations.printAllRoutes();
                break;
            case 2: 
                sortRoutes(stations, COST);
                break;
            case 3: 
                sortRoutes(stations, TIME);                
                break;
            default:
                break;
        }
    } while (choice != 4);
}