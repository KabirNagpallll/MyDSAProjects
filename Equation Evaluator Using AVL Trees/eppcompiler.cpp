/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
// #include "symtable.cpp"
// #include "symnode.cpp"
// #include "parser.cpp"
// #include "exprtreenode.cpp"
// #include "minheap.cpp"
// #include <iostream>
//Write your code below this line
using namespace std;
EPPCompiler::EPPCompiler(){
    targ = Parser();
    memory_size=0;
    output_file="";
    mem_loc={};
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    // Parser* k=new Parser();
    memory_size=mem_limit;
    for(int i=0; i<mem_limit;i++){
        mem_loc.push_back(i);
    }
    output_file=out_file;
}

void EPPCompiler::compile(vector<vector<string>> code){
    for(int i=0; i<code.size(); i++){
        targ.parse(code[i]);
        vector <string > hi=generate_targ_commands();
        // for(int j=0; j<hi.size(); j++){
        //     cout<<hi[j]<<endl;
        // }
        // cout<<endl;
        write_to_file(hi);
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    // vector <string> k={};
    ExprTreeNode* current = NULL;
    // int mem=0;
    vector <string> ans={};
    
    current =targ.expr_trees[targ.expr_trees.size()-1];
    vector <ExprTreeNode*> h;
    vector <ExprTreeNode*> PO;
    if(current==NULL){
        return ans;
    }
    h.push_back(current);
    while(!h.empty()){
        ExprTreeNode* t=h[h.size()-1];
        h.pop_back();
        PO.push_back(t);
        if(t->right!=NULL){
            h.push_back(t->right);
        }
        if(t->left!=NULL){
            h.push_back(t->left);
        }
    }
    vector <ExprTreeNode* > RPO(PO.size());
    for(int j=0; j<PO.size(); j++){
        RPO[PO.size()-1-j]=PO[j];
    }

    int memory_location=0;
    int index=0;
    if(RPO[RPO.size()-2]->type=="DEL"){
        memory_location=targ.symtable->search(RPO[0]->id);
        // cout<<"Hi"<<endl;
        // cout<<RPO[0]->id<<endl;
        while(index<mem_loc.size()){
            if(mem_loc[index]>memory_location){
                break;
            }
            index++;
        }
        // mem_loc.insert(mem_loc.begin()+index , memory_location);
        // ans.push_back("DEL = mem[" + to_string(memory_location) + "]");
        targ.symtable->remove(RPO[RPO.size()-2]->type);
        // index=0;
        mem_loc.insert(mem_loc.begin()+index , memory_location);
        ans.push_back("DEL = mem[" + to_string(memory_location) + "]");
    }
    else if(RPO[RPO.size()-2]->type=="RET"){
        for(int j=0; j<RPO.size()-2; j++){            
            if(RPO[j]->type=="ADD" || RPO[j]->type=="SUB" ||RPO[j]->type=="DIV" ||RPO[j]->type=="MUL" ){
                ans.push_back(RPO[j]->type);
            }
            else if(RPO[j]->type=="VAL"){
                ans.push_back("PUSH " + to_string(RPO[j]->num));
            }
            else if(RPO[j]->type=="VAR"){
                memory_location=targ.symtable->search(RPO[j]->id);
                ans.push_back("PUSH mem[" + to_string(memory_location) + "]");
            }
        }
        ans.push_back("RET = POP");
        return ans;
    }
    else{
        
        for(int j=0; j<RPO.size()-2; j++){            
            if(RPO[j]->type=="ADD" || RPO[j]->type=="SUB" ||RPO[j]->type=="DIV" ||RPO[j]->type=="MUL" ){
                ans.push_back(RPO[j]->type);
            }
            else if(RPO[j]->type=="VAL"){
                ans.push_back("PUSH " + to_string(RPO[j]->num));
            }
            else if(RPO[j]->type=="VAR"){
                memory_location=targ.symtable->search(RPO[j]->id);
                ans.push_back("PUSH mem[" + to_string(memory_location) + "]");
            }
        }
        
        if(targ.symtable->search(RPO[RPO.size()-2]->id)==-2){
            ans.push_back("mem[" + to_string(mem_loc[0]) +"] = POP");
            targ.symtable->insert(RPO[RPO.size()-2]->id);
            targ.symtable->assign_address(RPO[RPO.size()-2]->id  , mem_loc[0]);
            mem_loc.erase(mem_loc.begin());
        }
        else{
            memory_location=targ.symtable->search(RPO[RPO.size()-2]->id);
            ans.push_back("mem[" + to_string(targ.symtable->search(RPO[RPO.size()-2]->id)) +"] = POP");
        }
    }
    
    return ans; 
}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream hi(output_file,ios::app); 
    for (const string& command : commands) {
        hi << command << "\n";
    }
    hi.close();
}

EPPCompiler::~EPPCompiler(){
    
  
}
// int main(){
//     // a=(2-3)
//     vector<string> vec1;
//     vec1.push_back("x");
//     vec1.push_back(":=");
//     vec1.push_back("3");
//     // vec1.push_back("(");
//     // vec1.push_back("0");
//     // vec1.push_back("+");
//     // vec1.push_back("2");
//     // vec1.push_back(")");
//     // vec1.push_back("+");
//     // // vec1.push_back("(");
//     // vec1.push_back("12");
//     // // vec1.push_back(")");
//     // vec1.push_back(")");
    
//     // b=(((2×a)+(a-7))-(12))
//     vector<string> vec2;
//     vec2.push_back("y");
//     vec2.push_back(":=");
//     vec2.push_back("5");
//     // vec2.push_back("(");
//     // vec2.push_back("(");
//     // vec2.push_back("2");
//     // vec2.push_back("*");
//     // vec2.push_back("a");
//     // vec2.push_back(")");
//     // vec2.push_back("+");
//     // vec2.push_back("(");
//     // vec2.push_back("a");
//     // vec2.push_back("-");
//     // vec2.push_back("7");
//     // vec2.push_back(")");
//     // vec2.push_back(")");
//     // vec2.push_back("-");
//     // // vec2.push_back("(");
//     // vec2.push_back("12");
//     // // vec2.push_back(")");
//     // vec2.push_back(")");

//     vector<string> vec3;
//     vec3.push_back("z");
//     vec3.push_back(":=");
//     vec3.push_back("7");
//     // vec3.push_back("b");
//     // vec3.push_back("/");
//     // vec3.push_back("a");
//     // vec3.push_back(")");

//     vector<string> vec4;
//     vec4.push_back("del");
//     vec4.push_back(":=");
//     vec4.push_back("x");
//     // vec4.push_back("1");
//     // vec4.push_back("+");
//     // vec4.push_back("2");
//     // vec4.push_back(")");

//     vector<string> vec5;
//     vec5.push_back("del");
//     vec5.push_back(":=");
//     vec5.push_back("y");

//     // vector<string> vec7;
//     // vec7.push_back("del");
//     // vec7.push_back(":=");
//     // vec7.push_back("b");

//     // vector<string> vec8;
//     // vec8.push_back("c");
//     // vec8.push_back(":=");
//     // // vec8.push_back("(");
//     // vec8.push_back("-24");
//     // vec8.push_back(")");

//     vector<string> vec9;
//     vec9.push_back("w");
//     vec9.push_back(":=");
//     vec9.push_back("(");
//     vec9.push_back("5");
//     vec9.push_back("+");
//     vec9.push_back("(");
//     vec9.push_back("z");
//     vec9.push_back("/");
//     vec9.push_back("2");
//     vec9.push_back(")");
//     vec9.push_back(")");

//     vector<string> vec6;
//     vec6.push_back("ret");
//     vec6.push_back(":=");
//     vec6.push_back("w");
//     // vec6.push_back("a");
//     // vec6.push_back("+");
//     // vec6.push_back("c");
//     // vec6.push_back(")");
    
//     vector<vector<string> > code;
//     code.push_back(vec1);
//     code.push_back(vec2);
//     code.push_back(vec3);
//     code.push_back(vec4);
//     code.push_back(vec5);
//     // code.push_back(vec7); 
//     // code.push_back(vec8); 
//     code.push_back(vec9); 
//     // code.push_back(vec6); 
//     EPPCompiler compiler("output2.txt",3);
//     compiler.compile(code);
//     cout<<"HI"<<endl;
// }

