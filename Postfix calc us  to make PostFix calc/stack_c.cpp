#include <iostream>
#include <stdexcept>
#include "stack_c.h"
// #include"list.cpp"
// #include"list.h"
// #include"node.cpp"
using namespace std;

Stack_C::Stack_C(){
    stk= new List();
}


void Stack_C::push(int data){
    if (stk!=nullptr){
        stk->insert(data);
    }
    else{
        throw std::runtime_error("Out of Memory");
    }
}

int Stack_C::pop(){
    if (stk->get_size()>0){
        int k= stk->delete_tail();
        return k;
    }
    else{
        throw std::runtime_error("Empty Stack");
    }
}
int Stack_C::get_element_from_top(int idx){
    int size=stk->get_size();
    if (size-1>=idx && idx>=0 ){
        Node* k=stk->get_head();
        for (int i=0; i<=size-1-idx; i++){
            k=k->next;
        }
        return k->get_value();
    }
    else{
        throw std::runtime_error("Index out of range"); 
    }
}
int Stack_C::get_element_from_bottom(int idx){
    int size=stk->get_size();
    if(size-1>=idx && idx>=0){
        Node* k=stk->get_head();
        for (int i=0; i<=idx; i++){
            k=k->next;
        }
        return k->get_value();
    }
    else{
        throw std::runtime_error("Index out of range");
    }
}
void Stack_C::print_stack(bool top_or_bottom){
    if (top_or_bottom==true){
        Node* k=stk->get_head();
        // int size=stk->get_size();
        while(k->is_sentinel_node()!=true){
            k=k->next;
        }
        k=k->prev;
        while(k->is_sentinel_node()!=true){
            cout<<k->get_value()<<endl;
            k=k->prev;
        }
    }
    else{
        Node* k=stk->get_head();
        // int size=stk->get_size();
        // int h{};
        while(k->is_sentinel_node()!=true){
            cout<<k->get_value()<<endl;
            k=k->next;
        }
    }
}
int Stack_C::add(){
    if (stk->get_size()>=2){
        int d=pop();
        int f=pop();    
        push(d+f);
        return d+f;
    }
    else {
        throw std::runtime_error("Not enough arguments");
    }
}
int Stack_C::subtract(){
    if (stk->get_size()>=2){
        int d=pop();
        int f=pop();    
        push(f-d);
        return f-d;
    }
    else {
        throw std::runtime_error("Not enough arguments");
    }
}
int Stack_C::multiply(){
    if (stk->get_size()>=2){
        int d=pop();
        int f=pop();    
        push(d*f);
        return d*f;
    }
    else {
        throw std::runtime_error("Not enough arguments");
    }
}
int Stack_C::divide(){
    if(get_size()<2){
        throw std::runtime_error("Not Enough Arguments");
    }
    else{
        int d=pop();
        int f=pop();
        if(d==0){
            push(f);
            push(d);
            throw std::runtime_error("Divide by Zero Error");
        }
        else{
            // if(top2%top1!=0){
            //     if(top2>0 && top1<0 ){
            //         push(top2/top1-1);
            //         return top2/top1-1;
            //     }
            //     else if(top2<0 && top1>0 ){
            //         push(top2/top1-1);
            //         return top2/top1-1;
            //     }
            // }
            // else{
            //     push()
            // }
            if(f*d<0){
                if(f%d!=0){
                    push(f/d-1);
                    return f/d-1;
                }
                else{
                    push(f/d);
                    return f/d;
                }
            }
            else{
                push(f/d);
                return f/d;
            }
        }
    }
}
List* Stack_C::get_stack(){
    return stk;
}
int Stack_C::get_size(){
    return stk->get_size();
}
Stack_C::~Stack_C(){
    delete[] stk;
}
// int main(){
//     Stack_C a;
//     a.push(1);
//     a.push(3);
//     a.push(2);
//     a.push(5);
//     a.push(5);
//     a.push(5);
//     a.push(5);
//     a.push(5);
//     a.push(5);
//     a.push(5);
//     a.push(5);
//     a.push(5);
//     a.push(5);

//     a.print_stack(0);
//     // cout<<a.pop()<<endl;
//     a.pop();
//     a.print_stack(1);
//     a.add();
//     a.print_stack(1);
//     // // std
//     // std::cout<<a.get_stack()->get_head()->next->next->get_value()<<endl;
//     Node*k=a.get_stack()->get_head();
//     while (k->is_sentinel_node()!=1){
//         cout<<k<<endl;
//         k=k->next;
//     } 
//     // a.add();
//     cout<<"HI"<<endl;
//     k=a.get_stack()->get_head();
//     while (k->is_sentinel_node()!=1){
//         cout<<k->get_value()<<endl;
//         k=k->next;
//     }   
//     cout<<k->prev->get_value()<<endl;
//     return 0;
// }