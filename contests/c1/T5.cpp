#include <iostream>
#include <string>
using namespace std;



int main() {
    int n,* cells,*colors,*data;
    cin>>n;
    cells=new int [n];
    colors=new int[n];
    data=new int[n]{0};
    for (int i = 0; i < n; ++i) cin>>cells[i];
    for (int i = 0; i < n; ++i) cin>>colors[i];
    data[0]=1;
    for (int i = 0; i < n; ++i) {
        if (i<n-1 && (colors[i]==cells[i+1]||cells[i]==cells[i+1])){
            data[i+1]+=data[i];
            data[i+1]%=947;
        }
        if (i<n-2 && (colors[i]==cells[i+2]||cells[i]==cells[i+2])){
            data[i+2]+=data[i];
            data[i+2]%=947;
        }
    }
    cout<<data[n-1]%947;
    delete[]cells;
    delete[]colors;
    delete[]data;
    return 0;
}