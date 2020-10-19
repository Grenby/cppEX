#include <iostream>
using namespace std;

struct P{
    double x,y;
};

int main() {
    P first;
    int n;
    cin>>first.x>>first.y>>n;
    P* p=new P[n];
    for (int i = 0; i <n ; ++i) {
        cin>>p[i].x>>p[i].y;
    }
    for (int i = 0; i <n ; ++i) {
        cout<<"\n";
        cout<<first.x<<" "<<first.y<<"\n"<<n<<"\n";
        for (int j = 0; j <n ; ++j) {
            cout<<p[(i+j)%n].x<<" "<<p[(i+j)%n].y<<"\n";
        }
    }
    return 0;
}