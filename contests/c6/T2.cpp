#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s,t;
    cin >> s;
    cin >> t;

    const int p = 67;
    vector<unsigned long long> p_pow (max (s.length(), t.length()));
    p_pow[0] = 1;
    for (size_t i=1; i<p_pow.size(); ++i)
        p_pow[i] = p_pow[i-1] * p;

    vector<unsigned long long> h (t.length());
    for (size_t i=0; i<t.length(); ++i){
        if (isupper(t[i]))h[i] = (t[i] - 'A' + 1) * p_pow[i];
        else h[i] = (t[i] - 'a' + 1) * p_pow[i];
        if (i)  h[i] += h[i-1];
    }

    unsigned long long h_s = 0;
    for (size_t i=0; i<s.length(); ++i)
        if (isupper(s[i])) h_s += (s[i] - 'A' + 1) * p_pow[i];
        else  h_s += (s[i] - 'a' + 1) * p_pow[i];

    bool k = false;
    for (size_t i = 0; i + s.length() - 1 < t.length(); ++i){
        unsigned long long cur_h = h[i+s.length()-1];
        if (i)  cur_h -= h[i-1];
        if (cur_h == h_s * p_pow[i]){
            bool f = true;
            for (int j = 0; j <s.length() ; ++j) {
                if (s[j]!=t[i+j]) {
                    f = false;
                    break;
                }
                if (j>2500)break;
            }
            if (f){
                k=true;
                cout << i << ' ';
            }
        }
    }
    if (!k)cout<<-1;

    return 0;
}