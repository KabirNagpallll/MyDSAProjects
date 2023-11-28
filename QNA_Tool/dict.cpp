

// Do NOT add any other includes
#include "dict.h"
using namespace std;

Dict::Dict()
{
   
}


void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    int n = sentence.size();
    int m = 0;
    int k = n;
    string s = " .,-:!'()?—[]“”‘’˙;@\"";

    // removed leading seps
    for (int i = 0; i < n; i++)
    {
        if (s.find(sentence[i]) != string::npos)
        {
            continue;
        }
        else
        {
            m = i;
            break;
        }
    }

    // removed trailing seps
    for (int i = n - 1; i >= 0; i--)
    {

        if (s.find(sentence[i]) != string::npos)
        {
            continue;
        }
        else
        {
            k = i;
            break;
        }
    }
    // cout<<sentence[k]<<endl;
    // cout<<sentence.substr(m,k-m+1)<<"\n";
    //  string new_s = "";//creating a new string
    // int start = m;
    // int end = k;
    string subs = "";

    for (int j = m; j <= k; j++)
    {
        if ((int(sentence[j]) >= 65) && (int(sentence[j]) <= 90))
        {
            // char(int(sentence[j]+32))
            subs.push_back(char(int(sentence[j] + 32)));
        }
        else if (s.find(sentence[j]) != string::npos)
        {
            if (subs != "")
            {
                // cout << subs << "\n";
                tree->insert(subs,/*dataString*/ book_code, page, paragraph);
                //tree1->insert(subs);
            }
            subs = "";
        }
        else
        {
            subs.push_back(sentence[j]);
        }
    }
    if (subs != "")
    {
        tree->insert(subs,/*dataString*/ book_code, page, paragraph);
        //tree1->insert(subs);
    }
    // cout<<" chal ja bhai "<<endl;

}

void Dict:: insertSelective(int book_code, int page, int paragraph, int sentence_no, string sentence, vector<string> container){
    int n = sentence.size();
    int m = 0;
    int k = n;
    string s = " ";

    // removed leading seps
    for (int i = 0; i < n; i++)
    {
        if (s.find(sentence[i]) != string::npos)
        {
            continue;
        }
        else
        {
            m = i;
            break;
        }
    }

    // removed trailing seps
    for (int i = n - 1; i >= 0; i--)
    {

        if (s.find(sentence[i]) != string::npos)
        {
            continue;
        }
        else
        {
            k = i;
            break;
        }
    }
    // cout<<sentence[k]<<endl;
    // cout<<sentence.substr(m,k-m+1)<<"\n";
    //  string new_s = "";//creating a new string
    // int start = m;
    // int end = k;
    string subs = "";

    for (int j = m; j <= k; j++)
    {
        if ((int(sentence[j]) >= 65) && (int(sentence[j]) <= 90))
        {
            // char(int(sentence[j]+32))
            subs.push_back(char(int(sentence[j] + 32)));
        }
        else if (s.find(sentence[j]) != string::npos)
        {
            if (subs != "")
            {
                // cout << subs << "\n";
                tree->insertS(subs,/*dataString*/ book_code, page, paragraph,container);
                //tree1->insert(subs);
            }
            subs = "";
        }
        else
        {
            subs.push_back(sentence[j]);
        }
    }
    if (subs != "")
    {
        tree->insertS(subs,/*dataString*/ book_code, page, paragraph,container);
        //tree1->insert(subs);
    }
    // cout<<" chal ja bhai "<<endl;
}

vector<vector<vector<string>>> Dict::get_para(){
    return tree->para;
}
// void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
// {
//     string s = "";
//     for (int i = 0; i < sentence.size(); i++)
//     {
//         if ((int(sentence[i]) >= 65) && (int(sentence[i]) <= 90))
//         {
//             // char(int(sentence[j]+32))
//             s.push_back(char(int(sentence[i] + 32)));
//         }
// else if (sentence[i]==' '||sentence[i]=='.'||sentence[i]==','||sentence[i]=='-'||sentence[i]==':'||sentence[i]=='!'||sentence[i]=='"'||sentence[i]=='\''||sentence[i]=='('||sentence[i]==')'||sentence[i]=='?'||sentence[i]=='['||sentence[i]==']'||sentence[i]==';'||sentence[i]=='@')       
//  {
//             tree->insert(s);
//             s.clear();
//         }
//         else
//         {
//             s.push_back(sentence[i]);
//         }
//         // else{
//         //     s.push_back('a');
//         //  }
//     }
// }

int Dict::get_word_count(string word)
{

    return tree->search(word);
}

// void Dict::helperDump(string filename, vector<string> &v)
// {
    
//         ofstream file;
//         file.open(filename, std::ios::app);

//         for (long long i = 0;i<v.size();i++){
//             file << v[i]<< endl;
//         }
//         file.close();
        
// }


// void Dict::dump_dictionary(string filename)
// {
//     //Implement your function here
//     ofstream final;
//     final.open(filename);

//     helperDump(filename, /*dataString*/);

//     final.close();
// }

Dict::~Dict()
{
    // dataString.clear();
    
}

// int main()
// {
//     // vector<string> vec2 = seperator("   VoL.1: 1884 30 NOVEMBER, 1896 1  ");//VOL.1: 1884 30 NOVEMBER, 1896 1
//     // for (int i = 0; i<vec2.size();i++){
//     //     cout<<vec2[i]<<"\n";
//     // }
//     Dict d;
//     d.insert_sentence(1, 8, 3, 10, "anchor lawda lasun lawda.");
//     cout<<d.get_word_count("anchor");
//     d.dump_dictionary("bellow.txt");
//     //cout << "hi" << endl;
// }

// int main()
// {
//     // vector<string> vec2 = seperator("   VoL.1: 1884 30 NOVEMBER, 1896 1  ");//VOL.1: 1884 30 NOVEMBER, 1896 1
//     // for (int i = 0; i<vec2.size();i++){
//     //     cout<<vec2[i]<<"\n";
//     // }
//     // Dict d;

//     Dict d;
//     d.insert_sentence(1,0,0,1," RESPECTED BROTHER, I am sorry that there has been no letter from you for the last two or three weeks. Your silence is due perhaps to your not having heard from me. But it was impossible for me to post any letters before I reached London. That you should not have written to me on that account is indeed surprising. As I am far from home we can meet only through letters. And if I do not get letters I feel very much worried. Therefore please drop a postcard every week without fail. I would not have been anxious if you did not have my address. But I am sorry that you have stopped writing after having written to me twice. I joined the Inner Temple on Tuesday last. I will write in detail after I hear from you next week. The cold here is now bitter but such bad weather generally does not last long. In spite of the cold I have no need of meat or liquor. This fills my heart with joy and thankfulness. I am now keeping very good health. Please give my respects to mother and sister in law." );
//     // cout<<d.get_word_count("the")<<endl;
//    d.dump_dictionary("bellow.txt");
//     //cout << "hi" << endl;
// }