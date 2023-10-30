#include "Chaining.h"
#include <iostream>
// #include <algorithm>
// #include <cassert>
using namespace std;

// vector<int> Bal4;
vector<vector<int>> Chaining::split(vector <int >k){
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
vector <int> Chaining::merge(vector <int> d,vector <int> k){
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
vector<int> Chaining::mergesort(vector <int> f){
    
    if (f.size()==1){
        return f;
    }
    else{
        vector<vector<int>>k= split(f);
        return merge (mergesort(k[0]),mergesort(k[1]));
    }
}
bool g4=true;

void Chaining::createAccount(std::string id, int count)
{
    // IMPLEMENT YOUR CODE HERE
    Account k;
    k.id = id;
    k.balance = count;
    int s = hash(id);
    if (g4==true){
        bankStorage2d.resize(150000); //GdBd
        g4=false;
    }
    bankStorage2d[s].push_back(k);
    // Bal4.push_back(count);
    Size++;
}

std::vector<int> Chaining::getTopK(int k)
{
    // IMPLEMENT YOUR CODE HERE
    vector <int> Sort;
    vector <int> Bal4;
    for (int i=0; i<bankStorage2d.size(); i++){
        for (int j=0; j<bankStorage2d[i].size(); j++){
            Bal4.push_back(bankStorage2d[i][j].balance);
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
    Bal4=mergesort(Bal4);
    while (f<Bal4.size() && f<k){
        Sort.push_back(Bal4[f]);
        f++;
    }

    
    return Sort;
    // Placeholder return value
}

int Chaining::getBalance(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int k = hash(id);
    for (int i = 0; i < bankStorage2d[k].size(); i++)
    {
        if (bankStorage2d[k][i].id == id)
        {
            return bankStorage2d[k][i].balance;
        }
    }
    return -1; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count)
{
    int k = hash(id);
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

bool Chaining::doesExist(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int k = hash(id);
    for (int i = 0; i < bankStorage2d[k].size(); i++)
    {
        if (bankStorage2d[k][i].id == id)
        {
            return true;
        }
    }
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    if (doesExist(id) == true)
    {
        int k = hash(id);
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
int Chaining::databaseSize()
{
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

int Chaining::hash(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int result=0;
    int multiplier=1;
    for (int i = id.length() - 1; i >= id.length() - 7 && multiplier <= 1000000; --i) {
            result += (id[i]) * multiplier;
            multiplier *= 10;
    }

    return result%142867;// Placeholder return value
}
// void testDatabase(BaseClass *db)
// {
//     db->createAccount("Alice", 1000);
//     db->createAccount("Bob", 1500);
//     db->createAccount("Charlie", 2000);

//     assert(db->getBalance("Alice") == 1000);
//     assert(db->getBalance("Bob") == 1500);
//     assert(db->getBalance("Charlie") == 2000);

//     db->addTransaction("Alice", -200);
//     db->addTransaction("Bob", 300);
//     db->addTransaction("Charlie", -400);

//     assert(db->getBalance("Alice") == 800);
//     assert(db->getBalance("Bob") == 1800);
//     assert(db->getBalance("Charlie") == 1600);

//     std::vector<int> topBalances = db->getTopK(2);
//     assert(topBalances.size() == 2);
//     assert(topBalances[0] == 1800);
//     assert(topBalances[1] == 1600);

//     assert(db->databaseSize() == 3);

//     assert(db->doesExist("Alice"));
//     assert(!db->doesExist("Eve"));
// }
// int main()
// {

//     // LinearProbing linearProbingDB;
//     // QuadraticProbing quadraticProbingDB;
//     // CubicProbing cubicProbingDB;
//     // Comp compDB;



//     std::cout << "Testing Chaining:" << std::endl;
//     Chaining chainingDB;
//     testDatabase(&chainingDB);

//     // std::cout << "\nTesting Linear Probing:" << std::endl;
//     // testDatabase(&linearProbingDB);

//     // std::cout << "\nTesting Quadratic Probing:" << std::endl;
//     // testDatabase(&quadraticProbingDB);

//     // std::cout << "\nTesting Cubic Probing:" << std::endl;
//     // testDatabase(&cubicProbingDB);

//     // std::cout << "\nTesting Comp:" << std::endl;
//     // testDatabase(&compDB);
//     return 0;
// }
// int main(){
//     Chaining cube;

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
