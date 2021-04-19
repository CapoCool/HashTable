// Assignment #1
// Name: Dillan Poorman
// ASU Email Address: dpoorman@asu.edu
// Description: To be completed

#include <iostream> //to use cout
#include <iomanip> //to format output
#include <string> //to use strings

using namespace std;

//struct Project represents some project information
struct Project
{
    string projectName;
    int cost;
    string region;
    struct Project* next;
};

//class LinkedList will contains a linked list of projects
//Edit: uses returned, to display a deleted or found element
class LinkedList
{
private:
    struct Project* head;

public:

    struct Project returned;
    int listSize;
    
    
    LinkedList();
    ~LinkedList();

    bool addProject(string projectName, int numberOfParticipants, string region);
    bool removeProject(string projectName);
    int searchList();
    bool searchList(string projectName);
    void printList();
};

//Constructor to initialize the linked list
LinkedList::LinkedList()
{
    head = NULL;
    
    listSize = 0;
}

//Destructor
//Description: ...... to be completed
LinkedList::~LinkedList()
{
    Project* temp = head;
    int count = 0;
    while (temp != NULL) {
        Project* deleted = temp;
        temp = temp->next;
        delete deleted;
        count++;
    }

    cout << "Number of deleted projects is: " << count << endl;
}

//Description: Adds project to the link list
bool LinkedList::addProject(string newProjectName, int newNumberOfParticipants, string region)
{
    //allocate new project

    try {
        Project* new_project = new Project();

        //place data, I could've placed the data in the conditionals, but it would've been more lines of code, 
        //and inserting the data in the node first helps with readability considering the amount of flow control
        new_project->cost = newNumberOfParticipants;
        new_project->projectName = newProjectName;
        new_project->region = region;


        //temp pointer for comparisons
        Project* temp;

        //base case and first case
        if (head == NULL || head->projectName > new_project->projectName) {
            new_project->next = head;
            head = new_project;
            
            listSize++;
            return true;

        }
        else {

            temp = head;

            //find insertion point, and drops out when loop finds duplicate
            while (temp->next != NULL && temp->next->projectName < new_project->projectName) {

                temp = temp->next;

            }

            //checks for duplicate, if not a duplicate then the algorithm has found the place to add
            //while keeping it alphabetized, also it deletes it when a duplicate it found 
            //to conserve memory during runtime (I think it does, it's
            //been a while since I've used C++)
            if ((temp->projectName == new_project->projectName)
                || (temp->next != NULL && temp->next->projectName == new_project->projectName)) {
                delete(new_project);
                return false;
            }
            else {
                new_project->next = temp->next;
                temp->next = new_project;
            }

            listSize++;
            return true;
        }

    }
    catch (const bad_alloc& e) {

        return false;
    }
}

//Description: Removes project given the name of the project
bool LinkedList::removeProject(string projectName)
{


    
    
    //Project* temp = head;
    Project* temp = head;
    

    //case for null list
    if (head == NULL) {
        return false;
    }

    //case for 1 node or head node, keeps the whole list from being deleted
    if (head->projectName == projectName) {

        
        //case for 1 node, just make it null
        if (head->next == NULL) {
            returned = *head;
            head = NULL;
            
            
            

            listSize--;
            return true;
        }
        
        //if there's another node, it writes the second node to the head node and then deletes the second node.
        returned = *head;
        head->cost = head->next->cost;
        head->region = head->next->region;
        head->projectName = head->next->projectName;

        //temp becomes the next node
        temp = head->next;

        //setting the head to the new second node
        head->next = head->next->next;

        
        listSize--;
        return true;

        

    }

    //case for rest of list, iterates through the list until reaches the end, or a match is made
    while (temp->next != NULL && temp->next->projectName != projectName) {

        temp = temp->next;
    }

    //no match is found
    if (temp->next == NULL) {
        return false;
    }

    //checks for match, and destroys link
    if (temp->next->projectName == projectName) {
        
        returned = *temp->next;
        temp->next = temp->next->next;

       
        listSize--;
        return true;
    }
    
    
    return true;

    

}

//overloaded searchlist function for finding the max in a linked list
int LinkedList::searchList() {
    Project* proj;
    int max = 0;
    //makes sure list is there
    if (head == NULL) {
        return false;
    }

    //sets changed to the head to start from beginning
    proj = head;

    //iterates through list
    while (proj != NULL) {

        //checks for project name match
        if (proj->cost > max) {

            max = proj->cost;

            returned = *proj;
            


        }


        proj = proj->next;
    }
    return max;
}
//overloaded to search linked list given a project name
bool LinkedList::searchList(string projectName)
{
    Project* proj;

    //makes sure list is there
    if (head == NULL) {
        return false;
    }

    //sets changed to the head to start from beginning
    proj = head;

    //iterates through list
    while (proj != NULL) {

        //checks for project name match
        if (proj->projectName == projectName) {

            returned = *proj; 
            return true;


        }


        proj = proj->next;
    }

    return false;
}


//Description: prints based on requirements for project 5
void LinkedList::printList()
{
    struct Project* current = head;

    if (current == NULL) {
        printf("the list is empty");
        cout << endl;
        cout << endl;
    }
    else {
        while (current != NULL) {
            cout << "Project Name: " << current->projectName << endl;
            cout << "Region: " << current->region << endl;
            cout << "Cost: " << current->cost << endl;
            cout << endl;
            cout << endl;
            current = current->next;

        }
    }
    
}
