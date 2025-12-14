#pragma once

#include <iostream>
using namespace std;
#include "vector.h" 

template <typename K, typename V>
class HashMap {
private:
    struct Entry {
        K key;
        V value;
        Entry() {}
        Entry(K k, V v) : key(k), value(v) {}
    };

    Array< Array<Entry> > buckets;
    int bucketCount;

    // Custom hash function
    int hashFunction(const int& key) {
        return key % bucketCount;
    }

    int hashFunction(const string& key) {
        long long hash = 0, p = 31, power = 1;
        for (char c : key) {
            hash = (hash + (c) * power) % bucketCount;  // just use ASCII
            power = (power * p) % bucketCount;
        }
        return (int)hash;
    }

    // Generic template fallback (not optimized)
    template <typename T>
    int hashFunction(const T& key) {
        return ((size_t)&key) % bucketCount; // fallback: use address
    }

public:
    HashMap(int bucketCount = 10) {
        this->bucketCount = bucketCount;
        buckets = Array< Array<Entry> >();
        for (int i = 0; i < bucketCount; i++) {
            Array<Entry> bucket;
            buckets.push_back(bucket);
        }
    }

    void insert(const K& key, const V& value) {
        int idx = hashFunction(key.id);
        Array<Entry>& bucket = buckets[idx];
        for (int i = 0; i < bucket.length(); i++) {
            if (bucket[i].key.id == key.id) {
                bucket[i].value = value;
                return;
            }
        }
        bucket.push_back(Entry(key, value));
    }

    K get(const K& key) {
        int idx = hashFunction(key.id);
        Array<Entry>& bucket = buckets[idx];
        for (int i = 0; i < bucket.length(); i++) {
            if (bucket[i].key.id == key.id) return bucket[i].key;
        }
        return K(); // default if not found
    }

    bool containsKey(const K& key) {
        int idx = hashFunction(key.id);
        Array<Entry>& bucket = buckets[idx];
        for (int i = 0; i < bucket.length(); i++) {
            if (bucket[i].key.id == key.id) return true;
        }
        return false;
    }

    void remove(const K& key) {
        int idx = hashFunction(key.id);
        Array<Entry>& bucket = buckets[idx];
        for (int i = 0; i < bucket.length(); i++) {
            if (bucket[i].key.id == key.id) {
                for (int j = i; j < bucket.length() - 1; j++) {
                    bucket[j] = bucket[j + 1];
                }
                bucket.pop_back();
                return;
            }
        }
    }

    void display() {
        for (int i = 0; i < bucketCount; i++) {
            cout << "Bucket " << i << ": ";
            Array<Entry>& bucket = buckets[i];
            for (int j = 0; j < bucket.length(); j++) {
                cout << "(" << bucket[j].key << "," << bucket[j].value << ") ";
            }
            cout << endl;
        }
    }
};
