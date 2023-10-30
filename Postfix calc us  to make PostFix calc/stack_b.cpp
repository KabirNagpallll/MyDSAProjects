#include <iostream>
#include <stdexcept>
#include "stack_b.h"
using namespace std;
Stack_B::Stack_B()
{
    capacity = 1024;
    size = 0;
    stk = new int[capacity];
}
void Stack_B::push(int data)
{
    if (size < capacity && size >= 0)
    {
        stk[size] = data;
        size++;
    }
    else if (size >= capacity)
    {
        int *temp;
        temp = new (nothrow) int[2 * capacity];
        if (temp == NULL)
        {
            throw runtime_error("Out of Memory");
            return;
        }
        for (int i = 0; i < size; i++)
        {
            temp[i] = stk[i];
        }
        capacity *= 2;
        temp[size] = data;
        size++;
        delete[] stk;
        stk = temp;
    }
    return;
}
//ERROR
int Stack_B::pop(){
//     if (size>0){
//         if(size>(capacity/4)+1 ){

//         }
//     }
//     else{
//         throw runtime_error("Empty Stack");
//     }
// }
// {
    int temp;
    if (size > 0)
    {
        if (size > (capacity / 4)+1 || capacity==1024)
        {
            temp = stk[size-1];
            size--;
        }
        // Error - assgn new to stk
        else if (size <= (capacity / 4)+1 && capacity > 1024)
        {
            capacity = capacity / 2;
            int *k = new int[capacity];
            for (int i = 0; i < size - 1; i++)
            {
                k[i] = stk[i];
            }
            temp = stk[size - 1];
            delete[] stk;
            stk = k;
            size--;
        }
        
    }
    else
        {
            throw runtime_error("Empty Stack");
        }
    return temp;
}



int Stack_B::get_element_from_top(int idx)
{
    if (size - 1 >= idx)
    {
        return stk[size - 1 - idx];
    }
    else
    {
        throw std::runtime_error("Index out of range");
    }
}
int Stack_B::get_element_from_bottom(int idx)
{
    if (size - 1 - idx >= 0)
    {
        return stk[idx];
    }
    else
    {
        throw std::runtime_error("Index out of range");
    }
}
void Stack_B::print_stack(bool top_or_bottom)
{
    if (top_or_bottom == 0)
    {
        for (int i = 0; i < size; i++)
        {
            cout << stk[i] << endl;
        }
    }
    else
    {
        for (int i = size - 1; i >= 0; i--)
        {
            cout << stk[i] << endl;
        }
    }
}
int Stack_B::add()
{
    int d;
    int f;
    if (size >= 2)
    {
        d = pop();
        f = pop();
        push(d + f);
    }
    else
    {
        throw std::runtime_error("Index out of range");
    }
    return d + f;
}
int Stack_B::subtract()
{
    if (size >= 2)
    {
        int d = pop();
        int f = pop();
        push(f - d);
        return f - d;
    }
    else
    {
        throw std::runtime_error("Index out of range");
    }
}
int Stack_B::multiply()
{
    if (size >= 2)
    {
        int d = pop();
        int f = pop();
        push(d * f);
        return d * f;
    }
    else
    {
        throw std::runtime_error("Index out of range");
    }
}
int Stack_B::divide()
{
    if (get_size() < 2)
    {
        throw std::runtime_error("Not Enough Arguments");
    }
    else
    {
        int d = pop();
        int f = pop();
        if (d == 0)
        {
            push(f);
            push(d);
            throw std::runtime_error("Divide by Zero Error");
        }
        else
        {
            if (d * f < 0)
            {
                if (f % d != 0)
                {
                    push(f / d - 1);
                    return f / d - 1;
                }
                else
                {
                    push(f / d);
                    return f / d;
                }
            }
            else
            {
                push(f / d);
                return f / d;
            }
        }
    }
}
int *Stack_B::get_stack()
{
    return stk;
}
int Stack_B::get_size()
{
    return size;
}
Stack_B::~Stack_B()
{
    delete[] stk;
}
// int main(){
//     Stack_B s;
//     s.push(24);
//     s.print_stack(1);
//     s.push(29);
//     s.print_stack(1);
//     s.push(28);
//     s.print_stack(1);
//     s.push(90);
//     s.print_stack(1);
//     s.push(43);
//     s.print_stack(1);
//     // s.divide();
//     s.print_stack(1);
//     cout<<s.get_size()<<endl;
//     s.pop();
//     s.print_stack(1);
//     s.pop();
//     s.print_stack(1);
//     s.pop();
//     s.print_stack(1);
//     s.pop();
//     s.print_stack(1);
//     s.pop();
//     s.print_stack(1);
//     return 0;
// }