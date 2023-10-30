#include <iostream>
#include"list.h"
// #include"node.cpp"
#include <stdexcept>
using namespace std;

List::List(){
    size=0;
    sentinel_head=new Node(true);
    sentinel_tail=new Node (true);
    sentinel_head->next=sentinel_tail;
    sentinel_tail->prev=sentinel_head;
}
void List::insert(int v){
    Node* temp = sentinel_tail->prev;
    Node* k =new Node (v, sentinel_tail, temp);
    temp->next=k;
    sentinel_tail->prev=k;

    size++;
}
//Not sure
int List::delete_tail(){
    Node *k=sentinel_tail->prev;
    int f= k->get_value();
    k->prev->next=sentinel_tail;
    sentinel_tail->prev=k->prev;
    delete k;
    size--;  
    return f; 
}

int List::get_size(){
    return size;
}
Node* List::get_head(){
    return sentinel_head;
}
List::~List(){
    Node* k=sentinel_head->next;
    for(int i=0; i<size;i++){
        sentinel_head->next=k->next;
        delete k;
        k=sentinel_head->next;
    }
    delete sentinel_head;
    delete sentinel_tail;
}


// // int main(){
// //     List l;
// //     l.insert(10);
// //     l.insert(1);
// //     l.insert(10);
// //     l.insert(1);
// //     l.insert(1);
// //     l.insert(10);
// //     l.insert(1);
// //     l.insert(1);
// //     l.insert(10);
// //     l.insert(10);
// //     l.insert(1);
// //     l.insert(10);
// //     Node* k= l.get_head();
// //     cout<<k->prev<<endl;
// //     while(k!=nullptr){
// //         cout<<k<<endl;
// //         k=k->next;
// //     }
// //     cout<<k<<endl;
// //     cout<<l.get_size()<<endl;
// //     cout<<l.get_head()->next->next->next->next->next->next->next->next->next->next->next->next->get_value()<<endl;
// //     cout<<l.delete_tail()<<endl;
// //     cout<<l.get_head()->next->next->next->next->next->next->next->next->next->next->next->get_value()<<endl;
// //     cout<<l.get_head()->next->next->next->next->next->next->next->next->next->next->next<<endl;
// //     cout<<l.get_head()->next->next->next->next->next->next->next->next->next->next->get_value()<<endl;
// //     // cout<<l.get_head()->prev<<endl;
// // }
