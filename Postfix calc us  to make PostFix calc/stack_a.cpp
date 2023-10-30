#include<iostream>
#include <stdexcept>
#include"stack_a.h"
using namespace std;
Stack_A::Stack_A() {
    size = 0;
}
void Stack_A::push(int data){
    if (size<1024 && size>=0){
        stk[size]=data;
        size++;
    }
    else {
        throw std::runtime_error("Stack Full");
    }
}
int Stack_A::pop(){
    int temp{};
    if (size>0){
        size--;
        temp= stk[size];                    
    }
    else{
        throw std::runtime_error("Empty Stack");
    }
    return temp;
}
int Stack_A::get_element_from_top(int idx){
    if (size-1-idx>=0){
        return stk[size-1-idx];
    }
    else{
        throw std::runtime_error("Index out of range");        
    }        
}
int Stack_A::get_element_from_bottom(int idx){
    if (size-1-idx>=0 && idx>=0){
        return stk[idx];
    }
    else{
        throw std::runtime_error("Index out of range");
    }
}
void Stack_A::print_stack(bool top){
    if (top==false){
        for (int i=0; i<size; i++){
            cout<<stk[i]<<endl;
        }
    }
    else{
        for (int i=size-1; i>=0; i--){
            cout<<stk[i]<<endl;
        }
    }
}
int Stack_A::add(){
    if (size>=2){
        int d=pop();
        int f=pop();
        push(d+f);
        return d+f;   
    }
    else{
        throw std::runtime_error("Not enough arguments");
    }
}
int Stack_A::subtract(){
    if (size>=2){
        int d=pop();
        int f=pop();
        push(f-d);
        return f-d;   
    }
    else{
        throw std::runtime_error("Not enough arguments");
    
    } 
    
}
int Stack_A::multiply(){
    if(size>=2){
        int d=pop();
        int f=pop();
        push(d*f);
        return d*f;   
    }
    else{
        throw std::runtime_error("Not enough arguments");
    }     
    
}
int Stack_A::divide(){
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
int* Stack_A::get_stack(){
    return stk;
}
int Stack_A::get_size(){
    return size;
}
// int main(){
//     Stack_A k;
//     k.push(2);
//     k.push(4);
//     k.push(3);
//     k.push(2);
//     k.pop();
//     k.pop();
//     k.pop();
    
//     k.print_stack(0);
//     k.pop();
    
//     k.print_stack(1);
//     k.push(12);
//     k.print_stack(1);
//     k.subtract();
//     k.subtract();
//     k.subtract();
//     k.print_stack(1);
// }
