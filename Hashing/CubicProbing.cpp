#include "CubicProbing.h"
// #include "BaseClass.h"
#include <iostream>
// #include <vector>;
using namespace std;
int p1=142857;
int CubicProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
        int result=0;
    int multiplier=1;
    for (int i = id.length() - 1; i >= id.length() - 7 && multiplier <= 1000000; --i) {
            result += (id[i]) * multiplier;
            multiplier *= 10;
    }

    return result%142867; // Placeholder return value
}

vector<vector<int>> CubicProbing::split(vector <int >k){
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
vector <int> CubicProbing::merge(vector <int> d,vector <int> k){
    vector <int> h;
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
vector<int> CubicProbing::mergesort(vector <int> f){
    
    if (f.size()==1){
        return f;
    }
    else{
        vector<vector<int>>k= split(f);
        return merge (mergesort(k[0]),mergesort(k[1]));
    }
}

// int Size=0;
vector <int> HashVal; 

bool g=true;
void CubicProbing::createAccount(std::string id, int count) {
    if (g==true){
        Account temp = Account{"",0};
        bankStorage1d.resize(p1, temp);
        g=false;
    }
    Account k;
    k.id=id;
    k.balance=count;
    int s=(hash(id))%p1;
    int c=1;

    while(bankStorage1d[s].id.size()!=0){
        s=(s+ c)%p1;
        c++;
    }
    bankStorage1d[s]=k;
    Size++;
    // Bal1.push_back(count);
    // IMPLEMENT YOUR CODE HERE
}

std::vector<int> CubicProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    vector <int> Sort;
    vector <int > Bal1;
    int f=0;
    for(int t=0; t<bankStorage1d.size(); t++){
        if(bankStorage1d[t].id.size()!=0){
            Bal1.push_back(bankStorage1d[t].balance);
        }
    }
    // for(int i=0;i<Bal1.size();i++){
    //     int j=i-1;
    //     int key=Bal1[i];
    //     while (j>=0 && Bal1[j]<key){
    //         Bal1[j+1]=Bal1[j];
    //         j--;
    //     }     
    //     Bal1[j+1]=key;
    // }
    Bal1=mergesort(Bal1);
    while (f<Bal1.size() && f<k){
        Sort.push_back(Bal1[f]);
        f++;
    }

    
    return Sort; // Placeholder return value
}
//GdBd
int CubicProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h=(hash(id))%p1;
    int k=0;
    while (k!=bankStorage1d.size()){
        if (bankStorage1d[h].id==id){
            return bankStorage1d[h].balance;
        }
        else{
            k++;
            h=(h+k)%p1;
        }
    }
    return -1; // Placeholder return value
}
//GdBd
void CubicProbing::addTransaction(std::string id, int count) {
    int h=(hash(id))%p1;
    int k=0;
    while (k!=bankStorage1d.size()){
        if (bankStorage1d[h].id==id){
                if (bankStorage1d[h].balance > -count)
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
            h=(h+k)%p1;
        }
    }
    if (bankStorage1d[h].id.size()==0){
        if (count>=0){
            createAccount(id, count);
        }
    }


    // return 0; 
    // IMPLEMENT YOUR CODE HERE
}

bool CubicProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h=(hash(id))%p1;
    int k=0;
    while (k!=bankStorage1d.size()){
        if (bankStorage1d[h].id==id){
            return true;
        }
        else{
            k++;
            h=(h+k)%p1;
        }
    }
    return false; // Placeholder return value
}

bool CubicProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if (doesExist(id)==true){
        int h=(hash(id))%p1;
        int k=0;
        while (k!=bankStorage1d.size()){
            if (bankStorage1d[h].id==id){
                bankStorage1d[h].id="";
                Size--;
                return true;
            }
            else{
                k++;
                h=(h+k)%p1;
            }
        }
        
    }
    return false; // Placeholder return value
}

int CubicProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return Size; // Placeholder return value
}

// int main(){
//     CubicProbing cube;

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


// }


// // int main(){
// //     CubicProbing k;
// //     k.createAccount("AAAA1234556", 1212);
// //     k.createAccount("AAAA1234256", 1212);
// //     k.createAccount("AAAA1434256", 1212);
// //     k.createAccount("AAAA1134256", 1212);
// //     k.createAccount("AAAA1237256", 1212);
// //     k.createAccount("AAAB1237256", 1212);
    
// // }
