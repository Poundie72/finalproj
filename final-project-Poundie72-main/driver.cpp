#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "MovieHashTable.hpp"
#include "DirectorSkipList.hpp"

using namespace std;

// Function prototypes
MovieNode* parseMovieLine(string line);
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList);
void display_menu();


// Main function
int main(int argc, char* argv[]) {
    // TODO
    if(argc != 4)
    {
        cout << "Invalid number of arguments." << endl;
        cout << "Usage: ./<program name> <csv file> <hashTable size> <skipList size>" << endl;
    }
    string filename = argv[1];
    int hashSize = stoi(argv[2]);
    int skipSize = stoi(argv[3]);

    MovieHashTable hashTable(hashSize);
    DirectorSkipList skipList(skipSize, DEFAULT_LEVELS);

    readMovieCSV(filename, hashTable, skipList);

    MovieNode* mTemp;
    DirectorSLNode* dTemp;
    string movieName;
    string directorName;

    int choice = 0;

    while (choice != 5)
    {
        cout << endl << "Number of collisions: " << hashTable.getCollisions() << endl;
        display_menu();
        cin >> choice;

        switch(choice)
        {
            case 1:
                cout << "Enter movie name: " <<  endl;
                cin.clear();
                cin.ignore();
                getline(cin, movieName);
                mTemp = hashTable.search(movieName);
                cout << movieName << " is directed by " << mTemp->director << endl;
            break;

            case 2:
                cout << "Enter director name: " <<  endl;
                cin.clear();
                cin.ignore();
                getline(cin, directorName);
                dTemp = skipList.search(directorName);
                cout << directorName << " directed " << dTemp->movies.size() << " movies." << endl;
            break;

            case 3:
                cout << "Enter movie name: " <<  endl;
                cin.clear();
                cin.ignore();
                getline(cin, movieName);
                mTemp = hashTable.search(movieName);
                cout << "Summary: " << movieName << " is a " << mTemp->year << " (" << mTemp->genre << ") film featuring " << mTemp->actors << "." << endl;
                cout << "Plot: " << mTemp->description << endl; 
            break;

            case 4:
                cout << "Enter director name: " <<  endl;
                cin.clear();
                cin.ignore();
                getline(cin, directorName);
                dTemp = skipList.search(directorName);

                cout << directorName << " directed the following movies: " << endl;

                for(int i = 0; i < dTemp->movies.size(); i++)
                {
                    cout << i << ". " << dTemp->movies[i]->title << endl;
                }
            break;
            
            case 5:
                cout << "goodBYE" << endl;
                return 0;
            break;

            default:
                cout << "pleas enter a valid choice :(" << endl;
            break;
        }

    }
    


    return 0;
}

// Function to parse a CSV line into a MovieNode object
MovieNode* parseMovieLine(string line) {
    stringstream ss(line);
    vector<string> fields;
    string field;

    // Loop through the characters in the line
    bool in_quotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '\"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            // add field to vector and reset for next field
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
            // handle double quotes inside a quoted field
            if (in_quotes && c == '\"' && i < line.length() - 1 && line[i+1] == '\"') {
                field += '\"'; // add the second double quote and skip it
                ++i;
            }
        }
    }
    fields.push_back(field);

    if (fields.size() != 12) {
        cerr << "Error: Invalid movie line format" << line << endl;
        return nullptr;
    }

    int rank = stoi(fields[0]);
    string title = fields[1];
    string genre = fields[2];
    string description = fields[3];
    string director = fields[4];
    string actors = fields[5];
    int year = stoi(fields[6]);
    int runtime = stoi(fields[7]);
    float rating = stof(fields[8]);
    int votes = stoi(fields[9]);
    float revenue = stof(fields[10]);
    int metascore = stoi(fields[11]);

    // Create a new MovieNode object with the parsed fields
    MovieNode* movie = new MovieNode(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);
    return movie;
}

// Function to read a CSV file into a vector of MovieNode objects
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList) {
    // TODO
    string line;
    ifstream inFile(filename);

    if(!inFile.is_open())
    {
        cout << "File not opened" << endl;
        return;
    }

    getline(inFile, line);//skips first line

    while(getline(inFile, line))
    {
        
        MovieNode* temp = parseMovieLine(line);
        
        movieTable.insert(temp->title, temp);
        
        directorList.insert(temp->director, temp);
        
    } 
}

// Function to display the menu options
void display_menu() {
    // TODo
    
    cout << "Please select an option:" << endl;
    cout << "1. Find the director of a movie" << endl;
    cout << "2. Find the number of movies by a director" << endl;
    cout << "3. Find the description of a movie" << endl;
    cout << "4. List the movies by a director" << endl;
    cout << "5. Quit" << endl;
    cout << endl;
    cout << "Enter an option:" << endl;


}

