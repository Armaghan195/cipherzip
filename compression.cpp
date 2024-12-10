#include "compression.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;


void compression::readdata(const string& filepath, string& data) 
{
    ifstream in(filepath, ios::binary);
    if (!in.is_open()) return;
    data.assign((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();
}

void compression::buildfreq(const string& data, unordered_map<char, int>& freq) 
{
    for (char c : data) freq[c]++;
}

node* compression::buildtree(const unordered_map<char, int>& freq)
{
    priority_queue<node*, vector<node*>, cmp> pq;
    for (auto& p : freq) 
    {
        pq.push(new node(p.first, p.second));
    }
    if (pq.empty()) return nullptr;
    while (pq.size() > 1) 
    {
        node* l = pq.top(); pq.pop();
        node* r = pq.top(); pq.pop();
        node* nd = new node('\0', l->freq + r->freq);
        nd->left = l;
        nd->right = r;
        pq.push(nd);
    }
    return pq.top();
}
