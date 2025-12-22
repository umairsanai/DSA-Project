#include<iostream>
#include"vector.h"
using namespace std;

template <typename T>
int linear_search(Array<T>&v , T target){
    int n = v.length();
    for(int i=0 ; i<n ; i++){
        if(v[i] == target) return i;
    }
    return -1;
}

template <typename T>
int binary_search(Array<T>&v , T target){
    int n = v.length();
    int l = 0 , h = n-1;
    while(l<=h){
        int m = l+(h-l)/2;
        if(v[m] == target) return m;
        else if(v[m] < target) l = m+1;
        else h = m-1;
    }
    return -1;
}