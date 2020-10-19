#include <string>
#include <iostream>
#include <vector>
class Checker {
private:

    static const unsigned long long size = 1<<20;
    static const unsigned long long size1 = (size<<3)-8;

    static const unsigned char bitIndex = 7;

    std::vector<unsigned char> E={1,2,4,8,16,32,64,128};

    unsigned char ss[size]{0};

    static unsigned long long hh(const std::string& s){
        unsigned long long hash =0;
        for (char c : s)hash= hash*31+c;
        return hash;
    }

    static inline unsigned long long id (unsigned long long h){ return (h&size1)>>3;}

public:

    Checker()= default;

    void Add(const std::string& s){
        unsigned long long h = hh(s);
        unsigned char t = h & bitIndex;
        for (char i=0;i<8;i++)if (t==i)ss[id(h)]|=E[i];
    };

    bool Exists(const std::string& s){
        unsigned long long h = hh(s);
        unsigned char t = h & bitIndex;
        for (char i=0;i<8;i++)if (t==i)return ss[id(h)]&E[i];
        return false;
    }
};


int main(){
    Checker s{};
    //std::cout<< sizeof(s);
    std::string s1 = "123";
    s.Add(s1);
    std::cout<<s.Exists(s1+"1");

    return 0;
}