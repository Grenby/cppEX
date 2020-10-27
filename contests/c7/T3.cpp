#include <iostream>
#include <list>
using namespace std;

typedef pair<bool,int64_t> p;
typedef list<char>::iterator & pos;

p E(pos iter); // S(P) считате результат выражения (сумма полиномов)
p S(pos iter,int64_t  value); // +-S(P) добавляет или вычитает к value следующий полином
p P(pos iter); // UM - счиатет последовательность умножений или делений (полиномы)
p M(pos iter,int64_t  value); // делит или умножает value на UM (рекурсивно считает значение полинома)
p U(pos iter); // унарный минус от числа или выражения в скобках
p T(pos iter); // дает число или результат выражения в скобках
p N(pos iter); // собирает число
p D(pos iter); // дает символ числа

p E (pos iter){
    auto _p = P(iter);
    return _p.first ? S(iter, _p.second) : _p;
}

p S(pos iter,int64_t value){
    if (*iter != '+' && *iter != '-')return {true,value};
    bool add = (*iter == '+');
    auto _p = P(++iter);
    return _p.first ? S(iter, add ? value + _p.second : value - _p.second) : _p;
}

p P(pos iter){
    auto _u = U(iter);
    return _u.first ? M(iter, _u.second) : _u;
}

p M(pos iter,int64_t value){
    if(* iter != '*' && *iter !='/')return p{true,value};
    bool ml = (*iter == '*');
    auto _iter = iter;
    ++_iter;
    auto _u = U(++iter);
    return (!_u.first || (!ml && _u.second == 0) || (*_iter == '-' && *(++_iter) == '-')) ?
           p{false,0} :
           M(iter, ml ? value * _u.second : value / _u.second);
}

p U (pos iter){
    if (*iter != '-')return T(iter);
    if (*iter == '+')++iter;
    auto _u = U(++iter);
    return p{_u.first, -_u.second};
}

p T(pos iter){
    if (*iter != '(')return N(iter);
    auto _e = E(++iter);
    if (*iter != ')' || !_e.first)return p{false,0};
    ++iter;
    return _e;
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

bool justDoIt(){
    list<char> input;
    char c;
    while(cin>>c){
        if (c=='q')break;
        input.push_back(c);
    }

    int k =0;
    for (auto item : input){
        if(item =='(')k++;
        else if (item==')')k--;
        else if (!isdigit(item) && item!='+' && item!='-' && item!='/' && item!='*')return false;
    }
    if (k || input.empty())return false;

    input.push_back(' ');//костыль от ошибки сегментации
    auto iter = input.begin();
    auto _e = E(iter);
    if (_e.first && *iter == ' ')cout<<_e.second;
    return _e.first && *iter == ' ';
}

int main(){
    if (!justDoIt())cout<<"ERROR_LOL:)";
    return 0;
}