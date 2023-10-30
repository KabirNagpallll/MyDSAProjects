#include <iostream>
#include "node.h"
#include <stdexcept>
using namespace std;
 
// int Node::get_value(){
//     return value;
// }
// Doubt
Node::Node(bool sentinel){
    if (sentinel==true){
        is_sentinel=true;
        next=nullptr;
        prev=nullptr;
    }
}
int Node::get_value(){
    return value;
}
Node::Node (int v, Node* nxt, Node* prv){
    value=v;
    next=nxt;
    prev=prv;
    is_sentinel=false;
}
bool Node::is_sentinel_node(){
    return is_sentinel;
}

