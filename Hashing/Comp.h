#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>
using namespace std;
class Comp : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    int Size=0;
    vector<int> mergesort(vector <int> f);
    vector <int> merge(vector <int> d,vector <int> k);
    vector<vector<int>> split(vector <int >k);
    // Other data members and functions specific to Your implementation
};

#endif // COMP_H
