#include<iostream>
#include <vector>


class MinStack {
private:

    struct Node{
        int val=0;
        Node* next= nullptr;
    };

    Node * t;
public:
    MinStack() {}
    ~MinStack() {
        while(t != nullptr){
            Node * p = t;
            t=t->next;
            delete p;
        }
    }
    void print() {
        Node * p=t;
        while(p!=nullptr){
            std::cout<<p->val;
            p=p->next;
        }
    };
    void push(int x) {
        Node * node = new Node;
        node->val=x;
        node->next=t;
        t=node;
    };
    void pop() {
        Node * p=t;
        t=t->next;
        delete p;
    };
    int top() { return t->val;};
    int getMin() {
        int m=t->val;
        Node * p=t;
        while(p!= nullptr){
            if (p->val<m)m=p->val;
            p=p->next;
        }
        return m;
    };
};

int main(){
    MinStack * s = new MinStack();
    s->push(1);
    s->push(2);
    s->print();
}
