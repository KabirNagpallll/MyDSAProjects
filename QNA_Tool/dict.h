

// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Dict
{
private:
    // vector<string> dataString;
    // for (int i =0; i<45;i++) dataString.push_back({});
    class Trienode
    {
    public:
        vector<Trienode *> arr;
        long long eofw;
        string val;
        long long id;
        
        // vector<vector<vector<double>>> para;//it will be just an empty vector just for size
        Trienode()
        {
            for (int i = 0; i < 200; i++)
            {
                arr.push_back(nullptr);
            }
            eofw = 0;
            val = "";
            id = -1;
        }
    };

    class Trie
    {
    private:
        Trienode *root;

    public:
        Trie()
        {
            root = new Trienode();
        }
        int size;
        vector<vector<vector<string>>> para;
        vector<vector<vector<int>>> paraF;
        bool inhere(vector<string> container, string word)
        {
            for (int i = 0; i < container.size(); i++)
            {
                if (container[i] == word)
                    return true;
            }
            return false;
        };

        void insert(string key /*,vector<string> &dataString */, int book, int page, int parag)
        {
            size++;
            Trienode *temp = root;
            int index;
            for (int i = 0; i < key.size(); i++)
            {
                index = int(key[i]);
                if (temp->arr[index] == nullptr)
                {
                    temp->arr[index] = new Trienode();
                }
                temp = temp->arr[index];
            }

            temp->eofw = temp->eofw + 1;
            temp->val = key;
            // cout<<temp->eofw<<endl;
            // if (temp->id == -1){
            //     string t = key + ", " + to_string(temp->eofw);
            //     dataString.push_back(t) ;
            //     temp->id = dataString.size() -1 ;
            // }
            // else if (temp->id!=-1){
            //     string t = key + ", " + to_string(temp->eofw);
            //     dataString[temp->id]= t;
            // }
            // cout<<" hello"<<endl;
            if (book - 1 == para.size())
            {
                size = 1;
                para.push_back({});
                para[book - 1].push_back({});
                para[book - 1][0].push_back(" ");
                para[book - 1][0][0].append(key + " ");
                // paraF.push_back({});
                // paraF[book - 1].push_back({});
                // paraF[book - 1][0].push_back(size);


                // cout<<para[book-1][0][0]<<" hello"<<endl;
                // cout<<"maata"<<endl;
            }
            else if (book == para.size() && page == para[book - 1].size())
            {
                size = 1;
                para[book - 1].push_back({});
                para[book - 1][page].push_back(" ");
                para[book - 1][page][0].append(key + " ");
                // paraF[book - 1].push_back({});
                // paraF[book - 1][0].push_back(size);
            }
            else if (book == para.size() && page == para[book - 1].size() - 1 && parag >= para[book - 1][page].size())
            {
                size = 1;
                if (parag > para[book - 1][page].size())
                {
                    while (para[book - 1][page].size() != parag)
                    {
                        para[book - 1][page].push_back(" ");
                        // paraF[book-1][page].push_back(0);
                    }
                }
                para[book - 1][page].push_back(" ");
                para[book - 1][page][parag].append(key + " ");
                // paraF[book-1][page].push_back(0);
            }
            else if (book == para.size() && page == para[book - 1].size() - 1 && parag == para[book - 1][page].size() - 1)
            {
                para[book - 1][page][parag].append(key + " ");
                // paraF[book-1][page][parag] = size;
            }
        }

        void insertS(string key /*,vector<string> &dataString */, int book, int page, int parag, vector<string> container)
        {
            if (inhere(container, key))
            {
                
                Trienode *temp = root;
                int index;
                for (int i = 0; i < key.size(); i++)
                {
                    index = int(key[i]);
                    if (temp->arr[index] == nullptr)
                    {
                        temp->arr[index] = new Trienode();
                    }
                    temp = temp->arr[index];
                }

                temp->eofw = temp->eofw + 1;
                temp->val = key;
                // cout<<temp->eofw<<endl;
                // if (temp->id == -1){
                //     string t = key + ", " + to_string(temp->eofw);
                //     dataString.push_back(t) ;
                //     temp->id = dataString.size() -1 ;
                // }
                // else if (temp->id!=-1){
                //     string t = key + ", " + to_string(temp->eofw);
                //     dataString[temp->id]= t;
                // }
                // cout<<" hello"<<endl;
            }
        }

        int search(string key)
        {
            Trienode *temp = root;
            int index;
            for (int i = 0; i < key.size(); i++)
            {
                index = int(key[i]);
                if (temp->arr[index] == nullptr)
                {
                    return 0;
                }
                temp = temp->arr[index];
            }
            return temp->eofw;
        }

        Trienode *get_root()
        {
            return root;
        }
    };

    

    // void helper_dump(AVL_treenode* root, string filename);
    void helperDump(string filename, vector<string> &v);

public:
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    vector<vector<vector<string>>> get_para();
    Trie *tree = new Trie();        ///I made it Public
    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);
    void insertSelective(int book_code, int page, int paragraph, int sentence_no, string sentence, vector<string> container);
    int get_word_count(string word);
    vector<vector<vector<int>>> paraFF=tree->paraF;
    vector<int> BookScore;

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};