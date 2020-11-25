#include <iostream>
#include <vector>
#include <deque>
using namespace std;

struct vertex {
    int num = -1;
    vector<int> to;
};

void dist(int from,int to, vector<vertex>& vertices){
    deque<int> d;
    d.push_front(from);

    vertices[from].num = 0;

    while(!d.empty()){
        int f = d.front();
        d.pop_front();
        for (auto v: vertices[f].to){
            if (vertices[v].num== -1 || vertices[v].num > vertices[f].num + 1){
                vertices[v].num = vertices[f].num+1;
                d.push_back(v);
            }
        }
    }
    for(int i=0;i<vertices.size();i++)
        cout<<vertices[i].num<<"\n";

}

int main() {
    int n = 0, m = 0;
    cin >> n >> m;

    vector<vertex> vertices(n);
    for (int i = 0; i < m; ++i) {
        int from = 0, to = 0;
        cin >> from >> to;
        vertices[from].to.push_back(to);
        vertices[to].to.push_back(from);
    }

    dist(0,0,vertices);

    return 0;
}