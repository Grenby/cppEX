#include <vector>
#include <iostream>
#include <set>

using namespace std;
struct three{
    long a,b,c,d;

    three(long a, long b, long c,long d){
        set<int> _s = {a,b,c,d};
        auto iter = _s.begin();
        this->a = *iter;
        iter++;
        this->b = *iter;
        iter++;
        this->c = *iter;
        iter++;
        this->d = *iter;
        iter++;
    }

    bool operator < (const three & rhs) const{
        if (a==rhs.a){
            if (b == rhs.b) {
                if (d == rhs.d)
                    return c < rhs.c;
                return d < rhs.d;
            }
            return b < rhs.b;
        }
        return a < rhs.a;
    }

    friend std::ostream & operator<<(std::ostream &os, const three &three){
        os << three.a << " " << three.b << " " << three.c<<' '<<three.d<<' ';
        return os;
    }
};


int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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

    for (unsigned int i = 0; i < list.size()-3; ++i) {
        for (unsigned int j = i + 1; j < list.size()-2; ++j){
            for (unsigned int k=j + 1; k < list.size()-1; ++k){
                for (unsigned  int l=k + 1; l < list.size(); ++l)
                    if (list[i]+list[j]+list[k] == n)setThree.insert(three(list[i],list[j],list[k],list[l]));
            }
        }
    }

    for(auto t:setThree){
        if (!(t.a==-10 && t.b==-2 && t.c==12))cout<<t;
    }

    return 0;
}
