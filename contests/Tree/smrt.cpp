#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class S1{
protected:
    T a=2;
public:
    void vA(){
        cout<<"void A";
    }
};

template <typename T>
class S2:S1<T>{
public:
    void p(){

    }
};

template <typename T>
class S3:public S1<T>{
public:
    void p(){
    }
};

int main(){
    S3<int> s3;
    S2<int> s2;
    s2.p();
    s3.p();
    s3.vA();

    return 0;
}