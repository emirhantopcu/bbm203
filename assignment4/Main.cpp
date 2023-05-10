#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <fstream>

using namespace std;

struct Node{
    Node(){
    }
    int frequency = 0;
    char label;
    Node* zero = nullptr;
    Node* one = nullptr;
};

struct less_than_key{
    //comparator for sorting the frequency list
    inline bool operator() (const Node *node1, const Node *node2){
        return (node1->frequency < node2->frequency);
    }
};

bool doesExist(char search, vector<Node*> list){
    //checkes if the node already exists in the frequency table
    for (int i = 0; i < list.size(); ++i) {
        if (list.at(i)->label == search){
            return true;
        }
    }
}

int getIndex(char search, vector<Node*> list){
    //gives the index of the node with the wanted label
    for (int i = 0; i < list.size(); ++i) {
        if (list.at(i)->label == search){
            return i;
        }
    }
}

void getCode(string code,Node* node,unordered_map<char, string> &code_table){
    //checks the given node if its a leaf node, if not calls the same function again for the right direction
    //each time it calls itself the code gets extended with zero or one
    if (node == nullptr){
        return;
    }
    if (!node->zero && !node->one){
        code_table[node->label] = code;
        return;
    }

    getCode(code +"0", node->zero, code_table);
    getCode(code +"1", node->one, code_table);
}

void encode(string to_be_encoded, string &encoded,unordered_map<char,string> code_table){
    //takes chars in the input line one by one and updates the encoded string line with their codes
    for (int i = 0; i < to_be_encoded.size(); ++i) {
        for (auto pair: code_table) {
            if (to_be_encoded.at(i) == pair.first){
                encoded += pair.second;
            }
        }
    }
}

void decode(Node* root, int &current_index, string encoded){
    // checkes if the node is a leaf, if so prints nodes label
    if (root == nullptr){
        return;
    }
    if (root->zero == nullptr && root->one == nullptr){
        cout << root->label;
        return;
    }
    //increases the index for next operation
    current_index++;
    //calls the function again according to the next bit in the encoded line
    if (encoded.at(current_index) == '0'){
        decode(root->zero,current_index,encoded);
    }else{
        decode(root->one,current_index, encoded);
    }
}

string serialize(Node *root){
    //checks the node if its null, if not calls the same function for left and right nodes
    if (root == nullptr){
        return "~";
    }
    string zero_serialized = serialize(root->zero);
    string one_serialized = serialize(root->one);
    string label_string(1,root->label);
    return label_string+zero_serialized+one_serialized;
}

Node* deserializeExtension(queue<char> &nodes){
    //for every char in the queue, it checkes them if they represent a null node pointer, if not creates a node with the char
    //for the child nodes calls the function again
    char label = nodes.front(); nodes.pop();
    if (label == '~'){
        return nullptr;
    }
    Node* new_node = new Node();
    new_node->label = label;
    new_node->zero = deserializeExtension(nodes);
    new_node->one = deserializeExtension(nodes);
    return new_node;
}

Node* deserialize(string to_be_deserialized){
    //uses a queue to store the chars, then sends it to the extension function
    queue<char> nodes;
    for (auto label:to_be_deserialized) {
        nodes.push(label);
    }
    return deserializeExtension(nodes);
}

void list(Node* node,int depth){
    //for current node, it looks if the node is a leaf, if so prints the label - if the label is not a letter, it prints "-*" -
    //also prints some characters according to the depth count to show the depth of the nodes on screen
    if (node == nullptr){
        return;
    }else{
        for (int i = 0; i < depth; ++i) {
            cout << " |";
        }
        if (node->label != '~' && node->label != '^'){
            cout << " -";
            cout << node->label << endl;
        }else{
            cout << " -*" << endl;
        }
    }
    //if the node is not a leaf calls the same function for child nodes
    list(node->zero,depth+1);
    list(node->one,depth+1);
}

vector<Node*> frequencyListMaker(string line){
    //reads every char in the input file and counts them. if the char is not in the frequency list creates a Node pointer
    //if the char exist in the frequency list, it increases that char's Node's frequency by 1.
    //then the program sorts the list and returns it
    vector<Node*> frequency_list;
    for (int i = 0; i < line.size(); ++i) {
        if (frequency_list.empty()){
            Node* new_node = new Node();
            new_node->label = line[i];
            new_node->frequency = 1;
            frequency_list.push_back(new_node);
            continue;
        }
        if(doesExist(line[i], frequency_list)){
            int index = getIndex(line[i], frequency_list);
            frequency_list.at(index)->frequency++;
        }else{
            Node *new_node = new Node();
            new_node->label = line[i];
            new_node->frequency = 1;
            frequency_list.push_back(new_node);
        }
    }
    sort(frequency_list.begin(),frequency_list.end(),less_than_key());
    return frequency_list;
}

Node* treeMaker(vector<Node*> frequency_list){
    Node* root;
    while (frequency_list.size() != 1){
        //takes the first two element from the sorted frequency list
        Node* temp0 = frequency_list[0];
        frequency_list.erase(frequency_list.begin());
        Node* temp1 = frequency_list[0];
        frequency_list.erase(frequency_list.begin());
        Node* new_node = new Node();
        // creates a new node with sum of the two nodes' frequencies as frequency and these two nodes as left and right node
        new_node->frequency = temp0->frequency + temp1->frequency;
        new_node->label = '^';
        new_node->zero = temp0;
        new_node->one = temp1;
        //puts the new node to the frequency list and sorts it again
        frequency_list.push_back(new_node);
        sort(frequency_list.begin(),frequency_list.end(),less_than_key());
        root = new_node;
        //this while loop works until there's 1 node left in the frequency list
    }
    return root;
}

int main() {
    //as soons as program starts working, it takes input line and splits it with " ".
    string input;
    getline(cin,input);
    string parsed;
    stringstream input_stringstream(input);
    vector<string> parsed_command;
    while(getline(input_stringstream,parsed,' ')){
        parsed_command.push_back(parsed);
    }
    //reads the command and executes the right if block.
    if (parsed_command[0] == "-i"){
        if (parsed_command[2] == "-encode"){
            string line;
            ifstream input(parsed_command[1]);
            getline(input,line);
            transform(line.begin(),line.end(),line.begin(),::tolower);
            //reads the file given in the command line, creates a vector of Node pointers and puts every
            // single character with their frequencies in this vector.
            vector<Node*> frequency_list;
            frequency_list = frequencyListMaker(line);
            //makes a tree and returns the pointer of the root node
            Node* root = treeMaker(frequency_list);
            //creates a map for storing the codes of each char
            unordered_map<char,string> code_table;
            //traverses the tree and gets the code table
            getCode("",root,code_table);
            string encoded;
            //encodes the input line by using the code table
            encode(line,encoded,code_table);
            //prints the encoded message
            cout << encoded << endl;
            //creates a file to store the tree for next use
            ofstream serialized_data("s.txt");
            serialized_data << serialize(root) << endl;
        }else if(parsed_command[2] == "-decode"){
            string line;
            ifstream serialized_data("s.txt");  
            getline(serialized_data,line);
            //reads the serialized data file and deserializes it
            Node* deserialized_root = deserialize(line);
            ifstream input(parsed_command[1]);
            string encoded;
            getline(input, encoded);
            //runs a while loop until all the bits in the encoded line are read, calls decode function for every code
            int current = -1;
            while (current < (int)encoded.size() - 2){
                decode(deserialized_root, current, encoded);
            }
            cout << endl;
        }
    }else if (parsed_command[0] == "-s"){
        string line;
        ifstream serialized_data("s.txt");
        getline(serialized_data,line);
        //deserializes the data in the serialized data file and creates the code table
        Node* deserialized_root = deserialize(line);
        unordered_map<char,string> code_table;
        getCode("",deserialized_root,code_table);
        //looks for the given char in the code table map, when found prints it
        for(auto pair: code_table){
            if (parsed_command[1].at(0) == pair.first){
                cout << pair.second << endl;
            }
        }
    }else if (parsed_command[0] == "-l"){
        //lists the deserialized tree
        string line;
        ifstream serialized_data("s.txt");
        getline(serialized_data,line);
        Node* deserialized_root = deserialize(line);
        int depth = 0;
        list(deserialized_root, depth);
    }
    return 0;
}
