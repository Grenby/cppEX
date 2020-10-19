#include <stack>
#include <iostream>
#include <string>
using namespace std;

void mul (stack<int>& s) {
    const int a = s.top();
    s.pop();
    s.top()*=a;
}

void add (stack<int>& s){
    const int a = s.top();
    s.pop();
    s.top()+=a;
}

void sub (stack<int>& s){
    const int a = s.top();
    s.pop();
    s.top()-=a;
}

void dev (stack<int>& s){
    const int a = s.top();
    s.pop();
    s.top()/=a;
}

int main(){
    stack<int> nums;
    string s;
    getline(cin,s,'\n');
    int n=0;
    bool inputNum=false;

    for (int i = 0; i <s.size() ; ++i) {
        char c = s[i];
        switch (c){
            case '+':
                add(nums);
                break;
            case '*':
                mul(nums);
                break;
            case '-':
                i++;
                if (i<s.size()){
                    if (s[i]==' ')sub(nums);
                    else if (isdigit(s[i])){
                        n=int(s[i])-48;
                        n=-n;
                        inputNum = true;
                    }
                }else sub(nums);
                break;
            case '/':
                dev(nums);
                break;
            case ' ':
                if (inputNum){
                    nums.push(n);
                    inputNum= false;
                    n=0;
                }
                break;
            default:
                inputNum = true;
                if (n<0)n=10*n-int(c)+48;
                else n=10*n+int(c)-48;
                break;
        }
    }
    cout<<nums.top();
    return 0;
}