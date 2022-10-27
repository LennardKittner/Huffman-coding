#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Quicksorter.h"
#include "Node.h"

using namespace std;
map<char, string> result;
map<string, char> resultrev;
map<string, int> binary;
vector<int> times;

void processNode(string value,Node* n){
    if (n->isSingleNode()){
        binary[value] = n->getValue0();
        return;
    }
    processNode(value+"1",n->getNode1());
    processNode(value+"0",n->getNode0());
}

string getbinary(int n, bool b){
    string r;
    while (n!=0){
        r=(n%2==0 ?"0":"1")+r;
        n/=2;
    }

    while (r.size() < (b ? 16 : 8))
        r = "0"+r;
    return r;
}

int powerof(int a,int p){
    int r = a;
    if (p == 0)
        return 1;
    for (int i = 0;i < p-1;i++){
        r = r*a;
    }
    return r;
}

int getDezimal(string a){
    int r = 0;
    for (int i = a.size()-1;i >= 0;i--){
        r = r + (a[i] == '1' ? powerof(2, (a.size()-1)-i) : 0);
    }
    return r;
}

void generateTree(map<char,int> map){
    Quicksorter qs;
    vector<Node*> nodes;

    for (auto const &x : map) {
        int n = x.second;
        times.push_back(n);
    }

    qs.sort(&times);
    for (int i = 0;i < times.size();i++) {
        nodes.push_back(new Node(times[i]));
    }

    while (nodes.size() > 1){
        nodes[0] = new Node(nodes[0],nodes[1]);
        nodes.erase(nodes.begin()+1);
        qs.sort(&nodes);
    }

    Node* tree = nodes[0];

    processNode("",tree);

}

void merge(bool a,map<char, int> map){
    if (a)
        for (auto const &x : map) {
            for (auto const &xx : binary)
               if (x.second == xx.second) {
                    result[x.first] = xx.first;
                    binary[xx.first] = -1;
                    break;
               }
        }
    else
        for (auto const &x : binary) {
            for (auto const &xx : map)
                if (x.second == xx.second) {
                    resultrev[x.first] = xx.first;
                    map[xx.first] = -1;
                    break;
                }
        }

}

int encode(){
    string filename;
    ifstream file;
    getline(cin, filename);
    file.open(filename);

    if (!file.is_open())
        return 1;

    vector<char> chars;
    map<char, int> map;
    char ch;
    while (file.good()) {
        file.get(ch);
        if (file) {
            if (find(chars.begin(), chars.end(), ch) != chars.end()) {
                ++map[ch];
            } else {
                chars.push_back(ch);
                map[ch] = 1;
            }
        }
    }

    generateTree(map);

    merge(true,map);

    file.clear();
    file.seekg( 0, std::ios_base::beg );

    string binaryStr =  "";
    while (file.good()) {
        file.get(ch);
        if (file)
            binaryStr += result[ch];
    }

    bool pedding_2B = false;
    string binaryStrTree = "";
    if (times[times.size()-1]>255)
        pedding_2B = true;

    vector<bitset<8>> binaryTree;
    for (auto const &x : map){
        binaryTree.push_back(bitset<8>((int)x.first));
        if (pedding_2B) {
            string tmp = getbinary(x.second, pedding_2B);
            binaryTree.push_back(bitset<8>(tmp.substr(0, 8)));
            binaryTree.push_back(bitset<8>(tmp.substr(8, 15)));
        }
        else
            binaryTree.push_back(bitset<8>(getbinary(x.second,pedding_2B)));
    }
    binaryTree.push_back(bitset<8>(0));
    if (!pedding_2B)
        binaryTree.push_back(bitset<8>(0));
    else {
        binaryTree.push_back(bitset<8>(0));
        binaryTree.push_back(bitset<8>(0));
    }

    int p = 8-binaryStr.size()%8;
    for (int i = 0;i < p;i++)
        binaryStr = binaryStr+"0";

    vector<bitset<8>> bstxt;
    for (int i = 0;i < binaryStr.size();i = i+8)
        bstxt.push_back(bitset<8>(binaryStr.substr(i,8)));

    ofstream output(filename+".huff"+ (pedding_2B ? "16" : "8"),ios::out | ios::binary | ios::app);

    for (int i = 0;i < binaryTree.size();i++) {
        output.write((char*)&binaryTree[i],sizeof(char));
    }

    for (int i = 0;i < bstxt.size();i++) {
        output.write((char*)&bstxt[i],sizeof(char));
    }
    output.close();
    cout << "finished\n";
    return 0;
}

int decode(){
    string filename;
    ifstream file;
    getline(cin, filename);
    file.open(filename, ios::binary);

    if (!file.is_open())
        return 1;
    string binary;
    char c;
    while (file.get(c)) {
        for (int i = 7; i >= 0; i--)
            binary += ((c >> i) & 1) == 1 ? "1" : "0";
    }

    int pedding = filename.substr(filename.find_last_of(".huff")+1,1) == "8" ? 8 : 16;

    int l =0;
    map<char, int> map;
    int till = pedding+8;
    for (int i = 0;pedding == 8 ? binary.substr(i, pedding+8) != "0000000000000000" : binary.substr(i, pedding+8) != "000000000000000000000000";i=i+pedding+8) {
        char cc = (char)getDezimal(binary.substr(i,8));
        int times = getDezimal(binary.substr(i+8, pedding));
        l += times;
        map[cc] = times;
        till = till+pedding+8;
    }

    string binarytxt = binary.substr(till,binary.size()-till-1);
    string resulttxt = "";

    generateTree(map);

    merge(false, map);

    string str = "";

    for (int i = 0;i < binarytxt.size();i++){
        str += binarytxt[i];

        if (resultrev.count(str) == 1) {
            resulttxt += resultrev[str];
            if (l == resulttxt.size())
                break;
            str = "";
        }
    }

    ofstream output;
    output.open(filename.substr(0,filename.find_last_of(".")));
    output << resulttxt;
    output.close();

    cout << "finished\n";
    return 0;
}

int main() {
    string en_de;
    cout << "type en for encode and de for decode\n";
    getline(cin, en_de);
    if (en_de == "en") {
        cout << "type in path of file\n";
        return encode();
    }
    else if (en_de == "de") {
        cout << "type in path of file\n";
        return decode();
    }
    return 1;
}
