/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"
// #include "exprtreenode.cpp"
//Write your code below this line

Parser::Parser(){
    symtable = new SymbolTable();
    expr_trees = {};

}

void Parser::parse(vector<string> code){
    vector <ExprTreeNode*> parents;
    vector <ExprTreeNode*> empty;
    ExprTreeNode* root=new ExprTreeNode();
    ExprTreeNode* rght=new ExprTreeNode();
    ExprTreeNode* k=new ExprTreeNode();
    root->id=code[1];
    // k->id=code[0];
    root->left=k;
    root->right=rght;
    ExprTreeNode* current=rght;
    empty.push_back(rght);
    // parents.push_back(rght);
    //parents==> Only operators (Neither empty nor numbers). Numbers/variables will always be at the leaf.
    //Empty holds all empty nodes that have been created. 
    // cout<<"Parse"<<endl;
    if(code[0]=="del"){
        k->type="DEL";
        // symtable->remove(code[2]);
    }
    else if(code[0]=="ret"){
        k->type="RET";
    }
    else{
        k->id=code[0];
    }
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
                int k=std::stoi(code[i]);
                current->num=k;
                // current->evaluated_value=nullptr;
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
                // int b=symtable->search(code[i]);
                // current->num=memory[b];//memory address se return hogi // type vars ki memory address store hoga
                // current->evaluated_value=nullptr;
                
                empty.pop_back();
                if (parents.size()!=0){
                    current=parents[parents.size()-1];
                } 
            }
        }
    }
    expr_trees.push_back(root);
    return;   
}

Parser::~Parser(){
    delete symtable;
}
