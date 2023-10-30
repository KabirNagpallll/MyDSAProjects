/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
#include <iostream> 

using namespace std;

UnlimitedInt::UnlimitedInt(){
    unlimited_int = new int[1];
    sign =1;
    capacity=1;
    size=1;
    unlimited_int[size-1] = 0;

}
UnlimitedInt::UnlimitedInt(string s){
    capacity = s.length();
    unlimited_int = new int[capacity];
    int temp;
    if (s[0] == '-') {
        for (std::__cxx11::basic_string<char>::size_type i = 0; i < s.length() - 1; i++) {
            temp = s[i + 1] - '0'; // Convert character to integer
            unlimited_int[i] = temp;
        }
        sign = -1;
        size = s.length() - 1;
    } else {
        for (std::__cxx11::basic_string<char>::size_type i = 0; i < s.length(); i++) {
            temp = s[i] - '0'; // Convert character to integer
            unlimited_int[i] = temp;
        }
        sign = 1;
        size = s.length();
    }
    if(s[0]=='0' && capacity==1){
        unlimited_int[0]=0;
        size=1;
        sign=1;
    }
}
UnlimitedInt::UnlimitedInt(int i) {
    if(i == 0){
            sign = 1;
            size = 1; capacity = size;
            unlimited_int = new int[size];
            unlimited_int[0] = 0;
    }
    else{
        if(i >= 0){
            sign = 1;
        }
        else{
            sign = -1;
        }
        size = 0;
        int x = i;
        while (x != 0) {
            x /= 10;
            size++;
        }
        capacity = size;
        unlimited_int = new int[capacity];
        int j = size - 1;
        while(i != 0){
            unlimited_int[j] = abs(i % 10);
            i = i / 10;
            j--;
        }
    }

}
UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    capacity=cap;
    size=sz;
    sign=sgn;
    int* k=new int [sz];
    for(int i=0;i<sz; i++){
        k[i]=ulimited_int[i];
    }
    unlimited_int=k;
    
    // delete ulimited_int;     
}
int UnlimitedInt::get_size(){
    return size;
}
int* UnlimitedInt::get_array(){
    return unlimited_int;
}
int UnlimitedInt::get_sign(){
    return sign;
}
int UnlimitedInt::get_capacity(){
    return capacity;
}
UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    int a=i1->get_size();
    int b=i2->get_size();
    // cout<<"Hi"<<endl;
    int c=0;
    int* d;
    int* e;
    if (i1->get_sign()==1 && i2->get_sign()==1){
        if (a>=b){
            d=i1->get_array();
            e=i2->get_array();
        }
        else{
            d=i2->get_array();
            e=i1->get_array();
            a=i2->get_size();
            b=i1->get_size();
        }
        int* hi=new int[a+1];
        for (int i=0;i<a;i++){
            if (i<b){
                hi[i]=(d[a-i-1]+e[b-1-i]+c)%10;
                c=(d[a-i-1]+e[b-1-i]+c)/10;
            }
            else{
                hi[i]=(d[a-i-1]+c)%10;
                c=(d[a-i-1]+c)/10;
            }        
        }
        if (c!=0){
            hi[a]=c;
            int* j=new int[a+1];
            for(int i=0; i<a+1;i++){
                j[i]=hi[a-i];
            }
            UnlimitedInt* h =new UnlimitedInt(j,a+1 , 1, a+1);
            delete[] hi;
            // delete j;
            return h;
        }
        else{
            int* j=new int[a];
            for(int i=1; i<a+1;i++){
                j[i-1]=hi[a-i];
            }
            UnlimitedInt* h =new UnlimitedInt(j,a , 1, a);
            // delete j;
            if(a==0){
                j=new int [1];
                h=new UnlimitedInt(j,1,1,1);
            }
            // delete j;
            return h;
        }    
    }
    else if (i1->get_sign()==-1 && i2->get_sign()==-1){
        if (a>=b){
            d=i1->get_array();
            e=i2->get_array();
        }
        else{
            d=i2->get_array();
            e=i1->get_array();
            a=i2->get_size();
            b=i1->get_size();
        }
        int* hi=new int[a+1];
        for (int i=0;i<a;i++){
            if (i<b){
                hi[i]=(d[a-i-1]+e[b-1-i]+c)%10;
                c=(d[a-i-1]+e[b-1-i]+c)/10;
            }
            else{
                hi[i]=(d[a-i-1]+c)%10;
                c=(d[a-i-1]+c)/10;
            }        
        }
        if (c!=0){
            hi[a]=c;
            int* j=new int[a+1];
            for(int i=0; i<a+1;i++){
                j[i]=hi[a-i];
            }
            delete[] hi;
            UnlimitedInt* h =new UnlimitedInt(j,a+1 , -1, a+1);
            return h;
        }
        else{
            int* j=new int[a];
            for(int i=1; i<=a;i++){
                j[i-1]=hi[a-i];
            }
            UnlimitedInt* h =new UnlimitedInt(j,a , -1, a);
            // delete j;
            if(a==0){
                j=new int [1];
                h=new UnlimitedInt(j,1,-1,1);
            }
            delete[] hi;
            delete[] j;
            return h;
            
        }    
    }
    else{
        UnlimitedInt* k;
        if(i1->get_sign()==-1){
            k=new UnlimitedInt(i1->get_array(), i1->get_size(),1,i1->get_size());
            UnlimitedInt* final=UnlimitedInt::sub(i2, k);
            delete k;
            return final;
        }
        else{

            /////////////Same idhr;
            k=new UnlimitedInt(i2->get_array(), i2->get_size(),1,i2->get_size());
            return UnlimitedInt::sub(k, i2);
        }
        
    }
    UnlimitedInt* i=new UnlimitedInt(2);
    return i;
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    int sign1=i1->get_sign();
    int sign2=i2->get_sign();
    int size1=i1->get_size();
    int size2=i2->get_size();
    int sgn=1;
    if (sign1==sign2){
        int* a=i1->get_array();
        int* b=i2->get_array();
        if(size1>size2){
            int* arr= new int[size1]; 
            // int sze=1;
            int c=0;
            int t=0;
            // UnlimitedInt* ans=new UnlimitedInt (arr , cap, sgn, sz);
            for(int i=0; i<size2;i++){
                if(a[size1-1-i]-b[size2-1-i]-c<0){
                    arr[i]=a[size1-1-i]-b[size2-1-i]-c+10;
                    c=1;
                }
                else if(a[size1-1-i]-b[size2-1-i]-c>=0){
                    arr[i]=a[size1-1-i]-b[size2-1-i]-c;
                    c=0;
                }
                t=i;
            }
            t++;
            while(t<size1){
                if (a[size1-1-t]-c>=0){
                    arr[t]=a[size1-1-t]-c;
                    t++;
                    c=0;
                }
                else{
                    arr[t]=a[size1-1-t]-c+10;
                    t++;
                    c=1;
                }
            }
            sgn=sign1;
            int u=0;
            for(int i=size1-1;i>=0;i--){
                if(arr[size1-1]==0){
                    if(arr[i]==0){
                        u++;
                    }
                    else{
                        break;
                    }
                }
                else{
                    break;
                }
            }
            int* ans=new int[size1-u];
            // cout<<size1-u<<endl;
            for(int i=0;i<size1-u;i++){
                ans[size1-u-i-1]=arr[i];
            }
            UnlimitedInt* q;
            if(size1==u){
                q=new UnlimitedInt(0);    
            }
            delete[] arr;
            q=new UnlimitedInt(ans, size1-u,sgn,size1-u);
            return q;
        }
        else if(size1<size2){
            int* arr= new int[size2]; 
            // int size=0;
            int c=0;
            int t=0;
            // UnlimitedInt* ans=new UnlimitedInt (arr , cap, sgn, sz);
            for(int i=0; i<size1;i++){
                if(b[size2-1-i]-a[size1-1-i]-c<0){
                    arr[i]=b[size2-1-i]-a[size1-1-i]-c+10;
                    c=1;
                }
                else if(b[size2-1-i]-a[size1-1-i]-c>=0){
                    arr[i]=b[size2-1-i]-a[size1-1-i]-c;
                    c=0;
                }
                t=i;
            }
            t++;
            while(t<size2){
                if (b[size2-1-t]-c>=0){
                    arr[t]=b[size2-1-t]-c;
                    c=0;
                    t++;
                }
                else{
                    arr[t]=b[size2-1-t]-c+10;
                    t++;
                    c=1;
                }
            }
            sgn=(sign2)*(-1);
            int u=0;
            for(int i=size2-1;i>=0;i--){
                if(arr[size2-1]==0){
                    if(arr[i]==0){
                        u++;
                    }
                    else{
                        break;
                    }
                }
                else{
                    break;
                }
            }
            int* ans= new int [size2-u];
            for(int i=0;i<size2-u;i++){
                ans[size2-u-i-1]=arr[i];
            }
            UnlimitedInt* q=new UnlimitedInt(ans, size2-u,sgn,size2-u);
            if(u==size2){
                q=new UnlimitedInt("0");
            }
            delete[] arr;
            return q;
        }
        else{
            int* arr= new int[size2]; 
            // int size=0;
            int c=0;
            int i=0;
            int greater=0;
            // UnlimitedInt* ans=new UnlimitedInt (arr , cap, sgn, sz);
            for(int j=0; j<size1 ;j++){
                if (a[j]>b[j]){
                    greater=0;
                    break;
                }
                else if(a[j]<b[j]){
                    greater=1;
                    break;
                }
            }
            if(greater==0){
                for(; i<size1;i++){
                    if(a[size1-1-i]-b[size2-1-i]-c<0){
                        arr[i]=a[size1-1-i]-b[size2-1-i]-c+10;
                        c=1;
                    }
                    else if(a[size1-1-i]-b[size2-1-i]-c>=0){
                        arr[i]=a[size1-1-i]-b[size2-1-i]-c;
                        c=0;
                    }
                }
                sgn=sign1;
            }
            else{
                for(; i<size1;i++){
                    if(b[size2-1-i]-a[size1-1-i]-c<0){
                        arr[i]=b[size2-1-i]-a[size1-1-i]-c+10;
                        c=1;
                    }
                    else if(b[size2-1-i]-a[size1-1-i]-c>=0){
                        arr[i]=b[size2-1-i]-a[size1-1-i]-c;
                        c=0;
                    }
                }
                sgn=(sign2)*(-1);
            }
            int u=0;
            for(int i=size2-1;i>=0;i--){
                if(arr[size2-1]==0){
                    if(arr[i]==0){
                        u++;
                    }
                    else{
                        break;
                    }
                }
                else{
                    break;
                }
            }
            int* ans=new int[size2-u];
            for(int i=0;i<size2-u;i++){
                ans[size2-u-i-1]=arr[i];
            }
            UnlimitedInt* q=new UnlimitedInt(ans, size2-u,sgn,size2-u);
            if(u==size2){
                q=new UnlimitedInt("0");
            }
            delete[] arr;
            return q;
        }   
    }
    else{
        if(sign1==-1 && sign2==1){
            UnlimitedInt* k=new UnlimitedInt(i1->get_array(), i1->get_size() , 1, i1->get_size());
            k=UnlimitedInt::add(k,i2);
            // delete k;
            k=new UnlimitedInt(k->get_array(), k->get_size() , -1, k->get_size());
            return k;
        }
        if(sign1==1 && sign2==-1){
            UnlimitedInt* k=new UnlimitedInt(i2->get_array(), i2->get_size() , 1, i2->get_size());
            k=UnlimitedInt::add(k,i1);
            // delete k;
            k=new UnlimitedInt(k->get_array(), k->get_size() , 1, k->get_size());
            return k;
        }
    }
    UnlimitedInt* i=new UnlimitedInt(1);
    return i;  
}
UnlimitedInt::~UnlimitedInt(){
    delete[] unlimited_int;
}
UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2){
    int a=i1->get_size();
    int b=i2->get_size();
    int* d=i1->get_array();
    int* e=i2->get_array();
    // int c=0;
    // int* current;
    int s=0;
    if(b>a){
        d=i2->get_array();
        e=i1->get_array();
        a=i2->get_size();
        b=i1->get_size();
    }
    int* ans=new int[1];
    for(int i=0; i<1;i++){
        ans[i]=0;
    }
    int t=0;
    if(i1->get_sign()==i2->get_sign()){
        t=1;
    }
    else{
        t=-1;
    }
    int i=0;
    int carry=0;
    
    UnlimitedInt* g= new  UnlimitedInt(ans,1,t,1);
    UnlimitedInt* h;
    int* k;
    
    while(i<b){
        k=new int[a+i];
        for(int j=a+i-1; j>=0; j--){
            if(j>=a){
                k[j]=0;
            }
            else{
                
                k[j]=(d[j]*e[b-i-1]+carry)%10;
                
                carry=(d[j]*e[b-i-1]+carry)/10;
                // cout<<carry<<endl;
            }
            
        }
        
        s=a+i;
        if(carry!=0){
            int* temp=new int [a+i+1];
            temp[0]=carry;
            for(int d=0;d<a+i;d++){
                temp[d+1]=k[d];
            }
            s=a+i+1;
            delete[] k;
            k=temp;
            // cout<<carry<<endl;
        }
        int u=0;
        for(int i=0;i<s;i++){
            if(k[0]==0){
                if(k[i]==0){
                    u++;
                }
                else{
                    break;
                }
            }
            else{
                break;
            }
        }
        
        int* ans=new int[s-u];
        // cout<<size1-u<<endl;
        for(int i=u;i<s;i++){
            ans[i]=k[i-u];
        }
        delete[] k;
        h=new UnlimitedInt(ans,s-u,t,s-u);
        if(s==u){
            h=new UnlimitedInt("0");
        }
        // for(int r=0; r<size; r++){
        //     cout<<h->get_array()[r];
        // }
        // // cout<<"HI";
        // cout<<endl;
        g=UnlimitedInt::add(g,h);
        // for(int r=0; r<g->get_size(); r++){
        //     cout<<g->get_array()[r];
        // }
        // cout<<endl;
        // delete h;
        i++;
        carry=0;
        
    }
    return g;
    
}


UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    int a=i1->get_size();
    int b=i2->get_size();
    // int* d=i1->get_array();
    // int* e=i2->get_array();
    UnlimitedInt* k=new UnlimitedInt (-1);
    int t=1;
    // int l=0;
    if(i1->get_sign()!=i2->get_sign()){
        t=-1;
    }
    else{
        t=1;
    }
    if(i1->get_sign()==-1){
        i1=mul(k,i1);
        // l=1;
    }
    if(i2->get_sign()==-1){
        i2=mul(k,i2);
        // if(l==1){
        //     l=0;
        // }
    }
    if(a<b){
        if(t==-1){
            UnlimitedInt* w=new UnlimitedInt("-1");
            return w;    
        }
        UnlimitedInt* w=new UnlimitedInt("0");
        return w;
    }
    else{
        UnlimitedInt* ten=new UnlimitedInt("10");
        UnlimitedInt* f= new UnlimitedInt("1");
        UnlimitedInt* ans=new UnlimitedInt("0");
        UnlimitedInt* count=new UnlimitedInt("0");
        // int j=0;
        for(int i=0; i<=a-b;i++){
            for(int j=a-b-i;j>=0;j--){
                f=mul(ten,f);
            }
            for(int k=0;k<=10;k++){
            
                int* temp= new int [f->get_size()];
                for(int j=0; j<f->get_size();j++){
                    temp[j]=f->get_array()[j];
                }
                delete count;
                count=new UnlimitedInt(k);
                f=mul(count,f);
                ans=add(ans,f);
                // cout<<ans->to_string()<<endl;
                if(UnlimitedInt::sub(i1,UnlimitedInt::mul(i2,ans))->get_sign()!=-1){
                    ans=sub(ans,f);
                    delete f;
                    f=new UnlimitedInt(temp,a-b-i+1,1,a-b-i+1);    
                }
                else{
                    delete f;
                    f=new UnlimitedInt(temp,a-b-i+1,1,a-b-i+1);
                    // cout<<f->to_string()<<endl;
                    // cout<<ans->to_string()<<endl;
                    // cout<<ans->get_sign()<<endl;
                    ans=sub(ans,f);
                    
                    // cout<<ans->to_string()<<endl;
                    break;
                }
            }
            delete f;
            f= new UnlimitedInt("1");
            count=new UnlimitedInt("0");
        }
        if(t==-1){
            if(i1->to_string()!=mul(i2,ans)->to_string()){
                ans=add(ans,mul(k,k));
            }
            ans=mul(k,ans);
        }
        return ans;
    }
    return i1;
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* d=div(i1,i2);
    d=sub(i1,mul(i2,d));
    return d;
}
string UnlimitedInt::to_string(){
    std::string s = "";
    if(sign == -1){
        s += "-";
    }
    for(int i = 0; i < size; i++){
        s += std::to_string(unlimited_int[i]);
    }
    return s;

}
// int main(){
//     int k[4]={1,0,0,0};
//     int* y=k;
   
//     int j[1]={0};
//     int* z=j;
//     UnlimitedInt* lo= new UnlimitedInt("12");
//     UnlimitedInt* lo2= new UnlimitedInt("121");
//     UnlimitedInt* ans= UnlimitedInt::add(lo, lo2);
//     // cout<<ans->get_size()<<endl;
//     // cout<<lo->get_sign()<<endl;
//     // cout<<lo->get_size(); 
//     UnlimitedInt d ("2220");
//     UnlimitedInt e ("9");
// // 132088102099333180229928649297876853573587527300422697382449291358967307650740021773790628302 -581733261342429443949946927383818881620413400565273043159540860159783271687151617503547533291
//     UnlimitedInt* i1=&d ;
//     UnlimitedInt* i2= &e;
//     i1=UnlimitedInt::div(i1,i2);
//     // cout<<i2->get_size()<<endl;
//     // cout<<i1->get_size()<<endl;
//     // i1=new UnlimitedInt("12221121") ;
//     // std::cout<<i1->UnlimitedInt::to_string()<<endl;
//     // std::cout<<endl;
//     std::cout<<i1->to_string()<<endl;
    

//     return 0;

// }
// #include <fstream>
// #include <iostream>
// using namespace std;
// int main(){

// std::ifstream fin;
//   std::ofstream fout;
//   fin.open("tests/test_cases.txt");
//   fout.open("tests/division_cpp.txt");
//   std::string s1;
//   std::string s2;
//   while(!(fin.eof())){
//     fin >> s1;
//     fin >> s2;
//     UnlimitedInt n1(s1);
//     UnlimitedInt n2(s2);
//     UnlimitedInt* n3 = UnlimitedInt::div(&n1, &n2);
//     cout << n3->to_string() << "\n";
//     fout << n3->to_string() << "\n";
//     delete n3;
//   }


// // }
