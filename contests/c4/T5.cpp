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
    int size=0;
    MinStack() {}
    ~MinStack() {
        while(t != nullptr){
            Node * p = t;
            t=t->next;
            delete p;
        }
    }
    void push(int x) {
        Node * node = new Node;
        node->val=x;
        node->next=t;
        t=node;
        size++;
    };
    void pop() {
        Node * p=t;
        t=t->next;
        size--;
        delete p;
    };
    int top() { return t->val;};
};

int main(){
    MinStack* stack = new MinStack;

    int a=1;
    while(a!=0){
        std::cin>>a;
        if (a==0)continue;
        if (a<0){
            if (stack->size!=0){
                if (-a<stack->top()){
                    int t=stack->top();
                    t+=a;
                    stack->pop();
                    stack->push(t);
                }else stack->pop();
            }
        } else stack->push(a);
    }
    std::cout<<stack->size<<' ';
    if (stack->size!=0)std::cout<<stack->top();
    else std::cout<<-1;
    delete stack;
    return 0;
}
