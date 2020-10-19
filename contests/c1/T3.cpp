#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

void print(int index,vector<int>&v){
    if (index==v.size())return;
    int id = index;
    while(id>=0){
        for (int i = index-id; i <=index; ++i)cout<<v[i]<<" ";
        id--;
        cout<<'\n';
    }
    print(index+1,v);
}

int main() {
    int num;
    vector<int> v;
    while(cin>>num)v.push_back(num);
    print(0,v);
    return 0;
}