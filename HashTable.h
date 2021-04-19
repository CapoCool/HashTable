/*
Dillan Poorman
CSE310
09/30/2020

Header file for HashTable

*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include "LinkedList.h"

using namespace std;



// declarations for the hash table
class HashTable {
public:

    int size;
    int maxCost;
    int listSize;
    LinkedList* table;

    HashTable();
    int hashFunc(string k);
    void createTable(int n);
    void Insert(string projectName, int cost, string region);
    void displayHash();
    void searchHash();
    void searchHash(string projName);
    void deleteHash(string projName);




};

#endif 
