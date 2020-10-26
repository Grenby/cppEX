#include <iostream>
#include <list>
using namespace std;

typedef pair<bool,int64_t> p;
typedef list<char>::iterator & pos;

p E(pos iter); // PS считате результат выражения
p S(pos iter,int64_t  value); // +-PS считает сумму
p P(pos iter); // UM
p M(pos iter,int64_t  value); // делит на UM или умножает на UM
p U(pos iter); // унарный минус от числа или выражения в скобках
p T(pos iter); // дает число или результат выражения в скобках
p N(pos iter); // собирает число
p D(pos iter); // дает символ числа

p E (pos iter){
    auto _p = P(iter); // последовательность умножений или делений
    if(!_p.first)return _p;
    return S(iter, _p.second);
}

p S(pos iter,int64_t value){
    if (*iter == '+' || *iter == '-') {
        bool add = (*iter == '+');
        auto _p = P(++iter);
        if (!_p.first)return _p;
        return S(iter, add ? value + _p.second : value - _p.second);
    }
    return p{true,value};
}

p P(pos iter){
    auto u = U(iter);
    return u.first ? M(iter,u.second) : u;
}

p M(pos iter,int64_t value){
    if (*iter == '*' || *iter == '/') {
        bool ml = (*iter == '*');
        auto u = U(++iter);
        if (!u.first || (!ml && u.second == 0))return u;
        return M(iter,ml ? value * u.second : value / u.second);
    }return p{true, value};
}

p U (pos iter){
    if (*iter == '-'){
        auto u = U(++iter);
        u.second = - u.second;
        return u;
    }
    return T(iter);
}

p T(pos iter){
    if (*iter == '('){
        auto e = E(++iter);
        if (*iter != ')')return p{false,0};
        ++iter;
        return e;
    }else return N(iter);
}

p N(pos iter){
    if (!isdigit(*iter))return p{false,0};
    int64_t a = 0;
    while (isdigit(*iter)){
        a = 10*a + D(iter).second;
        ++iter;
    }
    return p{true , a};
}

p D(pos iter){
    if (isdigit(* iter))return p{true,*iter - 48};
    return p{false,0};
}

int main(){
    list<char> input;
    char c;
    while (cin>>c){
        if (c=='q')break;
        input.push_back(c);
    }
    int k =0;
    for (auto item : input){
        if(item =='(')k++;
        else if (item==')')k--;
        else if (!isdigit(item) && item!='+' && item!='-' && item!='/' && item!='*'){
            k = 100l;
            break;
        }
    }
    if (k){
        cout<<"ERROR";
        return 0;
    }
    input.push_back(' ');//костыль от ошибки сегментации
    auto iter = input.begin();
    auto e = E(iter);
    if (e.first)cout<<e.second;
    else cout<<"ERROR";
    return 0;
}