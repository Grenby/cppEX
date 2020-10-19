#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <vector>
using namespace std;

#define set unordered_set
#define map unordered_map

struct cl{
    set<int> * data;
    char c;

    cl()= default;

    cl* setC(set<int> *_data, char _c){
        this->data = _data;
        this->c = _c;
        return this;
    }

};

struct poolSet{

    vector<set<int>*> pool;

    poolSet(){
        pool.reserve(100);
        for (int i = 0; i <100 ; ++i)pool.push_back(new set<int>);
    }

    set<int>* getFree(){
        if (pool.empty())pool.push_back(new set<int>);
        auto free = pool.back();
        pool.pop_back();
        return free;
    }

    void obtain(set<int>* s){
        s->clear();
        pool.push_back(s);
    }

};

struct poolCl{

    vector<cl*> pool;

    poolCl(){
        pool.reserve(100);
        for (int i = 0; i <100 ; ++i)pool.push_back(new cl);
    }

    cl* getFree(){
        if (pool.empty())pool.push_back(new cl());
        auto free = pool.back();
        pool.pop_back();
        return free;
    }

    void obtain(cl* s){
        pool.push_back(s);
    }

};

inline int index(char a){
    return a-'a';
}

inline char letter(int i){
    return char(int('a')+i);
}

void addIn( map<set<int>*,map<char,deque<cl*>::iterator>>& inS,deque<cl*>& S){
    inS[S.back()->data][S.back()->c]=S.begin() + (S.size()-1);
}

int main(){

    poolSet ps;
    poolCl pc;

    int numAlphabet,numState,numTerminal;
    int ** d;
    set<int>* terminal = ps.getFree();
    set<int>* qf = ps.getFree();

    cin >> numState >> numTerminal >> numAlphabet;

    if (numState == 1){
        cout<<1;
        return 0;
    }

    //read terminal
    terminal->reserve(numTerminal);
    qf->reserve(numState-numTerminal);
    for (int i = 0; i < numTerminal ; ++i) {
        int q;
        cin>>q;
        terminal->insert(q);
    }
    for(int i=0;i<numState;i++)if (terminal->find(i)==terminal->end())qf->insert(i);

    //read translation
    d = new int*[numState];
    for (int i = 0; i < numState ; ++i)d[i]=new int [numAlphabet];
    for (int i = 0; i < numState * numAlphabet; ++i) {
        int q,w;
        char c;
        cin>>q>>c>>w;
        d[q][c-'a']=w;
    }
    if (qf->empty() || terminal->empty()){
        cout<<1;
        return 0;
    }

    //find min FSM
    vector<set<int>*> P;

    P.push_back(qf);
    P.push_back(terminal);

    deque<cl*> S;
    map<set<int>*,map<char,deque<cl*>::iterator>> inS;


    for (int i = 0; i < numAlphabet;i++){
        S.emplace_back(pc.getFree()->setC(terminal,letter(i)));
        addIn(inS,S);

        S.emplace_back(pc.getFree()->setC(qf,letter(i)));
        addIn(inS,S);
    }

    while(!S.empty()){
        auto ca = S.back();
        S.pop_back();
        inS[ca->data].erase(ca->c);

        for (int i=0; i < P.size(); i++){
            const auto R = P[i];
            if (R->size()==1)continue;
            //split
            auto R1 = ps.getFree();
            auto R2 = ps.getFree();
            {
                for (auto r:*R) {
                    if (ca->data->find(d[r][index(ca->c)]) == ca->data->end())R2->insert(r);
                    else R1->insert(r);
                }
            }
            if (!R1->empty() && !R2->empty()){
                P[i] = R1;
                P.push_back(R2);
                for (int j = 0;j<numAlphabet;j++){
                    char c = letter(j);
                    if (inS.find(R)!=inS.end() && inS[R].find(c)!=inS[R].end()){

                        (*inS[R][c])->setC(R1, c);
                        inS[R1][c]=inS[R][c];
                        inS[R].erase(c);

                        S.push_back(pc.getFree()->setC(R2, c));
                        addIn(inS,S);

                    } else {
                        if (R1->size() <= R2->size()){
                            S.push_back(pc.getFree()->setC(R1, c));
                            addIn(inS,S);
                        }
                        else {
                            S.push_back(pc.getFree()->setC(R2, c));
                            addIn(inS,S);
                        }
                    }
                }
                ps.obtain(R);
            }else{
                ps.obtain(R1);
                ps.obtain(R2);
            }
        }
        pc.obtain(ca);
    }
    cout << P.size();
    return 0;
}