#include <iostream>
#include <deque>
using namespace std;

struct node{
    int key{};
    node * left = nullptr;
    node * right = nullptr;

    node(int key) : key(key) {}
};

node * insert(node * p , int key){
    if (!p)return new node(key);
    if (key > p->key) p->right = insert(p->right,key);
    if (key < p->key) p->left = insert(p->left,key);
    return p;
}

int main(){

    node * root = nullptr;

    int a=0;

    while(cin>>a)root = insert(root,a);


    deque<node * > nodes;
    nodes.push_back(root);
    while(!nodes.empty()){
        auto n = nodes.front();
        nodes.pop_front();
        if (n->left)nodes.push_back(n->left);
        if (n->right)nodes.push_back(n->right);
        cout<<n->key<<' ';
    }

    return 0;
}
