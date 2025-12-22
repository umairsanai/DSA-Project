#pragma once
#include <bits/stdc++.h>
using namespace std;

bool startsWith(string source, string part) {
    if (part.size() > source.size()) return false;
    for (int i = 0; i < (int)part.size(); i++) {
        if (source[i] != part[i])
            return false;
    }
    return true;
}
bool endsWith(string source, string part) {
    if (part.size() > source.size()) return false;
    int i = source.size()-1, j = part.size()-1;
    while (i >= 0 && j >= 0) {
        if (source[i] != part[j])
            return false;
        i--;
        j--;
    }
    return true;
}

vector<string> split(string s, string delimiter) {
    vector<string> ans;
    int start = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (startsWith(s.substr(i), delimiter)) {
            ans.push_back(s.substr(start, i-start));
            start = i + delimiter.size();
            i = i + delimiter.size() - 1;
        }
    }
    ans.push_back(s.substr(start));
    return ans;
}

string trim(string s){
    int start = 0 , end = (int)s.length()-1;
    while(start <= end && s[start] == ' ') start++;
    while(end >= 0 && s[end] == ' ') end--;
    return s.substr(start, end-start+1);
}