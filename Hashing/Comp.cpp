#include "Comp.h"
using namespace std;
bool g4=true;
vector<vector<int>> Comp::split(vector <int >k){
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
vector <int> Comp::merge(vector <int> d,vector <int> k){
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
vector<int> Comp::mergesort(vector <int> f){
    
    if (f.size()==1){
        return f;
    }
    else{
        vector<vector<int>>k= split(f);
        return merge (mergesort(k[0]),mergesort(k[1]));
    }
}
int p5=100019;
void Comp::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    Account k;
    k.id = id;
    k.balance = count;
    int s = (hash(id))%p5 ;
    if (g4==true){
        bankStorage2d.resize(p5); //GdBd
        g4=false;
    }
    bankStorage2d[s].push_back(k);
    // Bal4.push_back(count);
    Size++;
}

std::vector<int> Comp::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    vector <int> Sort;
    vector <int> Bal5;
    for (int i=0; i<bankStorage2d.size(); i++){
        for (int j=0; j<bankStorage2d[i].size(); j++){
            Bal5.push_back(bankStorage2d[i][j].balance);
        }
    }
    int f=0;
    
    // for(int i=0;i<Bal4.size();i++){
    //     int j=i-1;
    //     int key=Bal4[i];
    //     while (j>=0 && Bal4[j]<key){
    //         Bal4[j+1]=Bal4[j];
    //         j--;
    //     }     
    //     Bal4[j+1]=key;
    // }
    Bal5=mergesort(Bal5);
    while (f<Bal5.size() && f<k){
        Sort.push_back(Bal5[f]);
        f++;
    }

    
    return Sort; // Placeholder return value
}

int Comp::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int k = (hash(id))%p5;
    for (int i = 0; i < bankStorage2d[k].size(); i++)
    {
        if (bankStorage2d[k][i].id == id)
        {
            return bankStorage2d[k][i].balance;
        }
    }
    return -1; // Placeholder return value
}

void Comp::addTransaction(std::string id, int count) {
    int k = (hash(id))%p5;
    int b=0;
    for (int i = 0; i < bankStorage2d[k].size(); i++)
    {
        if (bankStorage2d[k][i].id == id && bankStorage2d[k][i].balance > -count)
        {
            bankStorage2d[k][i].balance = bankStorage2d[k][i].balance + count;
            b=1;
            break;
        }
        else if (bankStorage2d[k][i].id == id && bankStorage2d[k][i].balance < -count)
        {
            bankStorage2d[k][i].balance = 0;
            b=1;
            break;
        }
    }
    if (b==0 && count>=0){
        createAccount(id,count);
    }
    // IMPLEMENT YOUR CODE HERE
}

bool Comp::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int k = (hash(id))%p5;
    for (int i = 0; i < bankStorage2d[k].size(); i++)
    {
        if (bankStorage2d[k][i].id == id)
        {
            return true;
        }
    }
    
    return false; // Placeholder return value
}

bool Comp::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if (doesExist(id) == true)
    {
        int k = (hash(id))%p5;
        for (int i = 0; i < bankStorage2d[k].size(); i++)
        {
            if (bankStorage2d[k][i].id == id)
            {
                bankStorage2d[k].erase(bankStorage2d[k].begin() + i);
                Size--;
                return true;
            }
        }
    }
    return false; // Placeholder return value
}
int Comp::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    int c = 0;
    // vector <int> h;
    for (int j = 0; j < bankStorage2d.size(); j++)
    {
        for (int i = 0; i < bankStorage2d[j].size(); i++)
        {
            c++;
        }
    }
    return c; // Placeholder return value
}

int Comp::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    // int p=31;
    // long long int intNum= 0;
    // int power=1;
    // int t=1000000009;
    // for (int i=0; i<id.size()-4; i++){
    //     intNum=intNum + (id[i])*power;
    //     power= power*p;
    // }
    // intNum=intNum%t;
    // // cout<<intNum<<endl;
    // int result=0;
    // int multiplier=1;
    // for (int i = id.length() - 1; i >= id.length() - 7 && multiplier <= 1000000; --i) {
    //         result += (id[i]) * multiplier;
    //         multiplier *= 10;
    // }
    // long int x= intNum%99991;
    // long int u=x%142867;
        // cout<<u<<endl;
        // cout<<x%100000<<endl;
        // cout<<x<<endl;
    // cout<<x<<endl;
    // return x;
    long int hash_value = 0;

    
    for (char c : id) {
        hash_value = (hash_value * 53 + c) % 99991;
    }

    return hash_value;

     // Placeholder return value
}


// Feel free to add any other helper functions you need
// Good Luck!