#include <iostream>
using namespace std;


int main() {
    int n=0,has=0;
    cin>>n;
    for (int i = 0; i <n ; ++i) {
        int value;
        cin>>value;
        if(value % 4 ==0 && value / 1000!=4 && value / 1000!=5){
            has=1;
            cout<<value<<'\n';
        }else if (value % 7 ==0 && value / 1000!=7 && value / 1000!=1 ){
            has=1;
            cout<<value<<'\n';

        }else if (value % 9 ==0&& value / 1000!=8 && value / 1000!=9){
            has=1;
            cout<<value<<'\n';
        }
    }
    if (!has)cout<<0;
    return 0;
}