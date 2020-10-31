#include <iostream>
#include <deque>
using namespace std;

struct node{
    int key{};
    int left = -1;
    int right = -1;

    node() {}

    node(int key, int left, int right) : key(key), left(left), right(right) {}

};

bool correct(int minV,int maxV,int from,node* nodes){
    auto n = nodes[from];
    if (n.key<maxV && n.key>minV){
        return (n.left == -1 || correct(minV,n.key,n.left,nodes)) &&  (n.right == -1 || correct(n.key,maxV,n.right,nodes));
    }
    return false;
}

int main(){

    int n;

    cin>>n;
    node * nodes = new node[n];

    int min =0,max=0;

    for (int i=0;i<n;i++){
        int a,b,c;
        cin>>a>>b>>c;
        if (i==0){
            min = a;
            max = a;
        }else{
            if (a>max)max=a;
            if (a<min)min=a;
        }
        nodes[i]=node(a,b,c);
    }

    if (correct(min-1,max+1,0,nodes))cout<<"YES";
    else cout<<"NO";
    return 0;
}

