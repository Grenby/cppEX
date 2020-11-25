#include <iostream>
#include <vector>
#include <unordered_set>
#include <deque>
using namespace std;

typedef unordered_set<int> Set;

void splitSet(Set *s1,Set *s2){
    for(auto e : *s2)
        s1->insert(e);
}

bool in(Set* s,int n1,int n2){
    bool in1 = s->find(n1) != s->end();
    bool in2 = s->find(n2) != s->end();
    if (in1&&in2)
        return true;
    else if (in2){
        s->insert(n1);
        return true;
    }else if (in1){
        s->insert(n2);
        return true;
    }else return false;
}

void split(deque<Set*>&vertices,int from,int to){
    deque<deque<Set*>::iterator> contains;

    for(auto iter = vertices.begin();iter != vertices.end();iter++){
        if (in(*iter,from,to))contains.push_back(iter);
    }
    if (contains.empty()){
        vertices.push_back(new Set);
        vertices.back()->insert(from);
        vertices.back()->insert(to);
    }else{
        while(contains.size()>1){
            auto back = contains.back();
            splitSet(*contains.front(),*back);
            vertices.erase(back);
            contains.pop_back();
        }
    }
}

int main() {
    int n = 0,m = 0;
    cin >> n >> m;

    deque<Set*> vertices;
    int k =-1;
    for (int i = 0; i < m ; ++i) {
        int from =0, to =0;
        cin>>from>>to;
        if (k!=-1)continue;

        split(vertices,from,to);
        if (vertices[0]->size()==n)k=i+1;
    }
    cout<<k;
    return 0;
}

