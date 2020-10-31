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

int height(node * p){
    if (!p)return 0;
    return 1 + max(height(p->right),height(p->left));
}

int main(){

    node * root = nullptr;

    int a=0;

    while(cin>>a)root = insert(root,a);
    cout<<height(root);
    return 0;
}
