#ifndef compression_h
#define compression_h

#include <string>
#include <unordered_map>
using namespace std;

struct node 
{
    char ch;
    int freq;
    node* left;
    node* right;
    node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

class compression 
{

private:
    static void readdata(const string& filepath, string& data);
    static void buildfreq(const string& data, unordered_map<char, int>& freq);
    static node* buildtree(const unordered_map<char, int>& freq);
};

#endif
