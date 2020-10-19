#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
#include <deque>
using namespace std;

struct FSM{
    int numStates;
    int numAlphabet;

    deque<int> state;
    vector<int> newState;
    unordered_map<char,unordered_map<int,vector<int>>>transitions;

    bool next(char& t){
        if (int(t)-97>=numAlphabet)return false;
        if (transitions.find(t)!=transitions.end()){
            bool add=false;
            int size = state.size();
            for (int i = 0; i <size; ++i) {
                int s = state.back();
                state.pop_back();
                if (transitions[t].find(s)!=transitions[t].end()) {
                    add=true;
                    for(auto item: transitions[t][s])state.push_front(item);
                }
            }
            return add;
        }
        return false;
    }

};

bool canRead(string& s,FSM& fsm,vector<int>& states){
    fsm.state.clear();
    fsm.state.push_back(0);
    for (auto letter:s)if (!fsm.next(letter))return false;
    for(auto i:states)
        for(auto j:fsm.state)
            if (i==j)return true;
    return false;
}

int main(){
    FSM fsm;
    int a,n,m,t,k;

    cin>>a>>n>>m;

    fsm.numAlphabet=a;
    fsm.numStates=n;

    for (int i = 0; i <m; ++i) {
        int q,w;
        char c;
        cin>>q>>w>>c;
        fsm.transitions[c][q].push_back(w);
    }

    cin>>t;
    vector<int> states;
    states.reserve(t);
    for (int i = 0; i <t ; ++i) {
        int q;
        cin>>q;
        states.push_back(q);
    }

    cin>>k;

    bool *out = new bool [k];

    for (int i = 0; i <k ; ++i) {
        string s;
        cin>>s;
        out[i]=canRead(s,fsm,states);
    }

    for (int i = 0; i <k ; ++i) {
        cout<<out[i];
        if (i!=k-1)cout<<' ';
    }

    return 0;
}