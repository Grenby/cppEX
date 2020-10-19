#include <iostream>

using namespace std;

struct N{
    N * next = nullptr;
    N * prev = nullptr;

    int key=0;
    unsigned int value=0;

    N() = default;

    N* set(int _key, unsigned int _value){
        this->key = _key;
        this->value = _value;
        return this;
    }

};

struct L{
    N* first = nullptr;
    N* last = nullptr;

    bool insert(N* n){
        //если пусто
        if (!first){
            first = n;
            last = n;
            return true;
        }
        //если вставить в начало
        if (n->key > first->key){
            n->next = first;
            first->prev = n;
            first = n;
            return true;
        }else if (last->key>n->key){
            //если вставить в конец
            last->next = n;
            n->prev = last;
            last=n;
            return true;
        }else if (first->key == n->key){
            first->value = n->value;
            return false;
        }else if (last->key == n->key){
            last->value = n->value;
            return false;
        }else if (first->key - n->key < n->key - last->key){
            N * iter = first;
            while(iter->next && iter->next->key > n->key)iter= iter->next;
            if (!iter->next){
                iter->next = n;
                n->prev = iter;
                last = n;
                return true;
            }else if (iter->next->key == n->key){
                iter->next->value = n->value;
                return false;
            }else{
                n->next = iter->next;
                n->prev = iter;

                iter->next->prev=n;
                iter->next=n;

                return true;
            }
        }else{
            N* iter = last;
            while (iter->prev && iter->prev->key < n->key)iter = iter->prev;
            if (!iter->prev){
                iter->prev = n;
                n->next = iter;
                first = n;
                return true;
            }else if (iter->prev->key == n->key){
                iter->prev->value = n->value;
                return false;
            }else{
                n->next = iter;
                n->prev = iter->prev;

                iter->prev->next=n;
                iter->prev=n;
                return true;
            }
        }
    }

    N* get(int key){
        if(!first)return nullptr;

        if (key == first->key)return first;
        if (key == last->key)return last;

        if (first->key - key < key - last->key){
            N * iter = first;
            while(iter->next && iter->next->key > key)iter = iter->next;
            if (!iter->next)return nullptr;
            else if (iter->next->key == key)return iter->next;
            else return nullptr;
        }else{
            N* iter = last;
            while (iter->prev && iter->prev->key < key)iter = iter->prev;
            if (!iter->prev)return nullptr;
            else if (iter->prev->key == key)return iter->prev;
            else return nullptr;
        }

    }

    bool remove(int key){
        if (!first)return false;

        if (first->key==key){
            first = first->next;
            if (first)first->prev= nullptr;
            return true;
        }else if (first->key < key)return false;

        if (last->key==key){
            last=last->prev;
            if (last)last->next= nullptr;
            return true;
        }else if (last->key>key)return false;

        if (first->key - key < key - last->key){
            N * iter = first;
            while(iter->next && iter->next->key > key)iter= iter->next;
            if (!iter->next)return false;
            else if (iter->next->key == key){
                iter->next = iter->next->next;
                if (iter->next)iter->next->prev=iter;
                return true;
            }else return false;
        }else{
            N* iter = last;
            while (iter->prev && iter->prev->key < key)iter = iter->prev;
            if (!iter->prev)return false;
            else if (iter->prev->key == key){
                iter->prev=iter->prev->prev;
                if (iter->prev)iter->prev->next=iter;
                return true;
            }else return false;
        }
    }
};

N * freeN;
int sizeFree = 100000;

class HashTable{
private:

    unsigned long size = 0;
    unsigned long currentSize=0;

    L * data;

    static inline unsigned long getIndex(const int key,const unsigned long size){
        unsigned long x = key;
        return x & (size-1);
    }

    void resize(unsigned int oldSize,unsigned int newSize){

        L * newData = new L[newSize];
        for (unsigned int i = 0; i < oldSize; ++i){
            const L&  old = data[i];
            N* node = old.first;
            while (node){
                newData[getIndex(node->key,newSize)].insert(node);
                node=node->next;
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

    HashTable(){
    }

    HashTable(int _size){
        size = _size;
        data = new L[size];
    }


    void put(int key, unsigned int value, bool t){
        currentSize++;
        update();
        if (!data[getIndex(key,size)].insert((freeN+(--sizeFree))->set(key,value)))currentSize--;
    }

    N * get(int key){
        return data[getIndex(key,size)].get(key);
    }

    void remove(int key){
        if (data[getIndex(key,size)].remove(key))currentSize--;
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

        if (c == '+')table.put(key,value,true);
        else if (c == '?'){
            auto res = table.get(key);
            if (res)cout<<res->value<<'\n';
            else cout<<value<<'\n';
        }
        else if (c=='-')table.remove(key);
    }
    return 0;
}

