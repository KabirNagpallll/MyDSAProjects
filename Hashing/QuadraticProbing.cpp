#include "QuadraticProbing.h"
#include <iostream>
// #include <vector>;
using namespace std;
vector <int> HashVal;
// vector <int> HashVal; 
// vector <int > Bal3;
bool g3=true;
int p3=262144;
vector<vector<int>> QuadraticProbing::split(vector <int >k){
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
vector <int> QuadraticProbing::merge(vector <int> d,vector <int> k){
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
vector<int> QuadraticProbing::mergesort(vector <int> f){
    
    if (f.size()==1){
        return f;
    }
    else{
        vector<vector<int>>k= split(f);
        return merge (mergesort(k[0]),mergesort(k[1]));
    }
}

void QuadraticProbing::createAccount(std::string id, int count) {
    if (g3==true){
        Account temp = Account{"",0};
        bankStorage1d.resize(p3, temp);
        g3=false;
    }
    Account k;
    k.id=id;
    k.balance=count;
    int s=(hash(id))%p3;
    int c=1;

    while(bankStorage1d[s].id.size()!=0){
        s=(s+ (c*(c+1)/2))%p3;
        c++;
    }
    bankStorage1d[s]=k;
    Size++;
    // Bal3.push_back(count);
    // IMPLEMENT YOUR CODE HERE
}

std::vector<int> QuadraticProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    vector <int> Sort;
    int f=0;
    vector <int> Bal3;
    // int f=0;
    for(int t=0; t<bankStorage1d.size(); t++){
        if(bankStorage1d[t].id.size()!=0){
            Bal3.push_back(bankStorage1d[t].balance);
        }
    }
    
    for(int i=0;i<Bal3.size();i++){
        int j=i-1;
        int key=Bal3[i];
        while (j>=0 && Bal3[j]<key){
            Bal3[j+1]=Bal3[j];
            j--;
        }     
        Bal3[j+1]=key;
    }
    while (f<Bal3.size() && f<k){
        Sort.push_back(Bal3[f]);
        f++;
    }
    return std::vector<int>(Sort);// Placeholder return value
}

int QuadraticProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h=(hash(id))%p3;
    int k=0;
    while (k!=bankStorage1d.size()){
        if (bankStorage1d[h].id==id){
            return bankStorage1d[h].balance;
        }
        else{
            k++;
            h=(h+k)%p3;
        }
    }
    return -1; // Placeholder return value
}

void QuadraticProbing::addTransaction(std::string id, int count) {
    int h=(hash(id))%p3;
    int k=0;
    while (k!=bankStorage1d.size()){
        if (bankStorage1d[h].id==id){
            if (bankStorage1d[h].balance > -count){
                bankStorage1d[h].balance = bankStorage1d[h].balance + count;
            }
            else if (bankStorage1d[h].balance < -count){
                bankStorage1d[h].balance = 0;
            }
            break;
        }
        else{
            k++;
            h=(h+k)%p3;
        }
    }
    if (bankStorage1d[h].id.size()==0){
        if (count>=0){
            createAccount(id, count);
        }
    }
    // IMPLEMENT YOUR CODE HERE
}

bool QuadraticProbing::doesExist(std::string id) {
    int h=(hash(id))%p3;
    int k=0;
    while (k!=bankStorage1d.size()){
        if (bankStorage1d[h].id==id){
            return true;
        }
        else{
            k++;
            h=(h+k)%p3;
        }
    }
    return false; 
    // IMPLEMENT YOUR CODE HERE // Placeholder return value
}

bool QuadraticProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if (doesExist(id)==true){
        int h=(hash(id))%p3;
        int k=0;
        while (k!=bankStorage1d.size()){
            if (bankStorage1d[h].id==id){
                bankStorage1d[h].id="";
                Size--;
                return true;
            }
            else{
                k++;
                h=(h+k)%p3;
            }
        }
        
    }
    return false;
     // Placeholder return value
}
int QuadraticProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return Size; // Placeholder return value
}

int QuadraticProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int result=0;
    int multiplier=1;
    for (int i = id.length() - 1; i >= id.length() - 7 && multiplier <= 1000000; --i) {
            result += (id[i]) * multiplier;
            multiplier *= 10;
    }

    return result%131072; // Placeholder return value
}
// int main(){
//     QuadraticProbing cube;

//     cube.createAccount("CDAD7786825_7990768648", 648);
//     cube.createAccount("DCDA7547234_9919615552", 552);
//     cube.createAccount("AACB1850545_7974534788", 788);
//     std::cout <<cube.databaseSize() << std::endl;
//     cube.createAccount ("CDBD5250777_1124276711", 711);
//     cube.createAccount ("ABCB8377155_0656808575", 575);
//     std::vector <int> vec = cube.getTopK(1);
//     std::cout << vec[0] << std::endl;
//     cube.createAccount( "CDDC3792028_3313680038", 38);
//     cube.createAccount ("CBBA9574444_7470182321", 321);
//     cube.createAccount ("DBCC4334636_8057544188", 188);
//     vec=cube.getTopK(3);
//     std::cout<<vec[0]<<std::endl;
//     std::cout <<vec[1] << std::endl;
//     std::cout << vec[2] << std::endl;
//     cube.createAccount ("BABD5741078_5109455304", 304);
//     cube.createAccount ("BCBA7529510_0817878868", 868);
//     std::cout << cube.databaseSize() << std::endl;
//     vec = cube.getTopK(1);
//     std::cout << vec[0] << std::endl;
//     cube.addTransaction ("BCBA7529510_0817878868", -860);
//     std:: cout << cube.getBalance("BCBA7529510_0817878868") << std::endl;
//     vec = cube.getTopK(1);
//     std:: cout << vec[0] << std::endl;
//     cube.addTransaction("DCDA7547234_9919615552", 592);
//     vec = cube.getTopK(5);
//     for(int i = 0;i<vec.size();i++){
//         std::cout << vec[i] << std::endl;
//     }
//     cube.deleteAccount ("DCDA7547234_9919615552");
//     std::cout << cube.doesExist("DCDA7547234_9919615552") << std::endl;
//     vec = cube.getTopK(4);
//     for(int i = 0;i<vec.size();i++){
//         std::cout << vec[i] << std::endl;
//     }
//     std::cout << cube.databaseSize() <<std::endl;
//     cout<<cube.getBalance("BABD8741078_5109455304")<<endl;

// }
