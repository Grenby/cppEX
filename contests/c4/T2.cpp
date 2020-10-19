#include <cstdint>
#include <iostream>

using namespace std;

class Fraction {
public:
    uint64_t denominator;
    int64_t numerator;
private:
    // Do NOT rename

    // Do NOT delete
    template < class T >
    friend bool operator==(const Fraction& lhs, const T& rhs);

    int64_t gcd (uint64_t a, uint64_t b) {
        return b ? gcd (b, a % b) : a;
    }

    void toPrime(){
        if(numerator==0)denominator=1;
        if (numerator==0 || numerator==1||numerator==-1||denominator==0||denominator==1)return;
        int64_t a = gcd((uint64_t)(numerator > 0 ? numerator:-numerator),denominator);
        denominator /= a;
        numerator /= a;
    }

public:
    Fraction() = delete;

    Fraction(const Fraction& rhs){
        numerator=rhs.numerator;
        denominator=rhs.denominator;
    }

    Fraction& operator = (const Fraction& rhs){
        this->numerator=rhs.numerator;
        this->denominator=rhs.denominator;
        return * this;
    }

    Fraction(int64_t numerator, uint64_t denominator){
        this->numerator=numerator;
        this->denominator=denominator;
        toPrime();
    }
    //  Add operator overloads below

    Fraction& operator -(){return *new Fraction(-numerator,denominator);}

    Fraction& operator -(const Fraction& rhs){
        int64_t g1 = gcd(denominator,rhs.denominator);
        int64_t g2 = gcd(numerator>0?numerator:-numerator,rhs.numerator>0?rhs.numerator:-rhs.numerator);
        g2=g2==0?1:g2;
        g1=g1==0?1:g1;
        Fraction f1 (numerator/g2,denominator/g1);
        Fraction f2 (rhs.numerator/g2,rhs.denominator/g1);
        Fraction f(f1.numerator*f2.denominator-f2.numerator*f1.denominator,f1.denominator*f2.denominator);
        f.numerator*=g2;
        f.denominator*=g1;
        f.toPrime();
        return *new Fraction(f);
    }

    Fraction& operator +(const Fraction& rhs){
        int64_t g1 = gcd(denominator,rhs.denominator);
        int64_t g2 = gcd(numerator>0?numerator:-numerator,rhs.numerator>0?rhs.numerator:-rhs.numerator);
        g2=g2==0?1:g2;
        g1=g1==0?1:g1;
        Fraction f1 (numerator/g2,denominator/g1);
        Fraction f2 (rhs.numerator/g2,rhs.denominator/g1);
        Fraction f(f1.numerator*f2.denominator+f2.numerator*f1.denominator,f1.denominator*f2.denominator);
        f.numerator*=g2;
        f.denominator*=g1;
        f.toPrime();
        return *new Fraction(f);
    }

    Fraction& operator *(const Fraction& rhs){
        Fraction f1(numerator,rhs.denominator);
        Fraction f2(rhs.numerator,denominator);
        return *new Fraction(f1.numerator*f2.numerator,f1.denominator*f2.denominator);
    }

    Fraction& operator +=(const Fraction& rhs){
        int64_t g1 = gcd(denominator,rhs.denominator);
        int64_t g2 = gcd(numerator>0?numerator:-numerator,rhs.numerator>0?rhs.numerator:-rhs.numerator);
        g2=g2==0?1:g2;
        g1=g1==0?1:g1;
        Fraction f1 (numerator/g2,denominator/g1);
        Fraction f2 (rhs.numerator/g2,rhs.denominator/g1);
        Fraction f(f1.numerator*f2.denominator+f2.numerator*f1.denominator,f1.denominator*f2.denominator);
        f.numerator*=g2;
        f.denominator*=g1;
        f.toPrime();
        this->numerator=f.numerator;
        this->denominator=f.denominator;
        return *this;
    }

    Fraction& operator -=(const Fraction& rhs){
        int64_t g1 = gcd(denominator,rhs.denominator);
        int64_t g2 = gcd(numerator>0?numerator:-numerator,rhs.numerator>0?rhs.numerator:-rhs.numerator);
        g2=g2==0?1:g2;
        g1=g1==0?1:g1;
        Fraction f1 (numerator/g2,denominator/g1);
        Fraction f2 (rhs.numerator/g2,rhs.denominator/g1);
        Fraction f(f1.numerator*f2.denominator-f2.numerator*f1.denominator,f1.denominator*f2.denominator);
        f.numerator*=g2;
        f.denominator*=g1;
        f.toPrime();
        this->numerator=f.numerator;
        this->denominator=f.denominator;
        return *this;
    }

    Fraction& operator *=(const Fraction& rhs){
        Fraction f1(numerator,rhs.denominator);
        Fraction f2(rhs.numerator,denominator);
        numerator = f1.numerator*f2.numerator;
        denominator = f1.denominator*f2.denominator;
        return *this;
    }
};

int main(){
    Fraction * d = new Fraction(1,1);
    *d=-(*d);
    cout<<d->numerator;
    Fraction a(-2,3);
    Fraction c(2,8);
    a*=c;
    //cout<<a.numerator<<" ";
    //cout<<a.denominator;
    return 0;
}