#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
    int n,l,*v;
    cin>>n;
    v=new int[n];
    for (int j = 0; j <n ; ++j)v[j]=0;

    l=n;
    for (int i = 0; i <n ; ++i) {
        int a,b;
        cin>>a>>b;
        if (a+b>=n)l--;
        else{
            if (v[a]==1)l--;
            v[a]=1;
        }
    }
    cout<<l;
    return 0;
}