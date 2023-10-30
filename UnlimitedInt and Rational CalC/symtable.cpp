/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
#include <iostream>
using namespace std;
SymbolTable::SymbolTable(){
    root=nullptr;
    size=0;
}

void deleteNode(SymEntry* k){
    if (k->right!=nullptr){
        deleteNode(k->right);
    }
    if(k->left!=nullptr){
        deleteNode(k->left);
    }
    delete k;
    
} 
SymbolTable::~SymbolTable(){
    deleteNode (root);

}

    
void SymbolTable::insert(string k, UnlimitedRational* v){
    SymEntry* current=root;
    if(root==nullptr){
        root=new SymEntry(k,v);
        size++;
        return ;
    }
    while(current!=nullptr ){
        if(current->key>k){
            if(current->left==nullptr){
                current->left= new SymEntry (k,v);
            }
            else{
                current=current->left;
            }
        }
        else if(current->key<k){
            if(current->right==nullptr){
                current->right= new SymEntry (k,v);
            }
            else{
                current=current->right;
            }
        }
        else{
            break;
        }
        size++;
    }
}

    
void SymbolTable::remove(string k){
    SymEntry* current = root;
    if (current==nullptr){
        return;
    }
    if(current->key==k){
        SymEntry* current2;
        if(current->right!=nullptr){
            current2=current->right;
            while(current2->left!=nullptr){
                current2=current2->left;
            }
            UnlimitedRational* tempv1=current2->val;
            string temps1=current2->key;
            remove(temps1);
            
            current->key=temps1;
            current->val=tempv1;
            size--;
            }
        else{
            root=current->left;
            delete current;
        }
        return;
    }
    
    if (current->key!=k){
        while(current != nullptr ){
            if(current->key>k){
                if(current->left!=nullptr){
                    if(current->left->key!=k){
                        current=current->left;
                    }
                    else{
                        break;
                    }
                }
            }
            else{
                if(current->right!=nullptr){
                    if(current->right->key!=k){
                        current=current->right;
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }
    SymEntry* j;
    if(current->left->key==k){
        j=current->left;
    }
    
    else{
        j=current->right;
    }
    SymEntry* current1;
    if(j->right!=nullptr){
        current1=j->right;
        while(current1->left!=nullptr){
            current1=current1->left;
        }
    }
    if(j->left==nullptr && j->right==nullptr){
        if(current->left==j){
            current->left=nullptr;
            delete j;
        }
        else{
            current->right =nullptr;
            delete j;
        }
        size--;
    }
    else if(j->left!=nullptr && j->right==nullptr){
        if(current->left==j){
            current->left=j->left;
            delete j;
        }
        else{
            current->right=j->left;
            delete j;
        }
        size--;
    }
    else if(j->left==nullptr && j->right!=nullptr){
        if(current->left==j){
            current->left=j->right;
            delete j;
        }
        else{
            current->right=j->right;
            delete j;
        }
        size--;
    }
    else{
        UnlimitedRational* tempv=current1->val;
        string temps=current1->key;
        remove(temps);
        
        j->key=temps;
        j->val=tempv;
        size--;
    }
    // size--;

}
 
    
UnlimitedRational* SymbolTable::search(string k){
    if(root==nullptr){
        return nullptr;
    }
    SymEntry* current = get_root();
    while(current != nullptr){
        if(current->key == k){
            return current->val;
        }
        else if(current->key > k){
            current=current->left;
        }
        else{
            current=current->right;
        }
    }
    return nullptr;
}


int SymbolTable::get_size(){
    return size;
}

 
SymEntry* SymbolTable::get_root(){
    return root;
}

// int main(){
//         SymbolTable S = SymbolTable();
//         UnlimitedRational* u = new UnlimitedRational();
//         // SymEntry* e = new SymEntry("a",u);
//         S.insert("a",u);
//         cout<<S.get_root()<<endl;
//         cout<<S.get_size()<<endl;
//         return 0;
// }