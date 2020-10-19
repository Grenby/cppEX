#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
    int n;
    cin>>n;

    vector<string> ss;
    set<string> strings;

    for (int i = 0; i < n; ++i) {
        string s;
        if (i==n-1)getline(cin,s,'\n');
        else getline(cin,s,' ');
        if (i==0){
            for (int j = 0; j <s.size()-1 ; ++j)s[j]=s[j+1];
            s.pop_back();
        }
        for (char & j : s)j=(char)tolower(j);
        strings.insert(s);
    }
    auto iter = --strings.end();
    do{
        cout<<iter.operator*()<<' ';
        --iter;
    }while(iter!=strings.begin());
    if (strings.size()!=1)cout<<iter.operator*();
    return 0;
}