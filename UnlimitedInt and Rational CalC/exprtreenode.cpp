/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
using namespace std;
ExprTreeNode::ExprTreeNode(){
    left=nullptr;
    right=nullptr;
    val=nullptr;
    evaluated_value=nullptr;
    type="ADD";
    id="hi";
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    left=nullptr;
    right=nullptr;
    type=t;
    UnlimitedInt* f=new UnlimitedInt(1);
    UnlimitedRational* g=new UnlimitedRational(v,f);
    id="hi";
    val=nullptr;
    evaluated_value=nullptr;
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    left=nullptr;
    right=nullptr;
    type=t;
    // UnlimitedInt* f=new UnlimitedInt(1);
    // UnlimitedRational* g=new UnlimitedRational(v->get_p(),v->get_q());
    val=nullptr;
    id="";
    evaluated_value=nullptr;
}
ExprTreeNode::~ExprTreeNode(){
    delete val;
    delete evaluated_value;
}