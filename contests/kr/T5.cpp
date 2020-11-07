#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string t;
    cin >> t;

    const int p = 67;
    vector<unsigned long long> p_pow (t.length());
    p_pow[0] = 1;
    for (size_t i=1; i<p_pow.size(); ++i)
        p_pow[i] = p_pow[i-1] * p;

    vector<unsigned long long> h (t.length());
    for (size_t i=0; i<t.length(); ++i){
        h[i] = (t[i] - 'A' + 1) * p_pow[i];
        if (i)  h[i] += h[i-1];
    }

    if (t.length() < 10)
        return 0;

    bool k = false;
    for (size_t j = 0; j +10 < t.length();++j) {
        unsigned long long h_s = 0;
        for (size_t i=0; i<10; ++i)
            h_s += (t[i+j] - 'A' + 1) * p_pow[i];

        for (size_t i = j+10; i+10 < t.length(); ++i){
            unsigned long long cur_h = h[i+10];
            if (i)  cur_h -= h[i];
            if (cur_h == h_s * p_pow[i]){
                bool f = true;
                for (int kk = 0; kk <10 ; ++kk) {
                    if (t[j+kk]!=t[i+j]) {
                        f = false;
                        break;
                    }
                }
                if (f){
                    k=true;
                    for( int kk=0;kk<10;kk++)cout << t[j+kk];
                    cout<<'\n';
                }
            }
        }
    }
    if (!k)cout<<-1;

    return 0;
}
