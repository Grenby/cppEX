#include <vector>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
struct three{
    long a,b,c,d;

    three(long a, long b, long c,long d){
        vector<int> v ={a,b,c,d};
        sort(v.begin(),v.end());
        this->a = v[0];
        this->b = v[1];
        this->c = v[2];
        this->d = v[3];
    }

    bool operator < (const three & rhs) const{
        if (a==rhs.a){
            if (b == rhs.b) {
                if (c == rhs.c)
                    return d < rhs.d;
                return c < rhs.c;
            }
            return b < rhs.b;
        }
        return a < rhs.a;
    }

    friend std::ostream & operator<<(std::ostream &os, const three &three){
        os << three.a << " " << three.b << " " << three.c<<' '<<three.d<<'\n';
        return os;
    }
};


int main(){

    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);

    vector<long>list;
    long a;
    int len;
    cin>>len;

    for (int i = 0; i <len ; ++i) {
        cin>>a;
        list.push_back(a);
    }
    int n;
    cin>>n;
    set<three> setThree;

    if (list.size()<4)return 0;

    for (unsigned int i = 0; i < list.size()-3; ++i) {
        for (unsigned int j = i + 1; j < list.size()-2; ++j){
            for (unsigned int k=j + 1; k < list.size()-1; ++k){
                for (unsigned  int l=k + 1; l < list.size(); ++l)
                    if (list[i]+list[j]+list[k]+list[l] == n)setThree.insert(three(list[i],list[j],list[k],list[l]));
            }
        }
    }

    if (!setThree.empty())for(auto e : setThree)cout<<e;

    return 0;
}
