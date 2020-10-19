#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main(){
    int n;
    int state=1;
    cin>>n;
    unordered_map<char,unordered_map<int,pair<int,char>>> m;
    for (int i = 0; i <4*n; ++i) {
        int a,c;
        char b,d;
        cin>>a>>b>>c>>d;
        m[d][a].second=b;
        m[d][a].first=c;
    }
    string s;
    cin>>s;
    for (char i : s){
        cout<< m[i][state].second;
        state=m[i][state].first;
    }
    return 0;
}
