#ifndef IR_HPP
#define IR_HPP

#include <vector>

using namespace std;

class node {
public:
    int val;
    vector<node*> neighbors;
    
    node() {
        val = 0;
        neighbors = vector<node*>();
    }
    
    node(int _val) {
        val = _val;
        neighbors = vector<node*>();
    }
    
    node(int _val, vector<node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

#endif // IR_HPP
