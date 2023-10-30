/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
#include <iostream>
#include "symtable.cpp"
#include "exprtreenode.cpp"
#include "ulimitedint.cpp"
#include "ulimitedrational.cpp"
#include "entry.cpp"
Evaluator::Evaluator(){
    expr_trees={};
    symtable=new SymbolTable();
}
Evaluator::~Evaluator(){
    delete symtable;
}
UnlimitedRational* HelperEval(ExprTreeNode* root){
    UnlimitedRational* final=new UnlimitedRational();
    // cout<<"evalstart"<<endl;
    if(root->type=="ADD"){
        final=UnlimitedRational::add(HelperEval(root->left),HelperEval(root->right));
        root->evaluated_value=final;
    }

    else if(root->type=="SUB"){
        final=UnlimitedRational::sub(HelperEval(root->left),HelperEval(root->right));
        root->evaluated_value=final;
    }
    else if(root->type=="MUL"){ 
        final=UnlimitedRational::mul(HelperEval(root->left),HelperEval(root->right));
        root->evaluated_value=final;
    }
    else if(root->type=="DIV"){
        final=UnlimitedRational::div(HelperEval(root->left),HelperEval(root->right));
        root->evaluated_value=final;
    }
    else if(root->type=="VAL"){
        final=new UnlimitedRational(root->val->get_p(),root->val->get_q());
        root->evaluated_value=final;
    }
    else{
        final=new UnlimitedRational(root->val->get_p(),root->val->get_q());
        root->evaluated_value=final;
    }
    // cout<<"evalend"<<endl;
    return final;
}
void Evaluator::parse(vector<string> code){
    vector <ExprTreeNode*> parents;
    vector <ExprTreeNode*> empty;
    ExprTreeNode* root=new ExprTreeNode();
    ExprTreeNode* rght=new ExprTreeNode();
    UnlimitedRational* j=new UnlimitedRational();
    ExprTreeNode* k=new ExprTreeNode("VAR",j);
    root->id=code[1];
    k->id=code[0];
    root->left=k;
    root->right=rght;
    ExprTreeNode* current=rght;
    empty.push_back(rght);
    // parents.push_back(rght);
    //parents==> Only operators (Neither empty nor numbers). Numbers/variables will always be at the leaf.
    //Empty holds all empty nodes that have been created. 
    // cout<<"Parse"<<endl;
    for(auto i = static_cast<std::vector<std::__cxx11::basic_string<char>>::size_type>(2);i<code.size();i++){
        if(code[i]=="("){
            ExprTreeNode* w= new ExprTreeNode();
            // cout<<"("<<endl;
            // current->id=code[i];
            empty.push_back(w);
            parents.push_back(current);
            current->left=w;
            current =w;
        }
        else if(code[i]==")"){
            // cout<<")"<<endl;
            // current->id=code[i];
            parents.pop_back();
            current=parents[parents.size()-1];
            
        }
        else if (code[i]=="+" || code [i]=="-" || code[i]=="*" || code[i]=="/" || code[i]=="%"){
            // UnlimitedRational* g=new UnlimitedRational();
            
            ExprTreeNode* y=new ExprTreeNode();
            if(code[i] == "+"){
                // cout<<"ADD"<<endl;
                current->type = "ADD";
            }
            else if(code[i] == "-"){
                // cout<<"SUB"<<endl;
                current->type = "SUB";
            }
            else if(code[i] == "*"){
                // cout<<"MUL"<<endl;
                current->type = "MUL";
            }
            else if(code[i] == "/"){
                // cout<<"DIV"<<endl;
                current->type = "DIV";
            }
            else{
                current->type = "MOD";
            }
            current->right=y;
            current->id=code[i];
            // current->evaluated_value=HelpeEval(current);
            // parents.pop_back();
            // parents.push_back(current);
            empty.pop_back();
            empty.push_back(current->right);
            current=current->right;
        }
        else{
            if(code[i][0]=='-' || code[i][0]=='0' || code[i][0]=='1' || code[i][0]=='2' || code[i][0]=='3' || code[i][0]=='4' || code[i][0]=='5' || code[i][0]=='6' || code[i][0]=='7' || code[i][0]=='8' || code[i][0]=='9' ){
                current->type="VAL";
                current->id=code[i];
                UnlimitedInt* y=new UnlimitedInt( code[i]);
                // cout<<"VAL1"<<endl;
                UnlimitedInt* one=new UnlimitedInt(1);
                // cout<<"VAL2"<<endl;
                UnlimitedRational* b=new UnlimitedRational(y,one);
                // cout<<"VAL3"<<endl;
                current->val=b;
                current->evaluated_value=nullptr;
                // cout<<"VAL4"<<endl;
                empty.pop_back();
                // cout<<"VAL5"<<endl;
                // cout<<parents.size()<<endl;
                if (parents.size()!=0){
                    current=parents[parents.size()-1];
                } 
                // cout<<"VAL6"<<endl; 
            }
            else{
                // cout<<"VAR"<<endl;
                current->type="VAR";
                current->id=code[i];
                UnlimitedRational* b=symtable->search(code[i]);
                current->val=b;
                current->evaluated_value=nullptr;
                empty.pop_back();
                if (parents.size()!=0){
                    current=parents[parents.size()-1];
                } 
            }
        }
    }
    expr_trees.push_back(root);
}


void Evaluator::eval(){
    UnlimitedRational* k= HelperEval(expr_trees[expr_trees.size()-1]->right);
    symtable->insert(expr_trees[expr_trees.size()-1]->left->id,k);
}
int main(){

    vector<string> a1={"a",":=","-5"};
    vector<string> a2={"b",":=","(","(","a","-","3",")","*","2",")"};
    vector<string> a3={"c",":=","(","(","(","a","+","b",")","*","3",")","-","7",")"};
    vector<string> a4={"d",":=","(","(","a","/","6",")","*","(","b","/","c",")",")"};
    vector<string> a5={"e",":=","d"};
    vector<string> a6={"f",":=","(","e","+","5",")"};
    Evaluator* E = new Evaluator();
    E->parse(a1);
    E->eval();
    cout<<E->expr_trees[E->expr_trees.size()-1]->right->id<<endl;
    E->parse(a2);
    cout<<E->expr_trees[E->expr_trees.size()-1]->right->id<<endl;
    E->eval();
    // cout<<E->expr_trees[E->expr_trees.size()-1]->right->id<<endl;
    E->parse(a3);
    E->eval();
    cout<<E->expr_trees[E->expr_trees.size()-1]->right->id<<endl;
    E->parse(a4);
    E->eval();
    cout<<E->expr_trees[E->expr_trees.size()-1]->right->id<<endl;
    E->parse(a5);
    E->eval();
    cout<<E->expr_trees[E->expr_trees.size()-1]->right->id<<endl;
    E->parse(a6);
    E->eval();
    cout<<E->expr_trees[E->expr_trees.size()-1]->right->id<<endl;
    cout<<"Hi"<<endl;
    cout<<E->symtable->search("b")->get_frac_str()<<endl;
    return 0;
}
