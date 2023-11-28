
// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class SearchEngine {
private:
    // You can add attributes/helper functions here
    void help(string pattern, vector<int> &container){
        
        for (int i = 0; i<200; i++){
            container.push_back(-1);
        }
        for (int j = 0; j<pattern.size();j++){
            container[pattern[j]] = j;
        }
    }
    
    
    


public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */

    vector<string> dataString;
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
};