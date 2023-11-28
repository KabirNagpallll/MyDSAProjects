// Do NOT add any other includes
#include "search.h"

SearchEngine::SearchEngine()
{
    // Implement your function here
}

SearchEngine::~SearchEngine()
{
    // Implement your function here
    
    dataString.clear();

}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    // Implement your function here

    dataString.push_back(sentence);
    // Node *temp = new Node(book_code, page, paragraph, sentence_no, -1);
    // dataNode.push_back(temp);
}

void match(string pattern, string sentence, vector<int> cont, int &matches)
{
    int j = pattern.size() - 1;
    int i = j;
    while (i < sentence.size())
    {
        // cout<<pattern<<endl;

        if (j == 0 && (pattern[j] == sentence[i] || pattern[j] == char(int(sentence[i] + 32))))
        {

            i = i + pattern.size();
            j = pattern.size() - 1;
            matches++;
            
        }
        
        else if (pattern[j] == sentence[i] || pattern[j] == char(int(sentence[i] + 32)))
        {
            i--;
            j--;
            // cout<<"i: "<<i<<" pattern char: "<< pattern[j]<<" sentence char: "<<sentence[i]<<" j: "<<j<<endl;
            
        }
        // cout<<i<<", "<<j<<endl;
        // if (i==39){
        //             break;
        //         }
        else
        {
            if (int(sentence[i]) >= 65 && int(sentence[i]) <= 90)
            {
                char s = char(int(sentence[i] + 32));
               if (cont[s] >j)
                {
                    int k = j;
                    while (pattern[k] != s && k >= 0)
                    {
                        k--;
                    }
                    i = i + pattern.size() - k - 1;
                    j = pattern.size() - 1;
                }
                else
                {
                    // cout<<cont[s]<<endl;
                    i = i + pattern.size() - cont[s] - 1;
                    j = pattern.size() - 1;
                    // cout<<i<<", "<<j<<endl; 
                }
            }
            else
            {
                // cout<<"i: "<<i<<" pattern char: "<< pattern[j]<<" sentence char: "<<sentence[i]<<" j: "<<j<<endl;
                // cout<<sentence<<endl;
                
                if (cont[sentence[i]] >j)
                {
                    int k = j;
                    while (pattern[k] != sentence[i] && k >= 0)
                    {
                        k--;
                    }
                    i = i + pattern.size() - k - 1;
                    j = pattern.size() - 1;
                }
                else
                {
                    // cout<<cont[sentence[i]]<<endl;
                    i = i + pattern.size() - cont[sentence[i]] - 1;
                    j = pattern.size() - 1;
                    // cout<<i<<", "<<j<<endl;
                }
                
            }
            
        }
        
    }
}
Node *SearchEngine::search(string pattern, int &n_matches)
{
    // Implement your function here
    string s = "";
    for (int i = 0; i < pattern.size(); i++)
    {
        if (int(pattern[i]) >= 65 && int(pattern[i]) <= 90)
        {
            s.push_back(char(int(pattern[i] + 32)));
        }
        else
            s.push_back(pattern[i]);
    }
    vector<int> container;
    help(s, container);
    for (long long  i = 0; i < dataString.size(); i++)
    {
        match(s, dataString[i], container, n_matches);
    }

    return nullptr;
}

