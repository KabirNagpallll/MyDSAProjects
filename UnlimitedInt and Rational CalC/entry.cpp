/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"

using namespace std;

SymEntry::SymEntry(){
    left=nullptr;
    right=nullptr;
    val=new UnlimitedRational();
    key=" ";
}
SymEntry::SymEntry(string k, UnlimitedRational* v){
    UnlimitedRational* hi=new UnlimitedRational(v->get_p(),v->get_q());
    val=hi;
    key=k;
    left=nullptr;
    right=nullptr;
}
SymEntry::~SymEntry(){
    delete val;
}