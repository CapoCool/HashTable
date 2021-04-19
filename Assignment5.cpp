/*
* Assignment #5
* Dillan Poorman
* dpoorman@asu.edu
* 9/30/2020
* 
* Hash Table class for adding, searching, and removing items from a hash table
* 
* Hash Analysis:
*   I decided to start with the division function (h(k) = k % size) to just the table going
*   and for debugging, however the number of collisions was too much, then I rewatched the 
    lecture and decided to go with the multiplication method with the division method
*   though there are tons of different ways to do it, I decided to use the multiplication method
*   given in class, as it had a nice even spread of the indices, and kept the collisions down to 
*   a minimum, and with the division method it kept the indices within the range of the array
    It took some plugging in numbers to get it working right, but after a few attempts
*   the function worked well.
*/

#include <iostream>
#include <list>
#include <sstream>
#include <string.h>
#include <string>
#include <regex> 
#include <cmath>
#include "HashTable.h"


using namespace std;

//constructor for the hash table. Sets table to null, maxCost, size, and listSize equal to 0;
// I decided to use the linked list class I wrote for assignment 1. 
HashTable::HashTable() {

    table = NULL;
    maxCost = 0;
    size = 0;
    listSize = 0;

}

//hash function using the multiplication method, with the division method. 
//it adds together the ascii values of each character and then uses the multiplication
//and division method to find an index
int HashTable::hashFunc(string k) {
    int index = 0;
    int sum = 0;
    int i;
    for (i = 0; k[i] != '\0'; i++) {
        
        sum += (int)k[i];
        
    }
    
    index = floor(4 * (sum * ((sqrt(3)-1)/3)));
    return index % size;
}

//create an array of linked lists using Assignment #1 linkedlist.h, then sets the size to 10
void HashTable::createTable(int n) {
    table = new LinkedList[n];
    size = n;
}

//inserts an element using the projName as the key.
void HashTable::Insert(string projectName, int cost, string region) {

    int index = hashFunc(projectName);
    table[index].addProject(projectName, cost, region);

}

//overloaded function used to find the maxCost
void HashTable::searchHash() {
    int max = 0;
    int currentMax = 0;
    int index = 0;
    for (int i = 0; i < size; i++) {
        max = table[i].searchList();
        if (max > currentMax) {
            currentMax = max;
            index = i;
        }
        
    }
    
    cout << "The Project: " << table[index].returned.projectName << " has the highest cost of " << currentMax;

}

//overloaded function used to find an element by project name
void HashTable::searchHash(string projName) {
    int index = hashFunc(projName);
    bool result;
    result = table[index].searchList(projName);

    if (result == true) {
        cout << "The Project: ";
        cout << table[index].returned.projectName << " ";
        cout << "with Cost " << table[index].returned.cost << " ";
        cout << "is found" << endl;

    }
    else {
        cout << "The Project: " << projName << "is not found" << endl;
    }
}

//deletes by finding the index and then iterating through the linked list
void HashTable::deleteHash(string projName) {
    int index = hashFunc(projName);
    bool result;
    result = table[index].removeProject(projName);
    if (result == true) {
        
        cout << "The Project : " << table[index].returned.projectName << " ";
        cout << "with Cost " << table[index].returned.cost << " is removed" << endl;
        
        
    }
    else {
        cout << "The Project: " << projName << "is not removed" << endl;
    }
    
}

//displays hash using an already made function from assignment 1
void HashTable::displayHash() {

    cout << "Hash Table Content" << endl;
    cout << "---------------------" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Index: " << i << ", " << "linked list size: " << table[i].listSize << endl;
        
        table[i].printList();
        
    }
}

//used for input validation
void isInteger(string temp, int* n) {

    if (regex_match(temp, regex("^[+-]?[0-9]+$"))) {

        *n = stoi(temp);
    }
    else {
        *n = -1;
    }
}


//main function. 3 loops, one for setting the size using input validation, 1 for inputing the projects
//and the last for commands
int main() {

    
    //set variables
    int cost = 0, n = 0;
    string command, projName, region, temp;
    HashTable hash;

    
    //set size
    while (true) {
        cout << "Please enter the size of the hash table ";
        cin >> temp;
        isInteger(temp, &n);
        if (n <= 0) {
            cout << "Invalid size" << endl;
        }
        else {
            hash.createTable(n);
            break;
        }

    }
    
    //flushes the buffer
    cin.ignore(256, '\n');

    //uses getline by reading it first for the exit statement
    //then sets the variable to ss and then parses it
    while (getline(cin, command) && (command != "EndOfInsertion")) {
        istringstream ss(command);
        getline(ss, projName, ',');
        getline(ss, region, ',');
        ss >> temp;
        isInteger(temp, &cost);
        if (cost <= 0) {
            cout << "Invalid cost" << endl;
        }
        else {
            hash.Insert(projName, cost, region);
        }
    }

    cout << "Please enter a command: hash_display, hash_delete/projectname, hash_search/projectname, hash_max_cost" << endl;
    //does the same thing as above.
    while (getline(cin, command) && (command != "quit")) {
        istringstream ss(command);

        //command to display the hash
        if (command == "hash_display") {
            hash.displayHash();
        }

        //hash_delete, sets the command to region sort of as a do nothing variable, then gets
        //the project name to delete
        else if (regex_match(command, regex("(hash_delete)(.*)"))) {
            getline(ss, region, '/');
            getline(ss, projName);
            
            
            hash.deleteHash(projName);
        }

        //hash_search, sets the command to region as a do nothing variable, and then get the
        // project name to search
        else if (regex_match(command, regex("(hash_search)(.*)"))) {
            getline(ss, region, '/');
            getline(ss, projName);

            if (hash.table == NULL) {
                cout << "the list is empty" << endl;
            }
            else {
                hash.searchHash(projName);
            }


        }

        //hash_max_cost command
        else if (regex_match(command, regex("(hash_max_cost)(.*)"))) {
            if (hash.table == NULL) {
                cout << "the list is empty" << endl;
            }
            else {
                hash.searchHash();
            }
        }

        else {
            cout << "Invalid command" << endl;
        }
    }
    
    

}
