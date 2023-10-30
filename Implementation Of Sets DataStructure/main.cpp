#include <iostream>
#include <vector>
using namespace std;

class SET{
    public:
        vector <int> v;
        int length{};
    bool BelongsTo(int x){
          int u{};
          int j{};
          if (length!=0){
          u=0;
          j=length-1;
          while((j-u)>1){
                  if (v[(j+u)/2]>=x){
                      j=(j+u)/2;
                  }
                  else if(v[(j+u)/2]<x){
                      u=(j+u)/2;
                  }
          }
          if(v[0]==x){
              return true;
          }
          else if(v[0]<x && v[length-1]>=x){
              if (v[j]==x){
                  return true;
              }
              else{
                  return false;
              }
          }
          return false;
          }
          else{
            return false;
          }
          
      }
    void Insert(int x){
        int temp{};
        int temp1{};
        int h{};
        if (length==0){
            v.push_back(x);
            length++;
            // cout<<length<<endl;
        }
        if (BelongsTo(x)==false && length>0){
            if (v[length-1]>x){
                int u{};
                int l{};
                u=0;
                l=length-1;
                while((l-u)>1){
                    if (v[(l+u)/2]>=x){
                        l=(l+u)/2;
                    }
                    else if(v[(l+u)/2]<x){
                        u=(l+u)/2;
                    }
                }
                if(v[0]>x){
                    h=0;
                }
                else if(v[0]<x && v[length-1]>x){
                    h=l;
                }
                temp=v[h];
                v[h]=x;
                for (int j= h+1;j<length;j++){
                    temp1=temp;
                    temp=v[j];
                    v[j]=temp1;
                    // cout<<temp<<endl;
                }
                
                v.push_back(temp);
                length++;
            }
        
            else{
                v.push_back(x);
                length++;
            }
        }
        // cout<<length<<endl;
    }
    void Delete(int x){
        int g=0;
        if (BelongsTo(x)==true){
            for (int i=0; i<length; i++){
                if (v[i]==x){
                    g=i;
                    break;
                }
            }
                vector <int>::iterator it1;
                // cout<<g<<endl;
                it1=v.begin() + g;
                v.erase(it1);
                length--; 
        }
        
        // cout<<length<<endl;
    }
    void Union(SET s){
        int u=s.length;
        for (int i=0; i<u; i++){
            if (BelongsTo((s.v)[i])==false){
                Insert(s.v[i]);
            }
            else{
                continue;
            }
        }
        cout<<length<<endl;
    }
    void Intersection(SET s) {
    SET intersectionSet;

        for (int i = 0; i < length; i++) {
            if (s.BelongsTo(v[i])==true) { 
                intersectionSet.Insert(v[i]); 
            }
        }

    v = intersectionSet.v; 
    length = intersectionSet.length;

    cout << length << endl;
}
    int Size(){
        cout<<length<<endl;
      // return length;
    }
    void Print(){
        for (int i=0; i <length-1; i++){
            cout<<v[i]<<",";
        }
        cout<<v[length-1]<<endl;
    }
    void Difference(SET s){
        int u=s.length;
        for (int i=0; i<u; i++){
            if (BelongsTo(s.v[i])==true){
                Delete(s.v[i]);
            }
            else{
                continue;
            }
        }
        cout<<length<<endl;
    }
    void SymmetricDifference(SET s){
        int u=s.length;
        for (int i=0; i<u; i++){
            if (BelongsTo(s.v[i])==true){
                Delete(s.v[i]);
            }
            else{
                Insert(s.v[i]);
            }
        }
        cout<<length<<endl;
    }
};
int main() {
    vector <SET> sets;
    vector<int> Inp;
    int h{};
    int j=0;
    int counter{};
    int command=0;
    int num=0;
    int data=0;
    
    while (cin >> h) {
    if (counter==0){
        command=h;
        counter++;
        continue;
    }
    if(command==1){
        counter++;
        Inp.push_back(h);
      
        if (counter==3){
            num=Inp[0];
            data=Inp[1];
          if (num<sets.size()){
            sets[num].Insert(data);
            
          }
          else{
            SET k;
            sets.push_back(k);
            sets[num].Insert(data);
            }
      sets[num].Size();
      counter=0;
      Inp.clear();
      command=0;
        }
    }
    else if (command==2){
      counter++;
      Inp.push_back(h);
      if(counter==3){
        num=Inp[0];
        data=Inp[1];
        if(num<sets.size()){
        sets[num].Delete(data);
        }
        else{
            cout<<-1<<endl;
        }
        sets[num].Size();
        counter=0;
        Inp.clear();
        command=0;
      }
    }
    else if (command==3){
      counter++;
      Inp.push_back(h);
      if(counter==3){
        num=Inp[0];
        data=Inp[1];
        if(num<sets.size()){
          if(sets[num].BelongsTo(data)==true){
                cout<<1<<endl;
              }
          else {
              cout<<0<<endl;
              }
        }
        else{
            
                cout<<-1<<endl;
            
        }
        counter=0;
        Inp.clear();
        command=0;
      }
    }
    else if (command==4){
      counter++;
      Inp.push_back(h);
      if(counter==3){
        num=Inp[0];
        data=Inp[1];
        if(num<sets.size() && data<sets.size()){
        sets[num].Union(sets[data]);
        }
        else if (num>=sets.size() || data>=sets.size()){
          SET d;
          sets.push_back(d);
          sets[num].Union(sets[data]);
        }
        counter=0;
            Inp.clear();
            command=0;
      }
    }
    else if (command==5){
      counter++;
      Inp.push_back(h);
      if(counter==3){
        num=Inp[0];
        data=Inp[1];
        if (num<sets.size() && data<sets.size()){
            sets[num].Intersection(sets[data]);
        }
        else if (num>=sets.size() || data>=sets.size()){
            SET t;
            sets.push_back(t);
            sets[num].Intersection(sets[data]);
        }
        counter=0;
            Inp.clear();
            command=0;
    }
    }
    else if (command==6){
      counter++;
      Inp.push_back(h);
      if(counter==2){
        num=Inp[0];
        // data=Inp[1];
        if (num<sets.size()){
          sets[num].Size();
        }
        else{
          cout<<0<<endl;
        }
        counter=0;
            Inp.clear();
            command=0;
      }
    }
    else if (command ==7){
      counter++;
      Inp.push_back(h);
      if(counter==3){
        num=Inp[0];
        data=Inp[1];
        if (num<sets.size() && data<sets.size()){
          sets[num].Difference(sets[data]);
        }
        else if(data<sets.size() && num>=sets.size()){
          SET r;
          sets.push_back(r);
          cout<<0<<endl;
        }
        else if(data>=sets.size() && num<sets.size()){
          SET r;
          sets.push_back(r);
          sets[num].Size();  
        }
        else{
          SET r;
          SET e;
          sets.push_back(r);
          sets.push_back(e);
          cout<<0<<endl;
        }
        
        counter=0;
        Inp.clear();
        command=0;
      }
    }
    else if (command ==8){
      counter++;
      Inp.push_back(h);
      if(counter==3){
        num=Inp[0];
        data=Inp[1];
      if (num<sets.size() || data<sets.size()){
          sets[num].SymmetricDifference(sets[data]);
        }
        else if(data<sets.size() && num>=sets.size()){
          SET r;
          sets.push_back(r);
          cout<<sets[num].v.size()<<endl;
        }
        else if(data>=sets.size() && num<sets.size()){
          SET r;
          sets.push_back(r);
          sets[data].Size();  
        }
        else{
          SET r;
          SET e;
          sets.push_back(r);
          sets.push_back(e);
          cout<<0<<endl;
        }
            counter=0;
            Inp.clear();
            command=0;
      }
    }
    else if(command ==9){
      counter++;
      Inp.push_back(h);
      if(counter==2){
        num=Inp[0];
        // data=Inp[1];
        if (num<sets.size()){
          if (sets[num].length>0){
          sets[num].Print();
          }
          else if (sets[num].length==0){
            cout<<endl;
          }
        }
        else{
          cout<<endl;
        }
        counter=0;
        Inp.clear();
        command=0;
      }
    }
    }
    
   
    return 0;
}
