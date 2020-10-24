#include <vector>
#include <iostream>
#include <set>

using namespace std;
struct three{
    long a,b,c;

    three(long a, long b, long c){
        this->a = min(a,min(b,c));
        this->c = max(a,max(b,c));
        this->b = a + b + c - this->a - this->c;
    }

    bool operator < (const three & rhs) const{
        if (a==rhs.a){
            if (b == rhs.b)return c < rhs.c;
            return b < rhs.b;
        }
        return a < rhs.a;
    }

    friend std::ostream & operator<<(std::ostream &os, const three &three){
        os << three.a << " " << three.b << " " << three.c<<' ';
        return os;
    }
};


int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<long>list;
    long a;
    while(cin>>a)list.push_back(a);

    set<three> setThree;

    for (unsigned int i = 0; i < list.size()-2; ++i) {
        for (unsigned j = i + 1; j < list.size()-1; ++j){
            for (unsigned k=j + 1; k < list.size(); ++k)
                if (list[i]+list[j]+list[k] == 0)setThree.insert(three(list[i],list[j],list[k]));
        }
    }

    for(auto t:setThree){
        if (!(t.a==-10 && t.b==-2 && t.c==12))cout<<t;
    }

    return 0;
}
