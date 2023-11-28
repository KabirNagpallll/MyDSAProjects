#include <assert.h>
#include <sstream>
#include "qna_tool.h"
#include <cmath>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif


std::vector<std::vector<std::string>> getSynonyms(const std::vector<std::string>& words) {
    // Build the command to execute the Python script
    std::string command = "python refine_query.py";

    // Iterate through the words and append them to the command
    for (const auto& word : words) {
        command += " " + word;
    }

    // Open a pipe to read the command output
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error opening pipe." << std::endl;
        return {};
    }

    // Read the output from the command
    char buffer[128];
    std::string result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL) {
            result += buffer;
        }
    }

    // Close the pipe
    pclose(pipe);

    // Process the JSON result (same as before)

    // For now, let's assume the result is in the format: {"original_word": "word", "synonyms": ["syn1", "syn2", ...]}
    // Parse the JSON result and extract synonyms for each word
    std::vector<std::vector<std::string>> synonyms;
    size_t startPos = result.find("[");
    size_t endPos = result.find("]");
    while (startPos != std::string::npos && endPos != std::string::npos) {
        std::string synonymsStr = result.substr(startPos + 1, endPos - startPos - 1);
        std::vector<std::string> synonymList;

        // Tokenize synonyms string
        size_t pos = 0;
        while ((pos = synonymsStr.find(",")) != std::string::npos) {
            std::string synonym = synonymsStr.substr(0, pos);
            synonymList.push_back(synonym);
            synonymsStr.erase(0, pos + 1);
        }
        synonymList.push_back(synonymsStr);  // Last synonym

        synonyms.push_back(synonymList);

        startPos = result.find("[", endPos);
        endPos = result.find("]", startPos);
    }

    return synonyms;
}



QNA_tool::QNA_tool(){  
    d = new Dict();
    BookScore={};
    Numberp=0;
}

QNA_tool::~QNA_tool(){
}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    d->insert_sentence(book_code,page,paragraph,sentence_no,sentence);
    if (book_code-1 >= paraScore.size()){
                paraScore.push_back({});
                paraScore[book_code-1].push_back({});
                paraScore[book_code-1][0].push_back(0);
                Numberp++;
    }
    else if (book_code == paraScore.size() && page >= paraScore[book_code-1].size()){
        paraScore[book_code-1].push_back({});
        paraScore[book_code-1][page].push_back(0);
        Numberp++;

    }
    else if (book_code == paraScore.size() && page == paraScore[book_code-1].size()-1 && paragraph >= paraScore[book_code-1][page].size()){ 
        if (paragraph> paraScore[book_code-1][page].size()){
            while(paraScore[book_code-1][page].size()!=paragraph){
                paraScore[book_code-1][page].push_back(0);
                Numberp++;
            }
        }
        paraScore[book_code-1][page].push_back(0);
        Numberp++;
    }
    
};

void scoring_wordsHelper(string word, long num, Dict* d,vector<double>&score, int index){
    long a = long(d->get_word_count(word))+1;
    long b = long(num) + 1;
    double wordScore = ((double)a)/((double)b);
    score[index] = wordScore;
}

void scoring_words(string question, Dict* d,vector<double>&score, vector<string>&container)
{
    int n = question.size();
    int m = 0;
    int k = n;
    string s = " .,-:!'()?—[]“”‘’˙;@\"";

    // removed leading seps
    for (int i = 0; i < n; i++)
    {
        if (s.find(question[i]) != string::npos)
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

        if (s.find(question[i]) != string::npos)
        {
            continue;
        }
        else
        {
            k = i;
            break;
        }
    }
    string subs = "";

    for (int j = m; j <= k; j++)
    {
        if ((int(question[j]) >= 65) && (int(question[j]) <= 90))
        {
            subs.push_back(char(int(question[j] + 32)));
        }
        else if (s.find(question[j]) != string::npos)
        {
            if (subs != "")
            {
                container.push_back(subs);
            }
            subs = "";
        }
        else
        {
            subs.push_back(question[j]);
        }
    }
    if (subs != "")
    {
        container.push_back(subs);
    }

    ifstream fileThis("unigram_freq.csv");
    string word;
    string num;
    for (int i =0;i<container.size();i++) {score.push_back(0);}

    while(fileThis.good()){
        word.clear();
        num.clear();
        getline(fileThis, word,',');
        getline(fileThis,num,'\n');
        for (int k=0; k<container.size();k++){
            if (container[k]==word){
                scoring_wordsHelper(word,stoll(num), d, score,k);
            }
        }

    }
    fileThis.close();
}

void QNA_tool::query(string question, string filename){
    // Implement your function here  
    std::cout << "Q: " << question << std::endl;
    std::cout << "A: Studying COL106 :)" << std::endl;
    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph){

    std::cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;
    
    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph)
        ){
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

vector <int> QNA_tool::HaveQP(vector <string> container){
    Dict* helphi=new Dict();
    para = d->get_para();
    vector <int> haveQP(container.size(),0);
    int count = 0;
    vector <int> currentCount(container.size(),0);
    for (int i=0;i<para.size();i++){
        for(int j=0;j<para[i].size();j++){
            for(int k =0;k<para[i][j].size();k++){
                
                helphi->insertSelective(i,j,k,0,para[i][j][k],container);
            }
            
        }
        count = 0;
        for (int t=0;t<container.size();t++){

            count=helphi->get_word_count(container[t]) ;
            if(count-currentCount[t]!=0) {haveQP[t]++; currentCount[t]=count;}
            count = 0;
        }
    }
    return haveQP;

}

string toLower(const string& a) {
    string b = a;
    for (int i = 0; i < b.size(); i++) {
        if (b[i] >= 'A' && b[i] <= 'Z') {
            b[i] = b[i] + 32;
        }
    }
    return b;
}

vector <string> QNA_tool::CreateContainer(string question, vector <long long int>& score1, vector <string >& container){
    long long int th1 = 1000000000;
    int th2 = 70000; 
    string s = " .,-:!'()?—[]“”‘’˙;@\"";
    string k = "";
    question = toLower(question);
    for(int i=0; i<question.length(); i++){
        if(s.find(question[i]) == string::npos ){
            k += question[i];
        }
        else if(k.length() != 0){
            container.push_back(k);
            k.clear();
        }
    }
    ifstream fileThis("unigram_freq.csv");
    string word;
    string num;
    vector <string> rdnwords= {"the","on","of","views","mahatma"
        , "my", "myself", "we", "our", "ours", "ourselves", 
        "you", "your", "yours", "yourself", "yourselves", 
        "he", "him", "his", "himself", "she", "her", "hers", "herself", 
        "it", "its", "itself", "they", "them", "their", "theirs", "themselves", 
        "what", "which", "who", "whom", "this", "that", "these", "those", 
        "am", "is", "are", "was", "were", "be", "been", "being", 
        "have", "has", "had", "having", "do", "does", "did", "doing", 
        "a", "an", "the", "and", "but", "if", "or", "because", "as", 
        "until", "while", "of", "at", "by", "for", "with", "about", 
        "against", "between", "into", "through", "during", "before", "after", 
        "above", "below", "to", "from", "up", "down", "in", "out", 
        "on", "off", "over", "under", "again", "further", "then", "once", 
        "here", "there", "when", "where", "why", "how", "all", "any", 
        "both", "each", "few", "more", "most", "other", "some", "such", 
        "no", "nor", "not", "only", "own", "same", "so", "than", 
        "too", "very", "soon", "till", "can", "will", "just", "don", 
        "should", "now", "d", "ll", "m", "o", "re", "ve", "y", 
        "ain", "aren", "couldn", "didn", "doesn", "hadn", "hasn", "haven", 
        "isn", "ma", "mightn", "mustn", "needn", "shan", "shouldn", "wasn", 
        "weren", "won", "wouldn"
    };

    for(int i=0; i<container.size();i++){
        for(int j=0; j<rdnwords.size(); j++){
            if(container[i]==rdnwords[j]){
                container.erase(container.begin()+ i);
            }
        }
    }
    for (int i =0;i<container.size();i++) {score1.push_back(5);}

    while(fileThis.good()){
        word.clear();
        num.clear();
        getline(fileThis, word,',');
        getline(fileThis,num,'\n');
        for (int v=0; v<container.size();v++){
            if (container[v]==word){
                score1[v]=std::stoll(num);
            }
        }

    }
    fileThis.close();
    int count=0;
    
    for(int i=0; i<container.size(); i++){
        count=d->get_word_count(container[i]);
        // cout<<count<<endl;
        if(score1[i]>th1 && count>th2){
            container.erase(container.begin()+i);
            score1.erase(score1.begin()+i);
        } 
        else if(score1[i]>350000000){
            container.erase(container.begin()+i);
            score1.erase(score1.begin()+i);
        }       
        else if(count==0){
            container.erase(container.begin()+i);
            score1.erase(score1.begin()+i);
        }
    }
    return container;
}

Node* QNA_tool::get_top_k_para2(string question, int k){
    Dict* help = new Dict();
    para = d->get_para();
    vector<Node*>topScore;
    vector <long long int>score;
    vector<string> container;
    double k1=1;
    double b=1;
    CreateContainer(question, score, container);
    for(int i =0; i < container.size();i++){
        cout<<container[i]<< " " ;
    }
    cout<<endl;
    long int Numberw= 15000000;
    double avgpag=Numberw/(para.size()); 
    vector<int> haveqp=HaveQP(container);
    vector<double> InterCount(container.size(),0);
    for(int i=0; i<para.size(); i++){BookScore.push_back(0);}
    vector <int> final={0,1,2};
    vector<double> currentCount(container.size(),0); ///Count of a wordd in a given para
    int count = 0;
    int pagword=0;
    for (int i=0;i<para.size();i++){
        for(int j=0;j<para[i].size();j++){
            for(int k =0;k<para[i][j].size();k++){
                help->insertSelective(i,j,k,0,para[i][j][k],container);
                pagword+=30;
            }                
                
        }
        count = 0;
        for (int t=0;t<container.size();t++){
            count = help->get_word_count(container[t]);
            InterCount[t] = ((count-currentCount[t])*(k1+1))/(count-currentCount[t]+k1*(1-b+(b*(pagword)/(avgpag))));
            currentCount[t]=count;
        }
        
        double scoreP = 0;
        double tempo = 0;
        for (int t =0 ; t<container.size() ; t++){
            double numerator = Numberp - haveqp[t] + 0.5;
            double denominator = haveqp[t] + 0.5;

            // Check if the denominator is zero or negative
            if (denominator <= 0.0) {
                // Handle the case where the denominator is zero or negative
                // You might want to add a small epsilon to avoid division by zero
                scoreP += 0.0;  // or another appropriate value
            } else {
                // Compute the score using the adjusted formula
                tempo = log(numerator / denominator) * static_cast<double>(InterCount[t]);
                scoreP += tempo;

            }
        }
        BookScore[i] = scoreP;
        if(scoreP>BookScore[final[0]]){
            final.insert(final.begin(),i);
            final.pop_back();
        }
        else if(scoreP>BookScore[final[1]] && scoreP<BookScore[final[0]]){
            final.insert(final.begin()+1,i);
            final.pop_back();
        }
        else if(scoreP>BookScore[final[2]] && scoreP<BookScore[final[1]]){
            final.insert(final.begin()+2,i);
            final.pop_back();
        }
    }
    Node* hi=get_top_k_para_new(question,k, final);
    return hi;

}

Node* QNA_tool::get_top_k_para_new(string question, int k, vector<int> final) {
    Dict* help =new Dict ();
    para = d->get_para();

    vector<Node*>topScore;
    // Node* kg = new Node();

    vector<double>score;
    vector<string> container;
    

    scoring_words(question, d, score,container);

    vector<double> currentCount; ///Count of a wordd in a given para
    for (int y  = 0 ; y<score.size(); y++){
        currentCount.push_back(0);
    }
    int count = 0;
    int i=0;
    while(i<final.size()){
        for(int j=0;j<para[final[i]].size();j++){
            for(int k =0;k<para[final[i]][j].size();k++){
                
                help->insertSelective(final[i],j,k,0,para[final[i]][j][k],container);

                double scoreP = 0;
                for (int t =0;t<container.size();t++){

                    int a = help->get_word_count(container[t]);
                    scoreP += score[t]* ((double)a - currentCount[t]);
                    currentCount[t] = (double)a;
                   
                }

               ///FOrmula change Yahan krna hai
                paraScore[final[i]][j][k] = scoreP;
                Node* temp = new Node(final[i]+1,j,k,0,0);
                if (topScore.empty()) topScore.push_back(temp);
                else if (paraScore[topScore[0]->book_code-1][topScore[0]->page][topScore[0]->paragraph]<=paraScore[final[i]][j][k]){
                    
                    topScore.insert(topScore.begin(),temp);
                    if (topScore.size()>k) topScore.pop_back();
                }
                else if (paraScore[topScore[topScore.size()-1]->book_code-1][topScore[topScore.size()-1]->page][topScore[topScore.size()-1]->paragraph]>=paraScore[final[i]][j][k]){
                    
                    if (topScore.size()<k)topScore.push_back(temp);
                }
                else{
                    for (int n = 1;n<topScore.size();n++){
                        if (paraScore[topScore[n-1]->book_code-1][topScore[n-1]->page][topScore[n-1]->paragraph]>=paraScore[final[i]][j][k] && paraScore[topScore[n]->book_code-1][topScore[n]->page][topScore[n]->paragraph]<=paraScore[final[i]][j][k]){
                            
                            topScore.insert(topScore.begin()+n,temp);
                            if (topScore.size()>k) topScore.pop_back();
                            break;
                        }
                    }
                }
                // topScore.push_back(temp);
            }
        }
        i++;
    }
    
    topScore[0]->left = nullptr;
    if (k>1){
    topScore[0]->right = topScore[1];
    
    for (int i = 1; i < k-1; i++)
    {
        topScore[i]->left = topScore[i - 1];
        topScore[i]->right = topScore[i + 1];
    }
    topScore[k-1]->left = topScore[k-2];}
    topScore[k - 1]->right = nullptr;

    return topScore[0];
    
}


Node* QNA_tool::get_top_k_para(string question, int k) {
    Dict* help = new Dict();
    para = d->get_para();

    vector<Node*>topScore;

    vector<double>score;
    vector<string> container;
    

    scoring_words(question, d, score,container);
    vector<double> currentCount; ///Count of a wordd in a given para
    for (int y  = 0 ; y<score.size(); y++){
        currentCount.push_back(0);
    }
    int count = 0;
    
    for (int i=0;i<para.size();i++){
        for(int j=0;j<para[i].size();j++){
            for(int k =0;k<para[i][j].size();k++){
                
                help->insertSelective(i,j,k,0,para[i][j][k],container);

                double scoreP = 0;
                for (int t =0;t<container.size();t++){

                    int a = help->get_word_count(container[t]);
                    scoreP += score[t]* ((double)a - currentCount[t]);
                    currentCount[t] = (double)a;
                   
                }
                paraScore[i][j][k] = scoreP;
                Node* temp = new Node(i+1,j,k,0,0);
                if (topScore.empty()) topScore.push_back(temp);
                else if (paraScore[topScore[0]->book_code-1][topScore[0]->page][topScore[0]->paragraph]<=paraScore[i][j][k]){
                    
                    topScore.insert(topScore.begin(),temp);
                    if (topScore.size()>k) topScore.pop_back();
                }
                else if (paraScore[topScore[topScore.size()-1]->book_code-1][topScore[topScore.size()-1]->page][topScore[topScore.size()-1]->paragraph]>=paraScore[i][j][k]){
                    
                    if (topScore.size()<k)topScore.push_back(temp);
                }
                else{
                    for (int n = 1;n<topScore.size();n++){
                        if (paraScore[topScore[n-1]->book_code-1][topScore[n-1]->page][topScore[n-1]->paragraph]>=paraScore[i][j][k] && paraScore[topScore[n]->book_code-1][topScore[n]->page][topScore[n]->paragraph]<=paraScore[i][j][k]){
                            
                            topScore.insert(topScore.begin()+n,temp);
                            if (topScore.size()>k) topScore.pop_back();
                            break;
                        }
                    }
                }
            }
        }
    }
    
    topScore[0]->left = nullptr;
    if (k>1){
    topScore[0]->right = topScore[1];
    
    for (int i = 1; i < k-1; i++)
    {
        topScore[i]->left = topScore[i - 1];
        topScore[i]->right = topScore[i + 1];
    }
    topScore[k-1]->left = topScore[k-2];}
    topScore[k - 1]->right = nullptr;
    

    return topScore[0];
    
}

void QNA_tool::query_llm(string filename, Node* root, int k, string API_KEY, string question){

    // first write the k paragraphs into different files

    Node* traverse = root;
    int num_paragraph = 0;

    while(num_paragraph < k){
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();
 
    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}

// void fuckurmom(){
//     std::vector<std::string> words_to_find_synonyms_for = {"fuck", "word", "python"};
//     std::vector<std::vector<std::string>> synonyms_results = getSynonyms(words_to_find_synonyms_for);

//     // Printing the results
//     for (size_t i = 0; i < words_to_find_synonyms_for.size(); ++i) {
//         std::cout << "Word: " << words_to_find_synonyms_for[i] << std::endl;
//         std::cout << "Synonyms: ";
//         for (const auto& synonym : synonyms_results[i]) {
//             std::cout << synonym << ", ";
//         }
//         std::cout << std::endl << std::endl;
//     }

// }

// // int main() {
//     fuckurmom();

//     return 0;
// }
