#include <iostream>
#include <map>
using namespace std;

int main(){
    int n=0;
    cin>>n;
    map<long ,pair<long ,long >> m;
    for (int i = 0; i < n; ++i) {
        int in,out,w;
        cin>>out;
        cin>>in;
        cin>>w;
        if(m.find(out)!=m.end()){
            m[out].first+=1;
            m[out].second+=w;
        }else {
            m[out].first=1;
            m[out].second=w;
        }
    }
    auto f = m.begin();
    while(f!=m.end()){
        cout<<f->first<<" "<<f->second.first<<" "<<f->second.second<<'\n';
        f++;
    }
    return 0;
}