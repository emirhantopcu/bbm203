#include <iostream>
#include <fstream>

using namespace std;


class Stock{
public:
    string cards[24];
    string *waste[3]={&null,&null,&null};
    string null;
    int waste_current = 0;
    int openFromStock(){
        if (waste_current > lastAvailable()){
            reearrangeStock();
            waste_current=0;
            waste[0]=&null;
            waste[1]=&null;
            waste[2]=&null;
            return 0;
        }
        int count = 2;
        for (int i = waste_current; i < 24; ++i) {
            if (count == -1){
                break;
            }else if(cards[i].size() == 3){
                waste[count] = &cards[i];
                waste_current++;
                count--;
            }else if(cards[i].size() == 0){
                waste[count] = &null;
                count--;
            }
        }
        return 0;
    }
    int lastAvailable(){
        int last_valuable;
        for (int i = 0; i < 24; ++i) {
            if (cards[i].size() == 3){
                last_valuable = i;
            }
        }
        return last_valuable;
    }
    void reearrangeStock(){
        int count = 0;
        for (int i = 0; i < 24; ++i) {
            if (cards[i] != ""){
                cards[count]=cards[i];
                if (count != i){
                    cards[i] = "";
                }
                count++;
            }
        }
    }
    void rearrangeWaste(){
        int count = 0;
        for (int i = 0; i < 3; ++i) {
            if (*waste[i] == ""){
                count++;
            }
        }
        int initial_check = waste_current-1;
        if (count == 3){
            for (int i = initial_check; i > -1; --i) {
                if (!(cards[i].size() == 0)){
                    waste[2] = &cards[i];
                    break;
                }
            }
        }
    }
    bool isEmpty(){
        for (int i = 0; i < 24; ++i) {
            if (!(cards[i] == "")){
                return false;
            }
        }
        return true;
    }
};

class Pile{
public:
    string cards[19];
    void takeCards(string card_in){
        if (isEmpty()){
            int last_card = lastCardIndex();
            for (int i = last_card; i >= 0; --i) {
                cards[i+1] = cards[i];
            }
            cards[0] = card_in;
        }
    }

    void open(){
        if(cards[0].size() == 6){
            cards[0] = cards[0].substr(0,3);
        }else{
            cout << "Invalid Move!" << endl << endl;
        }
    }

    int lastCardIndex(){
        int last_card;
        for (int i = 0; i < 19; ++i) {
            if(cards[i] == ""){
                last_card = i-1;
                break;
            }
        }
        return last_card;
    }

    void rearrangePile(){
        if (cards[0] == ""){
            int count = 0;
            for (int i = 0; i < 19; ++i) {
                if (!(cards[i] == "")){
                    cards[count] = cards[i];
                    cards[i] = "";
                    count++;
                }
            }
        }
    }

    bool isEmpty(){
        int counter = 0;
        for (auto & card : cards) {
            if (card == ""){
                counter++;
            }
        }
        if (counter == 0){
            return false;
        }else{
            return true;
        }
    }
};

class Foundation{

public:
    string cardsF[13];

    bool isFoundation(string card){
        if (!(card.size() == 6)){
            if((cardsF[0] == "")){
                if (stoi(card.substr(1,2)) == 1){
                    return true;
                }
                else{
                    cout << "Invalid Move!" << endl << endl;
                    return false;
                }
            }
            else if (stoi(card.substr(1,2))-1 == stoi(cardsF[0].substr(1,2))){
                return true;
            }else{
                cout << "Invalid Move!" << endl << endl;
                return false;
            }
        }else{
            cout << "Invalid Move!" << endl << endl;
        }
    }
    void rearrangeFoundation(){
        if (cardsF[0] == ""){
            int count = 0;
            for (int i = 0; i < 19; ++i) {
                if (!(cardsF[i] == "")){
                    cardsF[count] = cardsF[i];
                    cardsF[i] = "";
                    count++;
                }
            }
        }
    }
};

Foundation foundation0;
Foundation foundation1;
Foundation foundation2;
Foundation foundation3;
Foundation *foundation_area[4] = {&foundation0,&foundation1,&foundation2,&foundation3};

Pile pile0;
Pile pile1;
Pile pile2;
Pile pile3;
Pile pile4;
Pile pile5;
Pile pile6;
Pile *tableau_area[7] = {&pile0,&pile1,&pile2,&pile3,&pile4,&pile5,&pile6};
Stock stock;

bool cardPlayable(string src_card, string dest_card){
    if (!(dest_card == "")){
        if(stoi(src_card.substr(1,2))+1 == stoi(dest_card.substr(1,2))){
            if (src_card.substr(0,1) == "D" &&
                (dest_card.substr(0,1) == "C" || dest_card.substr(0,1) == "S")){
                return true;
            }
            else if(src_card.substr(0,1) == "H" &&
                    (dest_card.substr(0,1) == "C" || dest_card.substr(0,1) == "S")){
                return true;
            }
            else if(src_card.substr(0,1) == "C" &&
                    (dest_card.substr(0,1) == "H" || dest_card.substr(0,1) == "D")){
                return true;
            }
            else if(src_card.substr(0,1) == "S" &&
                    (dest_card.substr(0,1) == "H" || dest_card.substr(0,1) == "D")){
                return true;
            }
            else{
                cout << "Invalid Move!" << endl << endl;// outputa yazılcak
                return false;
            }
        }else{
            cout << "Invalid Move!" << endl << endl;// outputa yazılcak
            return false;
        }
    }else if (stoi(src_card.substr(1,2)) == 13){
        return true;
    }else{
        cout << "Invalid Move!" << endl << endl;// outputa yazılcak
        return false;
    }
}

void moveToFoundationSub(string card, int f,int src_pile){
    if (foundation_area[f]->isFoundation(card)){
        for (int i = 12; i > 0; --i) {
            foundation_area[f]->cardsF[i] = foundation_area[f]->cardsF[i-1];
        }
        foundation_area[f]->cardsF[0] = card;
        tableau_area[src_pile]->cards[0] = "";
        tableau_area[src_pile]->rearrangePile();
    }
}

void moveToFoundation(int src_pile){
    if(tableau_area[src_pile]->cards[0].substr(0,1) == "H"){
        moveToFoundationSub(tableau_area[src_pile]->cards[0], 0,src_pile);
    }
    else if(tableau_area[src_pile]->cards[0].substr(0,1) == "D"){
        moveToFoundationSub(tableau_area[src_pile]->cards[0], 1,src_pile);
    }
    else if(tableau_area[src_pile]->cards[0].substr(0,1) == "S"){
        moveToFoundationSub(tableau_area[src_pile]->cards[0], 2,src_pile);
    }
    else if(tableau_area[src_pile]->cards[0].substr(0,1) == "C"){
        moveToFoundationSub(tableau_area[src_pile]->cards[0], 3,src_pile);
    } else{
        cout << "Invalid Move!" << endl << endl;
    }
}

void moveToFoundationWaste(){
    int condition = true;
    for (int i = 0; i < 3; ++i) {
        if (!(*stock.waste[i] == "")){
            condition = false;
            int f;
            if (stock.waste[i]->substr(0,1) == "H"){
                f = 0;
            }else if (stock.waste[i]->substr(0,1) == "D"){
                f = 1;
            }else if (stock.waste[i]->substr(0,1) == "S"){
                f = 2;
            }else if (stock.waste[i]->substr(0,1) == "C"){
                f = 3;
            }
            if (foundation_area[f]->isFoundation(*stock.waste[i])){
                for (int i = 12; i > 0; --i) {
                    foundation_area[f]->cardsF[i] = foundation_area[f]->cardsF[i-1];
                }
                foundation_area[f]->cardsF[0] = *stock.waste[i];
                *stock.waste[i] = "";
                break;
            } else{
                break;
            }
        }
    }
    if (condition){
        cout << "Invalid Move!" << endl << endl;
    }
    stock.rearrangeWaste();
}

void moveFoundation(int src_f, int dest_pile){
    if (!(foundation_area[src_f]->cardsF[0] == "")){
        if(cardPlayable(foundation_area[src_f]->cardsF[0], tableau_area[dest_pile]->cards[0])){
            tableau_area[dest_pile]->takeCards(foundation_area[src_f]->cardsF[0]);
            foundation_area[src_f]->cardsF[0] = "";
            foundation_area[src_f]->rearrangeFoundation();
        }
    }else{
        cout << "Invalid Move!" << endl << endl;
    }
}

void movePile(int src_pile, int src_pile_index, int dest_pile){
    if (tableau_area[src_pile]->cards[src_pile_index].size() == 3){
        if (cardPlayable(tableau_area[src_pile]->cards[src_pile_index],tableau_area[dest_pile]->cards[0])){
            for (int i = src_pile_index; i >= 0; --i) {
                tableau_area[dest_pile]->takeCards(tableau_area[src_pile]->cards[i]);
                tableau_area[src_pile]->cards[i] = "";
            }
            tableau_area[src_pile]->rearrangePile();
        }
    } else{
        cout << "Invalid Move!" << endl << endl;// outputa yazılcak
    }
}

void moveWaste(int dest_pile){
    bool condition = true;
    for (int i = 0; i < 3; ++i) {
        if (!(*stock.waste[i] == "")){
            condition = false;
            if (cardPlayable(*stock.waste[i], tableau_area[dest_pile]->cards[0])){
                tableau_area[dest_pile]->takeCards(*stock.waste[i]);
                *stock.waste[i] = "";
                break;
            } else{
                break;
            }
        }
    }
    if (condition){
        cout << "Invalid Move!" << endl << endl;
    }
    stock.rearrangeWaste();
}

void outputMaker(){
    cout << endl;
    if (stock.waste_current >= stock.lastAvailable() || stock.isEmpty()){
        cout << "___ ";
    } else{
        cout << "@@@ ";
    }
    for (int i = 0; i < 3; ++i) {
        if (*stock.waste[abs(2-i)] == ""){
            cout << "___ ";
        }
        else{
            cout << *stock.waste[abs(2 - i)] << " ";
        }
    }
    cout << "        ";
    for (int i = 0; i < 4; ++i) {
        if (foundation_area[i]->cardsF[0] == ""){
            cout << "___ ";
        }else{
            cout << foundation_area[i]->cardsF[0] << " ";
        }
    }
    cout << endl << endl;
    int max_value;
    max_value = tableau_area[0]->lastCardIndex();
    for (int i = 1; i < 7; ++i) {
        max_value = max(max_value,tableau_area[i]->lastCardIndex());
    }
    max_value++;
    for (int i = 0; i < max_value; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (tableau_area[j]->lastCardIndex()-i < 0){
                cout << "      ";
            } else if (tableau_area[j]->lastCardIndex()-i >= 0){
                if (tableau_area[j]->cards[tableau_area[j]->lastCardIndex()-i].size() == 6){
                    cout << "@@@   ";
                }else{
                    cout << tableau_area[j]->cards[tableau_area[j]->lastCardIndex() - i] << "   ";
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}

void gameStatus(){
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        if (!(foundation_area[i]->cardsF[0]== "")){
            if (stoi(foundation_area[i]->cardsF[0].substr(1,2)) == 13){
                count++;
            }
        }
    }
    if (count == 4){
        cout << endl << "****************************************" << endl << endl;
        cout << "You Win!" << endl << endl;
    }
}

int main(int argc, char** argv) {
    string deck[52];
    ifstream input(argv[1]);
    const char *outputFile = argv[3];
    freopen(outputFile, "w+", stdout);
    int i = 51;
    for(string line; getline(input, line);){
        deck[i] = line;
        i--;
    }
    int dikey = 7;
    int deck_index = 0;
    for (int j = 0; j < 7; ++j) {
        int index_two = 0;
        for (int k = 7-dikey; k < 7; ++k) {
            tableau_area[k]->cards[index_two] = deck[deck_index];
            deck[deck_index] = "";
            deck_index++;
            index_two++;
        }
        dikey--;
    }
    int stock_index = 0;
    for (int j = 0; j < 52; ++j) {
        if (!(deck[j] == "")){
            stock.cards[stock_index] = deck[j];
            stock_index++;
        }
    }
    for(auto & pile : tableau_area){
        for (int j = 1; j < 19; ++j) {
            if (!(pile->cards[j].empty()))
            pile->cards[j] = pile->cards[j]+"@@@";
        }
    }
    ifstream commands;
    commands.open(argv[2]);
    outputMaker();
    if (!commands.is_open()){
        cout << "exit" << endl << endl;
        cout << "****************************************" << endl << endl;
        cout << "Game Over!" << endl;
        return 0;
    }
    for(string line; getline(commands, line);){
        if (line.substr(0,1) == "m"){
            if (line.substr(5,1) == "t"){
                if (line.substr(19,1) == "p"){
                    cout << line << endl << endl;
                    moveToFoundation(stoi(line.substr(24,1)));
                    cout << "****************************************" << endl;
                    outputMaker();
                    gameStatus();
                }else if(line.substr(19,1) == "w"){
                    cout << line << endl << endl;
                    moveToFoundationWaste();
                    cout << "****************************************" << endl;
                    outputMaker();
                    gameStatus();
                }
            }else if (line.substr(5,1) == "p"){
                if (line.size() == 16){
                    cout << line << endl << endl;
                    movePile(stoi(line.substr(10,1)),stoi(line.substr(12,2)),stoi(line.substr(15,1)));
                    cout << "****************************************" << endl;
                    outputMaker();
                    gameStatus();
                }else{
                    cout << line << endl << endl;
                    movePile(stoi(line.substr(10,1)),stoi(line.substr(12,1)),stoi(line.substr(14,1)));
                    cout << "****************************************" << endl;
                    outputMaker();
                    gameStatus();
                }
            }else if (line.substr(5,1) == "w"){
                cout << line << endl << endl;
                moveWaste(stoi(line.substr(11,1)));
                cout << "****************************************" << endl;
                outputMaker();
                gameStatus();
            }else if (line.substr(5,1) == "f"){
                cout << line << endl << endl;
                moveFoundation(stoi(line.substr(16,1))-1,stoi(line.substr(18,1)));
                cout << "****************************************" << endl;
                outputMaker();
                gameStatus();
            }
        }else if (line.substr(0,1) == "o"){
            if (line.substr(5,1) == "f"){
                cout << line << endl << endl;
                stock.openFromStock();
                cout << "****************************************" << endl;
                outputMaker();
                gameStatus();
            }else{
                cout << line << endl << endl;
                tableau_area[stoi(line.substr(5,1))]->open();
                cout << "****************************************" << endl;
                outputMaker();
                gameStatus();
            }
        }else if(line.substr(0,1) == "e"){
            cout << line << endl << endl;
            cout << "****************************************" << endl << endl;
            cout << "Game Over!" << endl;
            return 0;
        }
    }
    cout << "Game Over!" << endl;
    return 0;
}