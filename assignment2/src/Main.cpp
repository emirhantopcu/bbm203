#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "LibrarySystem.h"

using namespace std;

int main(int argc, char** argv) {
    const char *outputFile = argv[2];
    freopen(outputFile, "w+", stdout);
    cout << "===Movie Library System===" << endl;
    ifstream commands;
    commands.open(argv[1]);
    vector<string> lines;
    ifstream command_file(argv[1]);
    string oneline;
    string checker;
    vector<vector<string>> splitted_lines;
    while (getline(command_file, oneline)) {
        stringstream ss(oneline);
        string b;
        vector<string> splitted_line;
        while (getline(ss, b, '\t')) {
            splitted_line.push_back(b);
        }
        splitted_lines.push_back(splitted_line);
    }
    for(string line; getline(commands, line);){
        lines.push_back(line);
    }
    for (int i = 0; i < lines.size(); ++i) {
        bool checker = false;
        if (i == 0){
            checker = true;
        }else{
            if (splitted_lines[i][0] != splitted_lines[i - 1][0]){
                checker = true;
            }
        }
        if (splitted_lines[i][0] == "addMovie"){
            if (checker){
                cout << endl;
                cout << "===addMovie() method test===" << endl;
            }
            LibrarySystem::addMovie(stoi(splitted_lines[i][1]), splitted_lines[i][2], stoi(splitted_lines[i][3]));
        }else if(splitted_lines[i][0] == "deleteMovie"){
            if (checker){
                cout << endl;
                cout << "===deleteMovie() method test===" << endl;
            }
            LibrarySystem::deleteMovie(stoi(splitted_lines[i][1]));
        }else if(splitted_lines[i][0] == "addUser"){
            if (checker){
                cout << endl;
                cout << "===addUser() method test===" << endl;
            }
            LibrarySystem::addUser(stoi(splitted_lines[i][1]), splitted_lines[i][2]);
        }else if(splitted_lines[i][0] == "deleteUser"){
            if (checker){
                cout << endl;
                cout << "===deleteUser() method test===" << endl;
            }
            LibrarySystem::deleteUser(stoi(splitted_lines[i][1]));
        }else if(splitted_lines[i][0] == "checkoutMovie"){
            if (checker){
                cout << endl;
                cout << "===checkoutMovie() method test===" << endl;
            }
            LibrarySystem::checkoutMovie(stoi(splitted_lines[i][1]), stoi(splitted_lines[i][2]));
        }else if(splitted_lines[i][0] == "showUser"){
            if (checker){
                cout << endl;
                cout << "===showUser() method test===" << endl;
            }
            LibrarySystem::showUser(stoi(splitted_lines[i][1]));
        }else if(splitted_lines[i][0] == "showMovie"){
            if (checker){
                cout << endl;
                cout << "===showMovie() method test===" << endl;
            }
            LibrarySystem::showMovie(stoi(splitted_lines[i][1]));
        }else if(splitted_lines[i][0] == "showAllMovie"){
            if (checker){
                cout << endl;
                cout << "===showAllMovie() method test===" << endl;
            }
            LibrarySystem::showAllMovie();
        }else if(splitted_lines[i][0] == "returnMovie"){
            if (checker){
                cout << endl;
                cout << "===returnMovie() method test===" << endl;
            }
            LibrarySystem::returnMovie(stoi(splitted_lines[i][1]));
        }
    }
}
