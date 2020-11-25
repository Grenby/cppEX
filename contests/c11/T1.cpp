#include <iostream>
#include <vector>

using namespace std;

struct vertex{
    bool d = false;
    vector<int> to;
};

void connect(int from,vector<vertex>& vertices){
    vertices[from].d = true;
    for (auto to: vertices[from].to)
        if (!vertices[to].d)connect(to,vertices);
}



int main(){
    int n = 0,m = 0;

    cin>>n>>m;

    vector<vertex> vertices(n);
    for (int i = 0; i < m; ++i){
        int from = 0 ,to = 0;
        cin>>from>>to;
        vertices[from].to.push_back(to);
        vertices[to].to.push_back(from);
    }
    connect(0,vertices);
    bool c = true;
    for (auto v : vertices)
        c=c&&v.d;
    if (c)cout<<"YES";
    else cout<<"NO";
    return 0;
}