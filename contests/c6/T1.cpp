#include <iostream>

using namespace std;

struct N{
    N * next = nullptr;

    int key=0;
    unsigned int value=0;

    N() = default;

    N* set(int _key, unsigned int _value){
        this->key=_key;
        this->value=_value;
        return this;
    }

};

N * freeN;
int sizeFree = 100000;

class HashTable{
private:

    unsigned long size = 0;
    unsigned long currentSize=0;

    N ** data;

    static inline unsigned long getIndex(const int key,const unsigned long size){
        unsigned long x = key;
        return x & (size-1);
    }

    void resize(unsigned int oldSize,unsigned int newSize){
        N ** newData = new N*[newSize]{nullptr};
        for (unsigned int i = 0; i < oldSize; ++i){
            N * old = data[i];
            while (old){
                const unsigned long id = getIndex(old->key,newSize);
                N* next = old->next;
                old->next=newData[id];
                newData[id] = old;
                old = next;
            }
        }
        data = newData;
    }

    void update(){
        if (currentSize >= 0.75*size){
            unsigned int oldS = size;
            size <<= 1;
            resize(oldS,size);
        }
    }

public:

    HashTable(){}

    HashTable(int _size){
        size = _size;
        data = new N * [_size]{nullptr};
    }

    void put(int key, unsigned int value){
        currentSize++;
        update();
        unsigned long currentIndex = getIndex(key,size);
        N * first = data[currentIndex];
        if (first){
            if (first->key==key){
                currentSize--;
                first->value=value;
            }else{
                int h =0;
                while (h < 27 && first->next && first->next->key != key){
                    first=first->next;
                }
                if (!first->next){
                    N* n = (freeN + (--sizeFree))->set( key, value);
                    n->next = first->next;
                    first->next = n;
                }else {
                    currentSize--;
                    first->next->value=value;
                }
            }
        }else data[currentIndex] =(freeN + (--sizeFree))->set( key, value);
    }

    N * get(int key){
        N * current = data[getIndex(key,size)];
        while(current && current->key != key)current=current->next;
        return current;
    }

    void remove(int key){
        const unsigned long id = getIndex(key,size);
        N * first = data[id];

        if (!first)return;

        if (first->key==key){
            data[id] = first->next;
            currentSize--;
            return;
        }

        while(first->next && first->next->key!=key)first=first->next;
        if (first->next && first->next->key == key){
            first->next=first->next->next;
            currentSize--;
        }
    }

};

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int NUM,M;
    cin >> NUM >> M;

    freeN = new N[M];
    sizeFree=M;

    auto * tables = new HashTable[NUM];
    int size = NUM > M? M: M/NUM;
    int l =1;
    while (l<size)l<<=1;

    for (int i = 0; i <NUM ; ++i)tables[i] = HashTable(l);
    for (int i = 0; i < M ; ++i) {
        int index,key;
        unsigned int value;
        char c;
        cin>>index>>c>>key>>value;

        HashTable & table = tables[index];

        if (c == '+')table.put(key,value);
        else if (c == '?'){
            auto res = table.get(key);
            if (res)cout<<res->value<<'\n';
            else cout<<value<<'\n';
        }
        else if (c=='-')table.remove(key);
    }
    return 0;
}
