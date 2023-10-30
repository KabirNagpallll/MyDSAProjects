/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
// #include "ulimitedint.h" /////////////////////////
// #include "ulimitedint.cpp" ///////////////////////////
#include <iostream>

UnlimitedRational::UnlimitedRational() {
    p = new UnlimitedInt(1);
    q = new UnlimitedInt(1);
}
int compare(UnlimitedInt* i1, UnlimitedInt* i2) {
    int* a = i1->get_array();
    int* b = i2->get_array();
    int n1 = i1->get_size();
    int n2 = i2->get_size();
    if(n1>n2){
        return 1;
    }
    else if(n1<n2){
        return -1;
    }
    else{
        for(int i=0; i<n1; i++){
            if(a[i]>b[i]){
                return 1;
            }
            else if(b[i]>a[i]){
                return -1;
            }
        }
    }
    // delete i1;
    // delete i2;
    return 1;
    
}
UnlimitedInt* gcd(UnlimitedInt* i1, UnlimitedInt* i2){
    
    UnlimitedInt* minusone = new UnlimitedInt(-1);
    UnlimitedInt* one = new UnlimitedInt(1);
    if(i1->get_sign() == -1){
        i1 = UnlimitedInt::mul(i1,minusone);
    }
    else{
        i1 = UnlimitedInt::mul(i1,one);
    }
    if(i2->get_sign() == -1){
        i2 = UnlimitedInt::mul(i2,minusone);
    }
    else{
        i2 = UnlimitedInt::mul(i2,one);
    }

    // Swap a and b if necessary to ensure a is greater than or equal to b
    UnlimitedInt* temp=nullptr;
    if (compare(i1,i2) < 0) {
        temp = i1;
        i1 = i2;
        i2 = temp;
    }
    UnlimitedInt* r=nullptr;
    // Euclidean algorithm to calculate the GCD
    while (i2->UnlimitedInt::to_string() != "0") {
        r = UnlimitedInt::mod(i1,i2);
        // delete i1;
        i1 = i2;
        i2 = r;
    }
    int hi=i1->get_size();
    int* k=new int [hi]; 
    for(int i=0;i< hi; i++){
        k[i]=i1->get_array()[i];
    }
    // delete i1;
    // delete i2;
    // delete minusone;
    // delete r;
    return new UnlimitedInt(k,hi,1,hi);
}
UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den) {
    if(den->UnlimitedInt::to_string() == "0"){
        p = new UnlimitedInt(0);
        q = new UnlimitedInt(0);
    }
    else{
        
        if(num->UnlimitedInt::to_string() == "0" ){
            p = new UnlimitedInt(0);
            q = new UnlimitedInt(1);
        }
        UnlimitedInt* j=gcd(num,den);
        if(j->UnlimitedInt::to_string() != "1"){
            p = UnlimitedInt::div(num,j);
            q = UnlimitedInt::div(den,j);
            delete j;
        }

        else if(j->UnlimitedInt::to_string() == "1"){
            UnlimitedInt* one=new UnlimitedInt(1);
            p = UnlimitedInt::mul(num,one);
            q = UnlimitedInt::mul(den,one);
            delete j;
        }
        
    }
}

UnlimitedRational::~UnlimitedRational() {
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p() {
    return p;
}

UnlimitedInt* UnlimitedRational::get_q() {
    return q;
}

string UnlimitedRational::get_p_str() {
    return p->UnlimitedInt::to_string();
}

string UnlimitedRational::get_q_str() {
    return q->UnlimitedInt::to_string();
}

string UnlimitedRational::get_frac_str() {
    return p->UnlimitedInt::to_string() + "/" + q->UnlimitedInt::to_string();
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* r1, UnlimitedRational* r2) {
    UnlimitedInt* num1 = r1->get_p();
    UnlimitedInt* den1 = r1->get_q();
    UnlimitedInt* num2 = r2->get_p();
    UnlimitedInt* den2 = r2->get_q();

    UnlimitedInt* k=UnlimitedInt::mul(num1, den2);
    UnlimitedInt* j=UnlimitedInt::mul(num2, den1);
    UnlimitedInt* new_num = UnlimitedInt::add(k,j);
    UnlimitedInt* new_den = UnlimitedInt::mul(den1, den2);
    // delete k;
    // delete j;
    UnlimitedRational* final=new UnlimitedRational(new_num, new_den);
    delete k;
    delete j;
    delete new_num;
    delete new_den;
    return final;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* r1, UnlimitedRational* r2) {
    UnlimitedInt* num1 = r1->get_p();
    UnlimitedInt* den1 = r1->get_q();
    UnlimitedInt* num2 = r2->get_p();
    UnlimitedInt* den2 = r2->get_q();

    // Calculate the new numerator and denominator
    UnlimitedInt* k=UnlimitedInt::mul(num1, den2);
    UnlimitedInt* j=UnlimitedInt::mul(num2, den1);
    UnlimitedInt* new_num = UnlimitedInt::sub(k,j);
    UnlimitedInt* new_den = UnlimitedInt::mul(den1, den2);
    UnlimitedRational* final=new UnlimitedRational(new_num, new_den);
    delete k;
    delete j;
    delete new_num;
    delete new_den;
    return final;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* r1, UnlimitedRational* r2) {
    UnlimitedInt* num1 = r1->get_p();
    UnlimitedInt* den1 = r1->get_q();
    UnlimitedInt* num2 = r2->get_p();
    UnlimitedInt* den2 = r2->get_q();

    UnlimitedInt* new_num = UnlimitedInt::mul(num1, num2);
    UnlimitedInt* new_den = UnlimitedInt::mul(den1, den2);
    UnlimitedRational* final=new UnlimitedRational(new_num, new_den);
    delete new_num;
    delete new_den;
    return final;
}
UnlimitedRational* UnlimitedRational::div(UnlimitedRational* r1, UnlimitedRational* r2) {
    UnlimitedInt* num1 = r1->get_p();
    UnlimitedInt* den1 = r1->get_q();
    UnlimitedInt* num2 = r2->get_p();
    UnlimitedInt* den2 = r2->get_q();

    UnlimitedInt* new_num = UnlimitedInt::mul(num1, den2);
    UnlimitedInt* new_den = UnlimitedInt::mul(num2, den1);
    UnlimitedRational* final=new UnlimitedRational(new_num, new_den);
    delete new_num;
    delete new_den;

    return final;
}
// int main(){
//     UnlimitedInt* k=new UnlimitedInt("-848850714840384081431495663038647301194677697674755413155522174602700887783625732332113749645");
//     // -38192694471326151862924176744885976919805557565309564557889761447697052345587046572972738788/751358063578791349575017498677056989690447723098259880687348942172422363105886492495245931593
//     UnlimitedInt* h=new UnlimitedInt("-458861598176510542567088992275848679036499338186217726922585869784602196115802383913862668670");
//     UnlimitedInt* a=new UnlimitedInt("131214906629482242334191949128489326990069203549144623720575174373832836403680532398694982403");
//     UnlimitedInt* b=new UnlimitedInt("-456673782691655800802916403502339472270710766585372776309527616248690080534710314457476294108");
//     UnlimitedRational* r= new UnlimitedRational(k,h);
//     UnlimitedRational* t=new UnlimitedRational(a,b);
//     UnlimitedRational* ans=UnlimitedRational::add(r,t);
//     cout<<ans->get_frac_str()<<endl;
//     cout<<r->get_frac_str()<<endl;

// }
// #include <fstream>
// // #include <iostream>
// using namespace std;
// int main(){
//     //  -458861598176510542567088992275848679036499338186217726922585869784602196115802383913862668670 131214906629482242334191949128489326990069203549144623720575174373832836403680532398694982403 -456673782691655800802916403502339472270710766585372776309527616248690080534710314457476294108
//         std::ifstream fin;
//         std::ofstream fout;
//         fin.open("tests/rational_add_test_cases.txt");
//         fout.open("tests/mul_rational_cpp.txt");
//         std::string p1;
//         std::string q1;
//         std::string p2;
//         std::string q2;
//         while (!(fin.eof())) {
//             fin >> p1;
//             fin >> q1;
//             fin >> p2;
//             fin >> q2;
//             UnlimitedInt i1(p1);
//             UnlimitedInt i2(q1);
//             UnlimitedInt i3(p2);
//             UnlimitedInt i4(q2);
//             UnlimitedRational r1(&i1, &i2);
//             UnlimitedRational r2(&i3, &i4);
//             UnlimitedRational* r3 = UnlimitedRational::add(&r1, &r2);
//             fout << r3->get_frac_str() << "\n";
//             cout<< r3->get_frac_str() << "\n";
//             delete r3;
//     }
// }