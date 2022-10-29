#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Quicksorter.h"
#include "Node.h"
#include "CLI.h"

std::map<char, std::string> result;
std::map<std::string, char> resultrev;
std::map<std::string, int> binary;
std::vector<int> times;

void processNode(std::string value,Node* n){
    if (n->isSingleNode()){
        binary[value] = n->getValue0();
        return;
    }
    processNode(value+"1",n->getNode1());
    processNode(value+"0",n->getNode0());
}

std::string getbinary(int n, bool b){
    std::string r;
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

int getDezimal(std::string a){
    int r = 0;
    for (int i = a.size()-1;i >= 0;i--){
        r = r + (a[i] == '1' ? powerof(2, (a.size()-1)-i) : 0);
    }
    return r;
}

void generateTree(std::map<char,int> map){
    Quicksorter qs;
    std::vector<Node*> nodes;

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

void merge(bool a,std::map<char, int> map){
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
    std::string filename;
    std::ifstream file;
    getline(std::cin, filename);
    file.open(filename);

    if (!file.is_open())
        return 1;

    std::vector<char> chars;
    std::map<char, int> map;
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

    std::string binaryStr =  "";
    while (file.good()) {
        file.get(ch);
        if (file)
            binaryStr += result[ch];
    }

    bool pedding_2B = false;
    std::string binaryStrTree = "";
    if (times[times.size()-1]>255)
        pedding_2B = true;

    std::vector<std::bitset<8>> binaryTree;
    for (auto const &x : map){
        binaryTree.push_back(std::bitset<8>((int)x.first));
        if (pedding_2B) {
            std::string tmp = getbinary(x.second, pedding_2B);
            binaryTree.push_back(std::bitset<8>(tmp.substr(0, 8)));
            binaryTree.push_back(std::bitset<8>(tmp.substr(8, 15)));
        }
        else
            binaryTree.push_back(std::bitset<8>(getbinary(x.second,pedding_2B)));
    }
    binaryTree.push_back(std::bitset<8>(0));
    if (!pedding_2B)
        binaryTree.push_back(std::bitset<8>(0));
    else {
        binaryTree.push_back(std::bitset<8>(0));
        binaryTree.push_back(std::bitset<8>(0));
    }

    int p = 8-binaryStr.size()%8;
    for (int i = 0;i < p;i++)
        binaryStr = binaryStr+"0";

    std::vector<std::bitset<8>> bstxt;
    for (int i = 0;i < binaryStr.size();i = i+8)
        bstxt.push_back(std::bitset<8>(binaryStr.substr(i,8)));

    std::ofstream output(filename+".huff"+ (pedding_2B ? "16" : "8"),std::ios::out | std::ios::binary | std::ios::app);

    for (int i = 0;i < binaryTree.size();i++) {
        output.write((char*)&binaryTree[i],sizeof(char));
    }

    for (int i = 0;i < bstxt.size();i++) {
        output.write((char*)&bstxt[i],sizeof(char));
    }
    output.close();
    std::cout << "finished\n";
    return 0;
}

int decode(){
    std::string filename;
    std::ifstream file;
    getline(std::cin, filename);
    file.open(filename, std::ios::binary);

    if (!file.is_open())
        return 1;
    std::string binary;
    char c;
    while (file.get(c)) {
        for (int i = 7; i >= 0; i--)
            binary += ((c >> i) & 1) == 1 ? "1" : "0";
    }

    int pedding = filename.substr(filename.find_last_of(".huff")+1,1) == "8" ? 8 : 16;

    int l =0;
    std::map<char, int> map;
    int till = pedding+8;
    for (int i = 0;pedding == 8 ? binary.substr(i, pedding+8) != "0000000000000000" : binary.substr(i, pedding+8) != "000000000000000000000000";i=i+pedding+8) {
        char cc = (char)getDezimal(binary.substr(i,8));
        int times = getDezimal(binary.substr(i+8, pedding));
        l += times;
        map[cc] = times;
        till = till+pedding+8;
    }

    std::string binarytxt = binary.substr(till,binary.size()-till-1);
    std::string resulttxt = "";

    generateTree(map);

    merge(false, map);

    std::string str = "";

    for (int i = 0;i < binarytxt.size();i++){
        str += binarytxt[i];

        if (resultrev.count(str) == 1) {
            resulttxt += resultrev[str];
            if (l == resulttxt.size())
                break;
            str = "";
        }
    }

    std::ofstream output;
    output.open(filename.substr(0,filename.find_last_of(".")));
    output << resulttxt;
    output.close();

    std::cout << "finished\n";
    return 0;
}


std::string help = "Options\n"
                   "  --help, -h        = Print help.\n"
                   "  --out, -o <file>  = Specify output file.\n"
                   "  --in, -i  <file>  = Specify input file.\n"
                   "  --tree, -t <file> = Specify the huffman tree file.\n"
                   "  --encode, -en     = Encode the input file and write the compressed file to the output file.\n"
                   "  --decode, -de     = Decode the input file and write the decompressed file to the output file.\n";

//TODO: move stuff away from main
//TODO: remove pointer and use smart pointer instead
//TODO: use the commandline arguments
//TODO: set up git actions
int main(int argc, char *argv[]) {
    CLI cli(argc, argv);

    if (cli.args->count(HELP)) {
        std::cout << help;
    } else if (cli.args->count(ERROR)) {
        std::cout << "Huffman Error: Unknown argument '" << (*cli.args)[ERROR] << "'" << std::endl;
        std::cout << "Huffman Error: Run 'huffman --help' for all supported options." << std::endl;
    } else if (cli.args->count(ERRORFILE)) {
        std::cout << "Huffman Error: no such file or directory: '" << (*cli.args)[ERRORFILE] << "'" << std::endl;
        std::cout << "Huffman Error: Run 'huffman --help' for all supported options." << std::endl;
    }

    return 0;
}
