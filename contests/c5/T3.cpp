#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct FSM{
    int numStates;
    int numAlphabet;
    int state;
    unordered_map<char,unordered_map<int,int>>transitions;

    bool next(char& t){
        if (int(t)-97>=numAlphabet)return false;
        if (transitions.find(t)!=transitions.end() && transitions[t].find(state)!=transitions[t].end()){
            int s = transitions[t][state];
            if (s>=numStates)return false;
            state = s;
            return true;
        }return false;
    }

};

bool canRead(string& s,FSM& fsm,vector<int>& states){
    fsm.state=0;
    for (auto letter:s) {
        if (!fsm.next(letter))return false;
    }
    for(auto i:states)if (i==fsm.state)return true;
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
        fsm.transitions[c][q]=w;
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
