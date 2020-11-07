
template <typename T>
class AbstractTree{
public:
    virtual ~AbstractTree(){};

    virtual T& insert(T& n){};

    virtual bool find(const T& n){};

    virtual T& erase(const T& n){};
};

template <typename T>
class RedBackTree :AbstractTree<T>{
private:
public:
    ~RedBackTree() override {

    }

    T &insert(T &n) override {
        return n;
    }

    bool find(const T &n) override {
        return false;
    }

    T &erase(const T &n) override {
        return n;
    }

};

template <typename T>
class AVLTree : AbstractTree<T> {
private:

public:
    ~AVLTree() override {

    }

    T &insert(T &n) override {
        return n;
    }

    bool find(const T &n) override {
        return false;
    }

    T &erase(const T &n) override {
        return n;
    }

};

int main(){
    return 0;
}