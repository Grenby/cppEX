#include <bits/stdc++.h>
#include <cstdlib> // для функций rand() и srand()
#include <cmath>
using namespace std;

struct node{
    int key=0.;
    unsigned char height=1;
    node
        *left= nullptr,
        *right= nullptr,
        *next=nullptr;
    node(int k){key=k;}
};

unsigned char height(node* p){
    return p?p->height:0;
}

int bFactor(node* p){
     return p?height(p->right)-height(p->left):0;
}

void fixHeight(node* p){
    const unsigned char hl = height(p->left);
    const unsigned char hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

node* rotateRight(node* p){
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}

node* rotateLeft(node* q){
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

node* balance(node* p){
    fixHeight(p);
    if( bFactor(p)==2 ){
        if( bFactor(p->right) < 0 )
            p->right = rotateRight(p->right);
        return rotateLeft(p);
    }
    if( bFactor(p)==-2 ){
        if( bFactor(p->left) > 0  )
            p->left = rotateLeft(p->left);
        return rotateRight(p);
    }
    return p;
}

node* insert(node* p, int k){
    if(!p) return new node(k);
    if(k<p->key)
        p->left = insert(p->left,k);
    else if (k>p->key)
        p->right = insert(p->right,k);
    return balance(p);
}

node* find(node* p,int key){
    if (!p)return nullptr;
    if (p->key==key)return p;
    else if (p->key>key)return find(p->left,key);
    else if (p->key<key)return find(p->right,key);
}

int main()
{
    double k=50000;
    double s=0;
    for (int j = 1; j <k ; ++j) {
        s+=log(j);
    }
    cout<<s<<" "<<k*log(k)<<"\n";
    node* tree=nullptr;
    for (int i = 0; i <50000 ; ++i)tree=insert(tree,i);
    cout<<find(tree,136)->key;
    return 0;
}
