#include<iostream>
#include <vector>
#include "MovieHashTable.hpp"
using namespace std;

// Constructor for MovieHashTable with default size
MovieHashTable::MovieHashTable() {
    // TODO
    table_size = DEFAULT_HTABLE_CAPACITY;

    table = new MovieNode*[table_size];

    for(int i = 0; i < table_size; i++)
    {
        table[i] = nullptr;
    }
    n_collisions = 0;
}

// Constructor for MovieHashTable with given size
MovieHashTable::MovieHashTable(int s) {
    // TODO
    table_size = s;

    table = new MovieNode*[table_size];

    for(int i = 0; i < table_size; i++)
    {
        table[i] = nullptr;
    }
    n_collisions = 0;
}

// Destructor for MovieHashTable that deletes all nodes in the hash table
MovieHashTable::~MovieHashTable() {
    // TODO
    for(int i = 0; i < table_size; i++)
    {
        table[i] = nullptr;
    }
    delete table;
}

// Hash function for MovieHashTable that returns an index in the hash table for a given movie title.
// Students must use their identikey to come up with a creative hash function that minimizes collisions
// for the given IMDB-Movie database to ensure efficient insertion and retrieval of movie nodes.
int MovieHashTable::hash(string title) {
    string idkey = "dada";
    int foo = 3878;
    
    for(int i = 0; i < title.size(); i++)
    {
        foo += title[i] + '0';
    }
    for(int i = 0; i < idkey.size(); i++)
    {
        foo += idkey[i] + '0';
    }

    int hashkey = foo%table_size;
    return hashkey;
}

// Inserts a movie node into the hash table with the specified title
void MovieHashTable::insert(string title, MovieNode* movie) {
    int key = hash(title);

    // if(table[key] == nullptr)
    // {
    //     table[key] = movie;
    //     return;
    // }

    for(int i = 0; i < table_size; i++)
    {
        if(table[(key+i)%table_size] != nullptr)
        {
            this->setCollisions();
        }
        else if(table[(key+i)%table_size] == nullptr)
        {
            table[key] = movie;

            return;
        }
    }
}

// Searches for a node in the hash table with the specified title
MovieNode* MovieHashTable::search(string title) {
    // TODO
    int key = hash(title);
    cout << "woo" << endl;
    cout << key << endl;
    cout << "tabel size: " << table_size << endl;

    for(int i = key; i < table_size; i++)
    {
        cout << "woo" << i << endl;
        cout << table[i%table_size]->title << endl;
        if(table[i%table_size]->title == title)
        {
            return table[i%table_size];
        }
    }
    return nullptr;
}

// Returns the number of collisions that have occurred during insertion into the hash table
int MovieHashTable::getCollisions() {
  
    return n_collisions;
}

// Increments the number of collisions that have occurred during insertion into the hash table
void MovieHashTable::setCollisions() {
    // TODO
    this->n_collisions++;
}
