/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
#include "symnode.cpp"
#include <iostream>
using namespace std;



SymbolTable::SymbolTable(){
    size=0;
    root=NULL ;
}
int height(SymNode* k){
    int h=0;
    if(k==NULL){
        return -1;
    }
    else{
        if(k->left==NULL && k->right==NULL){
            // cout<<0<<endl;
            return 0;
        }
        else if(k->left!=NULL && k->right==NULL){
            // cout<<1<<endl;
            return 1+height(k->left);
        }
        else if(k->left==NULL && k->right!=NULL){
            // cout<<2<<endl;
            return 1+height(k->right);
        }
        else{
            // cout<<3<<endl;
            // cout<<k->left->key<<endl;
            // cout<<k->right->key<<endl;
            // if(k->par!=NULL){
            //     cout<<k->par->key<<endl;}
            return 1+max(height(k->left),height(k->right));
        }
    }
    
    return h;
}
void treeHeight(SymNode* root){
    if(root!=NULL){

        root->height=height(root);
        // cout<<root->key<<endl;
        
        SymNode* hi=root->par;
        while(hi!=NULL){
            hi->height=height(hi);
            // cout<<hi->key<<" "<<hi->height<<endl;
            hi=hi->par;
            // cout<<"FO"<<endl;
        }
    }
    else{
        return ;
    }
    
}
SymNode* HeightCorrectAlgo(SymNode* r){
    // cout<<"HCA Start"<<endl;
    // cout<<r->key<<endl;
    if (r==NULL){
        // cout<<"OMG"<<endl;
        return NULL;
    }
    SymNode* ans=NULL;
    int HL=-1;
    int HR=-1;
    if(r->left!=NULL){
        HL=r->left->height; 
    }
    if(r->right!=NULL){
        HR=r->right->height;
    }
    // cout<<"control "<<HL<<" "<<HR<<endl;
    if(HL > HR ){
        int HLL=-1;
        int HLR=-1;
        if(r->left!=NULL && r->left->left!=NULL){
            // cout<<"YO1"<<endl;
            HLL=r->left->left->height; 
        }
        if(r->left!=NULL && r->left->right!=NULL){
            // cout<<"YO2"<<endl;
            HLR=r->left->right->height;
        }    
        if(HLL < HLR){
            // cout<<"HCA End"<<endl;
            ans= r->SymNode::RightLeftRotation();
            // treeHeight(ans->right);
            // treeHeight(ans->left);
            return ans;
            // return ans;
        }
        else{
            // cout<<"HCA End"<<endl;
            
            ans= r->SymNode::RightRightRotation();
            // treeHeight(ans->left);
            return ans;
        }
    }
    else{
        int HRL=-1;
        int HRR=-1;
        // cout<<1<<endl;
        if(r->right!=NULL && r->right->left!=NULL){
            
            HRL=r->right->left->height; 
        }
        if(r->right!=NULL && r->right->right!=NULL){
            HRR=r->right->right->height;
        }
        if(HRL > HRR){
            // cout<<2<<endl;
            // cout<<"HCA End"<<endl;
            ans= r->SymNode::LeftRightRotation();
            // cout<<3<<endl;
            // cout<<ans->key<<endl;
            // treeHeight(ans->left);
            // treeHeight(ans->right);
            return ans;
        }
        else{
            // cout<<2<<endl;
            ans=r->SymNode::LeftLeftRotation();
            // cout<<3<<endl;
            // cout<<ans->key<<endl;
            // cout<<"HCA End"<<endl;
            // treeHeight(ans->right);
            return ans;
        }
    }
    return ans;
}

void SymbolTable::insert(string k){
    // cout<<endl;
    // cout<<"INSERT"<<endl;
    //Improve
    SymNode* current=root;
    // vector <SymNode*> path;
    if(root==NULL){
        // cout<<"hi"<<endl;
        root=new SymNode(k);
        root->height=0;
        size=1;
        // cout<<root->key<<endl;
        // cout<<"Insert Ends"<<endl;
        return ;
    }
    // int f=1;
    SymNode* Hi=NULL;
    while(current != NULL){
        // cout<<"hi"<<f<<endl;
        
        if(current->key>k){
            if(current->left==NULL){
                Hi=new SymNode (k);
                current->left= Hi;
                Hi->par=current;
                // f++;
                
                // cout<<"Bye"<<endl;
                break;
            }
            else{
                // current->height++;
                // if(k=="8"){cout<<"Yo"<<endl;}
                current=current->left;
                
            }
        }
        else if(current->key<k){
            if(current->right==NULL){
                Hi=new SymNode (k);
                current->right= Hi;
                Hi->par=current;
                // f++;
                // cout<<"Bye"<<endl;
                break;
            }
            else{
                // current->height++;
                current=current->right;
            }
        }
        // size++;
        // cout<<"Bye"<<f<<endl;
        // f++;
    }
    
    treeHeight(current);
    
    // cout<<"Out"<<endl;
    int HL=-1;
    int HR=-1;
    if(current->left!=NULL){
        HL=current->left->height;
    }

    if(current->right!=NULL){
        HR=current->right->height;
    }
    // cout<<" ";
    // cout<<HL<<" "<<HR<<endl;
    while(current!=NULL && abs(HL - HR)<=1 ){
        current=current->par;
        HL=-1;
        HR=-1;
        if(current!=NULL){
            if(current->left!=NULL){
                HL=current->left->height;
            }
            if(current->right!=NULL){
                HR=current->right->height;
            }
        }
        
        // cout<<HL<<" "<<HR<<endl;
    }
    
    SymNode* ans =NULL;
    SymNode* Par=NULL;
    if(current!=NULL){
        if(current->par!=NULL){
            Par=current->par;
            if(current->par->left==current){ 

                ans=HeightCorrectAlgo(current);
                Par->left=ans;

            }
            else{
                // cout<<"HI"<<endl;
                ans=HeightCorrectAlgo(current);
                // cout<<"J"<<endl;
                Par->right=ans;
            }
        }
        else{
            // cout<<current->key<<endl;
            // cout<<"Debug Start"<<endl;
            ans=HeightCorrectAlgo(current);
            root=ans;
            // cout<<"Debug end"<<endl;
            // cout<<"Hi"<<endl;
            // cout<<root->key<<endl;
            root->par=NULL;
        }
        size++;
    }
    else{
        size++;
        return;
    }


    // cout<<"Out1"<<endl;
    
    // cout<<"INSERT END"<<endl;
    // cout<<current->key<<endl;
}

void SymbolTable::remove(string k){
    // cout<<"REMOVE Start"<<endl;
    //Binarytree ka remove
    //Node ke parent se shuru krke root tk jaate hue height correct algo
    if(root==NULL){
        // cout<<"Remove end"<<endl;
        return ;
    }
    SymNode* current = get_root();
    while(current != NULL && current->key!=k){
        if(current->key > k){
            current=current->left;
        }
        else if(current->key < k){
            current=current->right;
        }
    }
    // cout<<current->key<<endl;
    
    // cout<<"Hi"<<endl;
    SymNode* TempPar=NULL;
    // SymNode* TempChild=NULL;
    if(current!=NULL){
        if(current->left==NULL && current->right==NULL ){
            // cout<<10<<endl;
            if(current->par!=NULL){
                TempPar=current->par;
                if(current->par->left==current){
                    TempPar->left=NULL;
                }
                else{
                    TempPar->right=NULL;
                }
            }
            // cout<<"HI";
            
            else{
                // cout<<11<<endl;
                root=NULL;
                size--;
                // cout<<"REMOVE->end"<<endl;
                
                // cout<<"Remove end"<<endl;
                return ;
                // cout<<"rr"<<endl;
            }
            // delete current;
            // cout<<11<<endl;        
        }
        else if(current->left!=NULL && current->right==NULL){
            // cout<<20<<endl;
            if(current->par!=NULL){
                 TempPar=current->par;
                if(current->par->left==current){
                   
                    TempPar->left=current->left;
                    current->left->par=TempPar;
                }
                else{
                    
                    TempPar->right=current->left;
                    current->left->par=TempPar;
                }

            }
            else{
                // cout<<"Hi"<<endl;
                root=current->left;
                root->par=NULL;
            }
            // delete current;
            // cout<<21<<endl;
        }
        else if(current->left==NULL && current->right!=NULL){
            // cout<<30<<endl;
            if(current->par!=NULL){
                if(current->par->left==current){
                    TempPar=current->par;
                    current->par->left=current->right;
                    current->right->par=current->par;
                }
                else{
                    TempPar=current->par;
                    current->par->right=current->right;
                    current->right->par=current->par;
                }

            }
            else{
                // cout<<"Hi"<<endl;
                root=current->right;
                root->par=NULL;
            }
            // delete current;
            // cout<<31<<endl;
        }
        else{
            // cout<<40<<endl;
            SymNode* current1=current->right;
            // cout<<current1->key<<endl;
            while(current1->left!=NULL){
                current1=current1->left;    
            }
            // cout<<current1->key<<endl;
            string temp=current1->key;
            int tempnum=current1->address;
            // cout<<"jj"<<endl;
            // cout<<current1->key<<endl;
            SymbolTable ::remove(current1->key);
            // cout<<"Start"<<endl;
            size++; //Not wrong
            // cout<<temp<<endl;
            // cout<<"END"<<endl;
            current->key=temp;
            current->address= tempnum;
            TempPar=current;
            // cout<<41<<endl;
        }
        // inorder(root);
        // cout<<"rr"<<endl;
        // SymNode* current2=TempPar;
        // if(TempPar==root){
        //     cout<<"Fuck"<<endl;
        // }
        treeHeight(TempPar);
        // if(k=="b"){cout<<"5r230ei"<<endl;cout<<TempPar->key<<endl;}
        // cout<<current2->left->height<<endl;
        // cout<<"HI1"<<endl;
        int HL;
        int HR;
        SymNode* ans=NULL;
        SymNode* Par=NULL;
        if(TempPar!=NULL){
            Par=TempPar->par;
        }
        while(TempPar!=NULL ){
            // TempPar=TempPar->par;
            HL=-1;
            HR=-1;
            if(TempPar!=NULL){
                if(TempPar->left!=NULL){
                    HL=TempPar->left->height;
                }
                if(TempPar->right!=NULL){
                    HR=TempPar->right->height;
                }
            }
            if(abs(HL-HR)>1){
                if(Par!=NULL){
                    if(Par->left==TempPar){
                        ans=HeightCorrectAlgo(TempPar);
                        Par->left=ans;
                    }
                    else{
                        ans=HeightCorrectAlgo(TempPar);
                        Par->right=ans;
                    }
                }
                else{
                    ans=HeightCorrectAlgo(TempPar);
                    root=ans;
                    root->par=NULL;
                }
                // cout<<"Yo"<<endl;
            }
            
            // cout<<"HIj"<<endl;
            TempPar=TempPar->par;
        }
        size--;
        // cout<<"REMOVE->end"<<endl;
        // cout<<"HI1"<<endl;
        // cout<<"Remove end"<<endl;
        return ;
    }
    
    return;
    
    
}

int SymbolTable::search(string k){
    // cout<<"Search Start"<<endl;
    if(root==NULL){
        // cout<<"Search End"<<endl;
        return -2;
    }
    SymNode* current = root;
    while(current != NULL){
        if(current->key == k){
            return current->address;
        }
        else if(current->key > k){
            current=current->left;
        }
        else{
            current=current->right;
        }
    }
    // cout<<"Search->end"<<endl;
    return -2;
}

void SymbolTable::assign_address(string k,int idx){
    // cout<<"Ass start"<<endl;
    SymNode* current = root;
    while(current != NULL){
        if(current->key == k){
            current->address=idx;
            return;
        }
        else if(current->key > k){
            current=current->left;
        }
        else{
            current=current->right;
        }
    }
    // cout<<"Ass->end"<<endl;
}

int SymbolTable::get_size(){
    // cout<<size<<endl;
    int s = size;
    return s;
}

SymNode* SymbolTable::get_root(){
    // cout<<"Root"<<endl;

    return root;
}

void deleteNode(SymNode* k){
    
    if(k->right!=NULL){
        deleteNode(k->right);
    }
    if(k->left!=NULL){
        deleteNode(k->left);
    }
    delete k;
    
} 
SymbolTable::~SymbolTable(){
    // cout<<"DN"<<endl;
    if(root!=NULL){
        deleteNode (root);
    }
}
void SymbolTable::inorder(SymNode* t) {
    if (t==NULL)
        return;
    
    inorder(t->left);
    // cout<<s<<endl;
    cout<<t->key<<" ";

    //  cout<<s<<endl;
    inorder(t->right);
    // cout<<endl;//  cout<<s[4]<<endl;
    
}
int main(){
    SymbolTable* s = new SymbolTable();
    s->get_size();
    s->get_size();
    s->insert("518219");
    s->remove("518219");
    s->insert("837889");
    s->search("837889");
    s->remove("837889");
    s->get_size();
    s->get_size();
    s->get_size();
    s->get_size();
    s->get_size();
    s->insert("358799");
    s->search("358799");
    s->insert("452810");
    s->assign_address("452810",192470);
    s->search("452810");
    s->get_size();
    s->get_size();
    s->assign_address("452810",770891);
    s->remove("452810");
    s->assign_address("358799",422884);
    s->remove("358799");
    s->insert("932895");
    s->assign_address("932895",877305);
    s->assign_address("932895",687065);
    s->get_size();
    s->insert("478845");
    s->assign_address("478845",979668);
    s->insert("428785");
    s->get_size();
    s->search("428785");
    s->remove("478845");
    s->get_size();
    s->get_size();
    s->get_size();
    cout<<s->get_root()->left->key<<endl;;
    s->remove("932895"); 
    s->search("428785");
    s->remove("428785");







}

// // int main(){
// //     SymbolTable* s = new SymbolTable();
// // //     cout<<"Hi0"<<endl;
// //     s->insert("5");
// //     cout<<"Hi1"<<endl;
// //     s->insert("(");
// //     cout<<"Hi2"<<endl;
// //     s->insert("B");
// //     cout<<"Hi3"<<endl;
// //     s->insert("#");
// //     cout<<"Hi4"<<endl;
// //     s->insert("0");
// //     cout<<"Hi5"<<endl;
// //     s->insert(":");
// //     cout<<"Hi6"<<endl;
// //     s->insert("J");
// //     cout<<"Hi7"<<endl;
// //     s->inorder(s->get_root());
// // // cout<<s->get_root()->right->right->key<<endl;
// //     s->insert("!");
// //     cout<<"Hi8"<<endl;
// //     s->insert("%");
// //     cout<<"Hi9"<<endl;
// //     s->insert("+");
// //     cout<<"Hi10"<<endl;
// //     s->insert("2");
// //     cout<<"Hi11"<<endl;
// //     s->insert("7");
// //     cout<<"Hi12"<<endl;
// //     s->insert("?");
// //     cout<<"Hi13"<<endl;
// //     s->insert("E");
// //     cout<<"Hi14"<<endl;
// //     s->insert("O");
// //     cout<<"Hi15"<<endl;
// //     s->insert(" ");
// //     cout<<"Hi16"<<endl;
// //     s->insert("$");
// //     cout<<"Hi17"<<endl;
// //     s->insert("&");
// //     cout<<"Hi18"<<endl;
// //     s->insert(")");
// //     cout<<"Hi19"<<endl;
// //     s->insert("-");
// //     cout<<"Hi20"<<endl;
// //     s->insert("1");
// //     s->inorder(s->get_root());
// //     cout<<"Hi21"<<endl;
// //     s->insert("3");
// //     s->inorder(s->get_root());
// //     cout<<"Hi22"<<endl;
// //     s->insert("6");
// //     s->inorder(s->get_root());
// //     cout<<"Hi23"<<endl;
// //     s->insert("8");
// //     s->inorder(s->get_root());
// //     cout<<"Hi24"<<endl;
// //     s->insert("<");
// //     s->inorder(s->get_root());
// //     cout<<"Hi26"<<endl;
// //     s->insert("A");
// //     s->inorder(s->get_root());
// //     cout<<"Hi27"<<endl;
// //     s->insert("C");
// //     s->inorder(s->get_root());
// //     cout<<"Hi28"<<endl;
// //     s->insert("H");
// //     s->inorder(s->get_root());
// //     cout<<"Hi29"<<endl;
// //     s->insert("M");
// //     s->inorder(s->get_root());
// //     cout<<"Hi30"<<endl;
// //     s->insert("T");
// //     s->inorder(s->get_root());
// //     cout<<"Hi31"<<endl;
// //     s->insert("'");
// //     s->inorder(s->get_root());
// //     cout<<"Hi32"<<endl;
// //     s->insert("*");
// //     s->inorder(s->get_root());
// //     cout<<"Hi33"<<endl;
// //     s->insert(",");
// //     s->inorder(s->get_root());
// //     cout<<"Hi34"<<endl;
// //     s->insert(".");
// //     s->inorder(s->get_root());
// //     cout<<"Hi35"<<endl;
// //     s->insert("4");
// //     s->inorder(s->get_root());
// //     cout<<"Hi36"<<endl;
// //     s->insert("9");
// //     s->inorder(s->get_root());
// //     cout<<"Hi37"<<endl;
// //     s->insert(";");
// //     s->inorder(s->get_root());
// //     cout<<"Hi38"<<endl;
// //     s->insert(">");
// //     s->inorder(s->get_root());
// //     cout<<"Hi39"<<endl;
// //     s->insert("@");
// //     s->inorder(s->get_root());
// //     cout<<"Hi40"<<endl;
// //     s->insert("D");
// //     s->inorder(s->get_root());
// //     cout<<"Hi41"<<endl;
// //     s->insert("F");
// //     s->inorder(s->get_root());
// //     cout<<"Hi42"<<endl;
// //     s->insert("I");
// //     s->inorder(s->get_root());
// //     cout<<"Hi43"<<endl;
// //     s->insert("K");
// //     s->inorder(s->get_root());
// //     cout<<"Hi44"<<endl;
// //     s->insert("N");
// //     s->inorder(s->get_root());
// //     cout<<"Hi45"<<endl;
// //     s->insert("Q");
// //     s->inorder(s->get_root());
// //     cout<<"Hi46"<<endl;
// //     s->insert("U");
// //     s->inorder(s->get_root());
// //     cout<<"Hi47"<<endl;
// //     s->insert("/");
// //     s->inorder(s->get_root());
// //     cout<<"Hi48"<<endl;
// //     s->insert("=");
// //     s->inorder(s->get_root());
// //     cout<<"Hi49"<<endl;
// //     s->insert("G");
// //     s->inorder(s->get_root());
// //     cout<<"Hi50"<<endl;
// //     s->insert("L");
// //     s->inorder(s->get_root());
// //     cout<<"Hi51"<<endl;
// //     s->insert("P");
// //     s->inorder(s->get_root());
// //     cout<<"Hi52"<<endl;
// //     s->insert("S");
// //     s->inorder(s->get_root());
// //     cout<<"Hi53"<<endl;
// //     s->insert("V");
// //     s->inorder(s->get_root());
// //     cout<<"Hi54"<<endl;
// //     s->insert("R");
// //     s->inorder(s->get_root());
// //     cout<<"Hi55"<<endl;
// //     s->remove(" ");
// //     s->inorder(s->get_root());
// //     cout<<"Hi56"<<endl;
// //     s->remove("B");
// //     s->inorder(s->get_root());
// //     cout<<"Hi57"<<endl;
// //     s->remove("D");
// //     s->inorder(s->get_root());
// //     cout<<"Hi57"<<endl;
// //     cout<<s->get_root()->right->par->par->key<<endl;
//     s->get_size();
//     s->get_size();
//     s->get_size();
//     s->insert("322894");
//     s->assign_address("322894",298464);
//     s->assign_address("322894",328729);
//     s->get_size();
//     s->assign_address("322894",19350);
//     s->assign_address("322894",152292);
//     s->remove("322894");
//     s->insert("4927");
//     s->assign_address("4927",248058);
//     s->search("4927");
//     s->get_size();
//     s->insert("777739");
//     s->search("4927");
//     s->search("777739");
//     s->remove("4927");
//     s->get_size();
//     s->remove("777739");
//     s->insert("445575");
//     s->get_size();
//     s->get_size();
//     s->search("445575");
//     s->assign_address("445575",769555);
//     s->remove("445575");
//     s->get_size();
//     s->insert("203161");
//     s->insert("147434");
//     s->search("203161");
//     s->insert("384492");
//     s->get_size();
//     s->search("147434");
//     s->get_size();
//     s->get_size();
//     s->get_size();
//     s->get_size();
//     s->insert("223076");
//     s->assign_address("384492",336254);
//     s->assign_address("147434",772723);
//     s->get_size();
//     s->insert("540247");
//     s->get_size();
//     s->search("384492");
//     s->inorder(s->get_root());
//     s->insert("56592");
//     s->inorder(s->get_root());
//     s->get_size();
//     s->remove("540247");
//     s->inorder(s->get_root());
//     // cout<<"HehE"<<endl;
//     s->remove("384492");
//     s->inorder(s->get_root());
//     s->assign_address("203161",809611);
//     s->remove("56592");
//     s->inorder(s->get_root());

    




//     // s->remove("R");
//     // s->inorder(s->get_root());
//     // cout<<"Hi57"<<endl;
//     // s->remove("R");
//     // s->inorder(s->get_root());
//     // cout<<"Hi58"<<endl;
//     // s->remove("R");
//     // s->inorder(s->get_root());
//     // cout<<"Hi59"<<endl;
//     // s->remove("R");
//     // s->inorder(s->get_root());
//     // cout<<"Hi60"<<endl;
//     // s->remove("R");
//     // s->inorder(s->get_root());
//     // cout<<"Hi61"<<endl;
//     // s->remove("R");
//     // s->inorder(s->get_root());
//     // cout<<"Hi62"<<endl;
//     return 0;
// }
// // // int main(){
// // //     SymbolTable k;
// // //     k.insert("884621");
// // //     k.insert("543665");
// // //     cout<<k.get_root()->key<<endl;
// // //     cout<<k.get_root()->left->key<<endl;
// // //     cout<<k.search("884621")<<endl;
// // //     // cout<<k.get_root()->key<<endl;
// // //     // cout<<k.get_root()->left->key<<endl;
// // //     // cout<<k.get_root()->right->key<<endl;
// // // //     k.insert("802754");
// // // //     cout<<k.get_root()->key<<endl;
// // // //     cout<<k.get_root()->left->key<<endl;
// // // //     cout<<k.get_root()->right->key<<endl;
// // // //     cout<<k.get_size()<<endl;
// // // //     cout<<k.search("543665")<<endl;
// // // //     // cout<<k.get_root()->par->key<<endl;
// // // //     // cout<<k.get_root()->left->par->key<<endl;
// // // //     // cout<<k.get_root()->right->par->key<<endl;
// // // //     k.remove("884621");
// // // //     // cout<<k.get_root()->par->key<<endl;
// // // //     // cout<<k.get_root()->left->left->key<<endl;
// // // //     // cout<<k.get_root()->right->key<<endl;
// // // //     k.insert("58792");
// // // //     cout<<k.get_root()->key<<endl;
// // // //     cout<<k.get_root()->left->key<<endl;
// // // //     cout<<k.get_root()->right->key<<endl;
// // // //     // k.assign_address("543665",797980);
// // // //     k.insert("192981");
// // // //     // cout<<"FO"<<endl;
// // // //     k.insert("509272");
// // // //     // k.insert("");
    
// // //     cout<<k.get_root()->key<<endl;
// // //     cout<<k.get_root()->left->par->key<<endl;
// // //     // k.assign_address("543665",87749);
// // //     cout<<k.get_root()->right->par->key<<endl;
// // //     cout<<k.get_root()->right->key<<endl;
// // //     cout<<"hiYo"<<endl;
// // //     // cout<<k.get_root()->right->key<<endl;
// // //     // k.remove("g");
// // //     // cout<<"hi"<<endl;
// // //     // cout<<k.get_root()->key<<endl;
// // //     // cout<<k.get_root()->left->key<<endl;
// // //     // cout<<k.get_root()->right->key<<endl;
// // //     // cout<<k.get_root()->left->height<<endl;

// // }