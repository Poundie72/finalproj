#include<iostream>
#include <vector>
#include "DirectorSkipList.hpp" 
using namespace std;

// Constructor for DirectorSkipList with default capacity and levels
DirectorSkipList::DirectorSkipList() {
    // TODO
    this->capacity = DEFAULT_CAPACITY;
    this->levels = DEFAULT_LEVELS;
    head = nullptr;
}

// Constructor for DirectorSkipList with given capacity and levels
DirectorSkipList::DirectorSkipList(int _cap, int _levels) {
    // TODO
    this->capacity = _cap;
    this->levels = _levels;
    head = nullptr;
}

// Destructor for DirectorSkipList that deletes all nodes in the skip list (but not the MovieNodes, which are shared with other data structures)
DirectorSkipList::~DirectorSkipList() {
    // TODO
    DirectorSLNode* temp = new DirectorSLNode();
    DirectorSLNode* curr = new DirectorSLNode();
    curr = head;


    while(curr != nullptr)
    {
        temp = curr;
        curr = curr->next[0];
        delete temp;
    }
}

// Inserts a movie node into the skip list with the specified director
void DirectorSkipList::insert(string director, MovieNode* _movie) {
    // TODO
    srand(time(0));
    int n_levels = 1;
    while(n_levels < levels && rand() % 2 == 0)
    {
        n_levels++;
    }
  

    DirectorSLNode* temp = search(director);
    
    if(temp == nullptr)
    {
        DirectorSLNode* curr = head;
        DirectorSLNode** prev = new DirectorSLNode*[levels];

        temp = new DirectorSLNode(director, levels);
        temp->addMovie(_movie);
        if(head == nullptr)
        {
            head = temp;
            return;
        }
        
        for(int i = 0; i < levels; i++)
        {
            prev[i] = nullptr;
        }
        
        for(int i = levels-1; i >= 0; i--)//searches for place of insertion
        {
            while(curr->next[i] != nullptr && curr->next[i]->director < director)
            {
                curr = curr->next[i];
            }
            prev[i] = curr;
        }

        for(int i = n_levels; i >= 0; i--)
        {
            temp->next[i] = prev[i]->next[i];
            prev[i]->next[i] = temp;
        }

        delete[] prev;
        size++;

    }
    else
    {
        temp->addMovie(_movie);
    }
   
}

// Searches for a node in the skip list with the specified director
DirectorSLNode *DirectorSkipList::search(string director) {
    // TODO
    DirectorSLNode* curr; //= new DirectorSLNode();
    curr = head;

    if(head == nullptr){
        return nullptr;
    }

    for(int i = levels-1; i >= 0; i--)
    {
        while(curr->next[i] != nullptr && curr->next[i]->director < director)
        {
            curr = curr->next[i];
        }
    }


    curr = curr->next[0]; //curr was the node before the correct director

    if (curr != nullptr && curr->director == director)
    {
        return curr;
    }
    else
    {
        return nullptr;
    }

    return nullptr;
}

// Pretty-prints the skip list
void DirectorSkipList::prettyPrint() {
    // TODO

}
