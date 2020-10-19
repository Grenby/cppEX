#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>


//______________________________________________________________________________________________________________________
#include <bitset>
class Checker {
private:

    unsigned long long h1(const std::string& s){
        unsigned long long hash =0;
        for (char c : s)hash= hash*191+c;
        return hash;
    }

    unsigned long long h2(const std::string& s){
        unsigned long long hash =0;
        for (char c : s)hash= hash*31+c;
        return hash;
    }

    unsigned long long h3(const std::string& s){
        unsigned long long hash =0;
        for (char c : s)hash= hash*67+c;
        return hash;
    }

    unsigned long long h4(const std::string& s){
        unsigned long long hash =0;
        for (char c : s)hash= hash*131+c;
        return hash;
    }


public:
    static const unsigned long long size = 10 * 1024 * 1024 * 2;
    std::bitset<size> set1;
    std::bitset<size> set2;
    std::bitset<size> set3;
    std::bitset<size> set4;

    Checker(){
        for (int i = 0; i <size ; ++i){
            set1[i]=false;
            set2[i]=false;
            set3[i]=false;
            set4[i]=false;
        }
    }

    void Add(const std::string& s){
        set1[h1(s) % size] = true;
        set2[h2(s) % size] = true;
        set3[h3(s) % size] = true;
        set4[h4(s) % size] = true;
    };

    bool Exists(const std::string& s){
        return set1[h1(s) % size] && set2[h2(s) % size] && set3[h3(s) % size] && set4[h4(s) % size];
    }
};
//______________________________________________________________________________________________________________________

std::string gen_random(const int len) {

    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.resize(len);
    for (int i = 0; i < len; ++i)tmp_s[i]=alphanum[rand() % (sizeof(alphanum) - 1)];
    return tmp_s;

}

void printProgress(const int i, const int of){
    if (i% (of/100) ==0 )std::cout <<100.*(double) i / (of) << "%\n";
}

int main(){

    auto s = new Checker();

    const unsigned long long NUM_STRING = 75000;
    const unsigned long long NUM_TEST = NUM_STRING;
    const int LEN_STRING = 1000;

    std::cout<<"add\n";
    std:: unordered_set<std::string> set;

    unsigned long long alreadyContain = 0;
    unsigned long long error = 0;
    for(unsigned long long i=0; i < NUM_STRING; i++){
        printProgress(i,NUM_STRING);

        std::string str = gen_random(rand() % LEN_STRING + 1);

        if (set.find(str)==set.end()){
            set.insert(str);
            if (s->Exists(str)){
                alreadyContain++;
                error++;
            }
            else s->Add(str);
        }
    }

    std::cout<<"check\n";
    for(unsigned long long i=0; i < NUM_TEST; i++){
        printProgress(i,NUM_TEST);

        std::string str = gen_random(rand() % LEN_STRING + 1);
        if ((set.find(str) == set.end()) & s->Exists(str))error++;
        if ((set.find(str) != set.end()) & !s->Exists(str))error++;
    }

    std::cout<<"size of Checker = "<< sizeof(*s)/(1024.*1024.)<<"Mb ("<< (s->size)/(1024.*1024. * 8.)<<"Mb)";
    std::cout << "\nresult:\nerrors = " << error << " of "<<NUM_TEST <<" (" << 100.*(double)error/(NUM_TEST) << "%)\n";
    std::cout<<"rehash = "<<alreadyContain <<" of "<<NUM_STRING<<" ("<<100.*(double)alreadyContain/(NUM_TEST)<<"%)\n";
    error = 0;
    std::vector<unsigned char> E={1,2,4,8,16,32,64,128};

//    for (unsigned long long i = 0; i < s->size; ++i) {
//        if ((s->set[i]))error++;
//    }
//    std::cout<<"fullness = " << 100*(double)error/(double)(s->size)<<"% (of " <<100.*NUM_STRING/(double)(s->size)<<"%)";
    return 0;
}