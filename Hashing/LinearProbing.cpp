#include "LinearProbing.h"
#include <iostream>
// #include <vector>;
using namespace std;
// int s=0;
// vector <int> HashVal;
// vector <int> HashVal; 
// vector <int > Bal2;
bool g2=true;
int p2=142857;
vector<vector<int>> LinearProbing::split(vector <int >k){
    vector <int> n;
    vector <int> g;
    vector<vector<int>> d;
    for (int i=0; i<k.size()/2; i++){
        n.push_back(k[i]);
    }
    for (int i=k.size()/2; i<k.size(); i++){
        g.push_back(k[i]);
    }
    d.push_back(n);
    d.push_back(g);
    return d;
}
vector <int> LinearProbing::merge(vector <int> d,vector <int> k){
    vector <int> h;
    
        // if (d.size()>k.size()){
        //     for(int i=0; i<k.size();i++){
        //         if (d[i]<k[i]){
        //             h.push_back(d[i]);
        //             h.push_back(k[i]);
        //         }
        //         else {
        //             h.push_back(k[i]);
        //             h.push_back(d[i]);
        //         }

        //     }
        //     h.push_back(d[d.size()-1]);
        // }
        // else{
        //     for(int i=0; i<k.size();i++){
        //         if (d[i]<k[i]){
        //             h.push_back(d[i]);
        //             h.push_back(k[i]);
        //         }
        //         else {
        //             h.push_back(k[i]);
        //             h.push_back(d[i]);
        //         }

        //     }
        //     // h.push_back(d[d.size()-1]);
        // }
        int i=0;
        int j=0;
        while (i<=d.size()-1 && j<=k.size()-1){
            if (d[i]>k[j]){
                h.push_back(d[i]);
                i++;
            }
            else {
                h.push_back(k[j]);
                j++;
            }
        }
        if (i==d.size()){
            for (;j<=k.size()-1;j++){
                h.push_back(k[j]);
            }
        }
        else if (j==k.size()){
            for (;i<=d.size()-1;i++){
                h.push_back(d[i]);
            }
        }
    return h;
}
vector<int> LinearProbing::mergesort(vector <int> f){
    
    if (f.size()==1){
        return f;
    }
    else{
        vector<vector<int>>k= split(f);
        return merge (mergesort(k[0]),mergesort(k[1]));
    }
}
void LinearProbing::createAccount(std::string id, int count) {
    if (g2==true){
        Account temp = Account{"",0};
        bankStorage1d.resize(p2, temp);
        g2=false;
    }
    Account k;
    k.id=id;
    k.balance=count;
    int s=(hash(id))%p2;
    int c=1;

    while(bankStorage1d[s].id.size()!=0){
        s=(s+ (c))%p2;
        c++;
    }
    bankStorage1d[s]=k;
    Size++;
    // Bal2.push_back(count);
    // EMENT YOUR CODE HERE
    // IMPLEMENT YOUR CODE HERE
}

std::vector<int> LinearProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    vector <int> Sort;
    int f=0;
    vector <int > Bal2;
    // int f=0;
    for(int t=0; t<bankStorage1d.size(); t++){
        if(bankStorage1d[t].id.size()!=0){
            Bal2.push_back(bankStorage1d[t].balance);
        }
    }
    for(int i=0;i<Bal2.size();i++){
        int j=i-1;
        int key=Bal2[i];
        while (j>=0 && Bal2[j]<key){
            Bal2[j+1]=Bal2[j];
            j--;
        }     
        Bal2[j+1]=key;
    }
    while (f<Bal2.size() && f<k){
        Sort.push_back(Bal2[f]);
        f++;
    }
    return std::vector<int>(Sort);// Placeholder return value
}

int LinearProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h=(hash(id))%p2;
    int k=0;
    while (k!=bankStorage1d.size()){
        if (bankStorage1d[h].id==id){
            return bankStorage1d[h].balance;
        }
        else{
            k++;
            h=(h+(k))%p2;
        }
    }
    return -1;  // Placeholder return value
}

void LinearProbing::addTransaction(std::string id, int count) {
    int h=(hash(id))%p2;
    int k=0;
    while (k!=bankStorage1d.size()){
        if (bankStorage1d[h].id==id){
                if ( bankStorage1d[h].balance > -count)
            {
                bankStorage1d[h].balance = bankStorage1d[h].balance + count;
            }
            else if (bankStorage1d[h].balance < -count)
            {
                bankStorage1d[h].balance = 0;
            }
            break;
        }
        else{
            k++;
            h=(h+(k))%p2;
        }
    }
    if (bankStorage1d[h].id.size()==0){
        if (count>=0){
            createAccount(id, count);
        }
    }

    // IMPLEMENT YOUR CODE HERE
}

bool LinearProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h=(hash(id))%p2;
    int k=0;
    while (k!=bankStorage1d.size()){
        if (bankStorage1d[h].id==id){
            return true;
        }
        else{
            k++;
            h=(h+(k))%p2;
        }
    }
    return false;  // Placeholder return value
}

bool LinearProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if (doesExist(id)==true){
        int h=(hash(id))%p2;
        int k=0;
        while (k!=bankStorage1d.size()){
            if (bankStorage1d[h].id==id){
                bankStorage1d[h].id="";
                Size--;
                return true;
            }
            else{
                k++;
                h=(h+(k))%p2;
            }
        }
        
    }
    return false; // Placeholder return value
}
int LinearProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return Size; // Placeholder return value
}

int LinearProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
        int result=0;
    int multiplier=1;
    for (int i = id.length() - 1; i >= id.length() - 7 && multiplier <= 1000000; --i) {
            result += (id[i]) * multiplier;
            multiplier *= 10;
    }

    return result%142867; // Placeholder return value
}

