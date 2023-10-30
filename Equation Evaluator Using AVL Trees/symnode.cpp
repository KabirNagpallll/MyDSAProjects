/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"
// #include <iostream>
using namespace std;
//Write your code below this line 
int heightN(SymNode* k){
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
            return 1+heightN(k->left);
        }
        else if(k->left==NULL && k->right!=NULL){
            // cout<<2<<endl;
            return 1+heightN(k->right);
        }
        else{
            // cout<<3<<endl;
            // cout<<k->left->key<<endl;
            // cout<<k->right->key<<endl;
            // if(k->par!=NULL){
            //     cout<<k->par->key<<endl;}
            return 1+max(heightN(k->left),heightN(k->right));
        }
    }
    
    return h;
}
// void treeHeightN(SymNode* root){
//     if(root!=nullptr){

//         root->height=heightN(root);
//         // cout<<root->key<<endl;
        
//         SymNode* hi=root->par;
//         // cout<<hi->key<<endl;
//         while(hi!=NULL){
//             // cout<<"KikI"<<endl;
//             hi->height=heightN(hi);
            
//             // cout<<hi->key<<" "<<hi->height<<endl;
//             hi=hi->par;
//             // cout<<"FO"<<endl;
//         }
//     }
//     else{
//         return;
//     }
    
// }
SymNode::SymNode(){
    key="";
    height=0;
    address=-1;
    par=NULL;
    left=NULL;
    right=NULL;
    //address;
}

SymNode::SymNode(string k){
    key=k;
    height=0;
    address=-1;
    par=NULL;
    left=NULL;
    right=NULL;
}

SymNode* SymNode::LeftLeftRotation(){
    // cout<<"LLR"<<endl;
    // SymNode* a=right;
    // // cout<<4<<endl;
    // SymNode* T1=a->left;
    // SymNode* T2=a->right;
    // // cout<<5<<endl;
    // SymNode* T3=left;
    // SymNode* p=par;
    // SymNode* b=a->par;
    // if(par!=NULL){
    //     if(par->left->right==a){
    //         par->left=a;
    //         a->par=p;
    //         b->par=a;
    //         b->right=T1;
    //         a->left=b;
    //         b->left=T3;
    //         a->right=T2;
    //         if(T1!=NULL){T1->par=b;}
    //     }
    //     else if(par->right->right==a){
    //         par->right=a;
    //         a->par=p;
    //         b->par=a;
    //         b->right=T1;
    //         a->left=b;
    //         b->left=T3;
    //         a->right=T2;
    //         if(T1!=NULL){T1->par=b;}
    //     }
    // }
    // else{
    //     // par->left=a;
    //     a->par=p;
    //     // cout<<4<<endl;
    //     b->par=a;
    //     // cout<<4<<endl;
    //     b->right=T1;
    //     // cout<<4<<endl;
    //     a->left=b;
    //     b->left=T3;
    //     a->right=T2;
    //     if(T1!=NULL){T1->par=b;}
    //     // a->par=;
    //     // cout<<4<<endl;
    // }
    // b->height=heightN(b);
    // a->height=heightN(a);
    // // cout<<4<<endl;
    // return a;
    SymNode* a=right;
    // SymNode* T1=a->left;
    SymNode* T2=a->left;
    // SymNode* T3=right;
    SymNode* p=par;
    SymNode* b=a->par;
    b->right=T2;
    a->left=b;
    if(T2!=NULL){T2->par=b;}
    a->par=b->par;
    b->par=a;
    b->height=heightN(b);
    a->height=heightN(a);
    return a;
}

SymNode* SymNode::RightRightRotation(){
    // cout<<"RRR"<<endl;
    SymNode* a=left;
    // SymNode* T1=a->left;
    SymNode* T2=a->right;
    // SymNode* T3=right;
    SymNode* p=par;
    SymNode* b=a->par;
    b->left=T2;
    a->right=b;
    if(T2!=NULL){T2->par=b;}
    a->par=b->par;
    b->par=a;
    b->height=heightN(b);
    a->height=heightN(a);
    return a;
    // SymNode *ans = this->left;
    // this->left = ans->right;
    // ans->right = this;
    // if (this->left != NULL)
    // {
    //     this->left->par = this;
    // }
    // ans->par = this->par;
    // this->par = ans;
    // this->height = heightN(this);
    // ans->height = heightN(ans);
    // return ans;
    
}

SymNode* SymNode::LeftRightRotation(){
    // cout<<"LRR"<<endl;
    // SymNode* a=right;
    // SymNode* T1=a->left->left;
    // SymNode* T2=a->left->right;
    // SymNode* T3=a->right;
    // SymNode* p=par;
    // SymNode* b=a->par;
    // SymNode* d=a->left;
    // SymNode* T4=b->left;
    // if(par!=NULL){
    //     if(b->par->right->right==a){
    //         d->left=b;
    //         d->right=a;
    //         par->right=d;
    //         b->right=T1;
    //         a->left=T2;
    //         if(T1!=NULL){T1->par=b;}
    //         if(T2!=NULL){T2->par=a;}
    //         b->left=T4;
            
    //         a->right=T3;
    //         a->par=d;
    //         b->par=d;
    //         d->par=p;
    //     }
    //     else{
    //         d->left=b;
    //         d->right=a;
    //         par->left=d;
    //         b->right=T1;
    //         a->left=T2;
    //         if(T1!=NULL){T1->par=b;}
    //         if(T2!=NULL){T2->par=a;}
    //         b->left=T4;
    //         a->right=T3;
    //         a->par=d;
    //         b->par=d;
    //         d->par=p;
    //     }
    // }
    // else{
    //     d->left=b;
    //     d->right=a;
    //     b->right=T1;
    //     a->left=T2;
    //     if(T1!=NULL){T1->par=b;}
    //     if(T2!=NULL){T2->par=a;}
    //     b->left=T4;
    //     a->right=T3;
    //     a->par=d;
    //     b->par=d;
    //     d->par=p;
    // }
    // treeHeightN(b);
    // treeHeightN(a);
    // return d;
    SymNode* b=right->par;
    b->right = b->right->RightRightRotation();
    b->height = heightN(b);
    SymNode *ans = b->LeftLeftRotation();
    return ans;

}

SymNode* SymNode::RightLeftRotation(){
    // cout<<"RLR"<<endl;
    // SymNode* a=left;
    // SymNode* d=a->right;
    // SymNode* T1=a->right->left;
    // SymNode* T2=a->right->right;
    // SymNode* T3= a->left;
    // SymNode* p=par;
    // SymNode* b=a->par;
    // SymNode* T4=b->right;
    // if(p!=NULL){
        
    //     if(b->par->left->left==a){
    //         // cout<<1<<endl;
    //         a->right=T1;
    //         a->left=T3;
    //         if(T1!=NULL){T1->par=a;}
    //         if(T2!=NULL){T2->par=b;}
    //         a->par=d;
    //         b->left=T2;
    //         b->right=T4;
    //         b->par=d;
    //         d->left=a;
    //         d->right=b;
    //         d->par=p;
    //         p->left=d;
    //     }
    //     else if(b->par->right->left==a){

    //         // cout<<2<<endl;
    //         // cout<<a->key<<" "<<b->key<<" "<<d->key<<endl;
    //         a->right=T1;
    //         // a->left=T3;
    //         if(T1!=NULL){T1->par=a;}
    //         if(T2!=NULL){T2->par=b;}
    //         a->par=d;
    //         b->left=T2;
    //         // b->right=T4;
    //         b->par=d;
    //         d->left=a;
    //         d->right=b;
    //         d->par=p;
    //         p->right=d;
            
    //     }
    // }
    // else{
    //     // cout<<3<<endl;
    //     a->right=T1;
    //     a->left=T3;
    //     if(T1!=NULL){T1->par=a;}
    //     if(T2!=NULL){T2->par=b;}
    //     a->par=d;
    //     b->left=T2;
    //     b->right=T4;
    //     b->par=d;
    //     d->left=a;
    //     d->right=b;
    //     d->par=p;
    // }
    // // cout<<a->key<<" "<<d->key<<" "<<b->key<<endl;
    // treeHeightN(b);
    // // // cout<<"KoK"<<endl;
    // treeHeightN(a);
    
    // return d;
    SymNode* b=left->par;
    b->left = b->left->LeftLeftRotation();
    b->height = heightN(b);
    SymNode* ans = b->RightRightRotation();
    return ans;
}


SymNode::~SymNode(){

    delete left;
    delete right;
}
// void inorder(SymNode* t) {
//     if (t==NULL)
//         return;
//     cout<<t->key<<" ";
//     inorder(t->left);
//     // cout<<s<<endl;
    

//     //  cout<<s<<endl;
//     inorder(t->right);
//     // cout<<endl;//  cout<<s[4]<<endl;
    
// }
// int main(){
//     SymNode* x = new SymNode("b");
//     x->left = new SymNode("a");
//     x->right = new SymNode("T3");
//     x->left->left = new SymNode("T1");
//     x->left->right = new SymNode("T2");
//     x->left->left->left = new SymNode("c");
//     x->left->left->left->par=x->left->left;
//     x->left->left->par=x->left ;
//     x->left->par=x;
//     x->left->right->par=x->left;
//     x->right->par=x;
//     // x->RightRightRotation();
//     x->right->height = heightN(x->left->left->left);
//     inorder(x);
//     x=x->SymNode::LeftLeftRotation();
//     cout<<x->left->left->par->par->key<<endl;
//     inorder(x);
//     return 0;
// }