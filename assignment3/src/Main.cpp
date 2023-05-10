#include <iostream>
#include <fstream>
#include "Stack.h"
#include "Queue.h"
#include "DoublyLinkedList.h"
#include <vector>
#include <sstream>

using namespace std;

struct Package{
    string name;
};
struct Truck: Package{};

struct Destination{
    string name;
    Stack<Package> warehouse;
    Queue<Truck> garage;
};

void listElements(Stack<Package> stack){
    vector<Package> output_packages;
    output_packages = stack.listElements();
    for (int j = 0; j < output_packages.size(); ++j) {
        cout << output_packages[j].name << endl;
    }
}
void listElements(Queue<Truck> queue){
    vector<Truck> output_trucks;
    output_trucks = queue.listElements();
    for (int j = 0; j < output_trucks.size(); ++j) {
        cout << output_trucks[j].name << endl;
    }
}

int main(int argc, char** argv) {
    const char *outputFile = argv[5];
    freopen(outputFile, "w+", stdout);
    ifstream destinations;
    destinations.open(argv[1]);
    vector<Destination> dests;
    for(string line; getline(destinations, line);){
        Destination d;
        d.name = line;
        dests.push_back(d);
    }
    ifstream packages(argv[2]);
    string line;
    while (getline(packages,line)){
        vector<string> parsedString;
        stringstream pline(line);
        string word;
        while (getline(pline,word,' ')){
            parsedString.push_back(word);
        }
        Package newPackage;
        newPackage.name = parsedString.at(0);
        for (int i = 0; i < dests.size(); ++i) {
            if (dests[i].name == parsedString[1]){
                dests[i].warehouse.push(newPackage);
            }
        }
    }
    ifstream trucks(argv[3]);
    string tline;
    while (getline(trucks,tline)){
        vector<string> parsedStringT;
        stringstream pline(tline);
        string word;
        while (getline(pline,word,' ')){
            parsedStringT.push_back(word);
        }
        Truck newTruck;
        newTruck.name = parsedStringT.at(0);
        for (int i = 0; i < dests.size(); ++i) {
            if (dests[i].name == parsedStringT[1]){
                dests[i].garage.enqueue(newTruck);
            }
        }
    }
    ifstream missions(argv[4]);
    string mline;
    while (getline(missions,mline)){
        vector<string> parsedStringM;
        stringstream pline(mline);
        string word;
        while (getline(pline,word,'-')){
            parsedStringM.push_back(word);
        }
        vector<string> indices;
        stringstream indexline(parsedStringM.at(5));
        string number;
        while (getline(indexline,number,',')){
            indices.push_back(number);
        }
        DoublyLinkedList<Package> mission;
        for (int i = 0; i < dests.size(); ++i) {
            if (dests[i].name == parsedStringM.at(0)){
                Truck truck;
                dests[i].garage.getFront(truck);
                dests[i].garage.dequeue();
                mission.append(truck);
                for (int j = 0; j < stoi(parsedStringM.at(3)); ++j) {
                    Package aPackage;
                    dests[i].warehouse.getTop(aPackage);
                    dests[i].warehouse.pop();
                    mission.append(aPackage);
                }
            }
        }
        for (int i = 0; i < dests.size(); ++i) {
            if (dests[i].name == parsedStringM.at(1)){
                for (int j = 0; j < stoi(parsedStringM.at(4)); ++j) {
                    Package aPackage;
                    dests[i].warehouse.getTop(aPackage);
                    dests[i].warehouse.pop();
                    mission.append(aPackage);
                }
                vector<string> toDelete;
                for (int j = 0; j < indices.size(); ++j) {
                    toDelete.push_back(mission.get(stoi(indices[j])+1).name);
                    dests[i].warehouse.push(mission.get(stoi(indices[j])+1));
                }
                for (int j = 0; j < toDelete.size(); ++j) {
                    for (int k = 0; k < mission.size(); ++k) {
                        if (toDelete.at(j) == mission.get(k).name){
                            mission.remove(k);
                            break;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < dests.size(); ++i) {
            if (dests[i].name == parsedStringM.at(2)){
                Truck truck;
                truck.name = mission.get(0).name;
                dests[i].garage.enqueue(truck);
                mission.remove(0);
                for (int j = 0; j < mission.size(); ++j) {
                    dests[i].warehouse.push(mission.get(j));
                }
            }
        }
    }
    for (int i = 0; i < dests.size(); ++i) {
        cout << dests[i].name << endl;
        cout << "Packages:" << endl;
        listElements(dests[i].warehouse);
        cout << "Trucks:" << endl;
        listElements(dests[i].garage);
        cout << "-------------" << endl;
    }
    return 0;
}
