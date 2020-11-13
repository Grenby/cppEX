#ifndef UNTITLED_TREES_H
#define UNTITLED_TREES_H
#include <vector>


template <typename T>
class AbstractTree{
public:
    virtual void insert(const T& key);
    virtual bool find(const T& key);
    virtual void erase(const T& key);
    virtual void clear();
    virtual std::vector<T> dump();
};

template <typename T>
struct node {
    T key;
    node* left = nullptr;
    node* right = nullptr;
    node* parent = nullptr;
    unsigned char param = 1;
    explicit node(T  k):key(std::move(k)) {}
};



template <typename T>
class BinaryTree:public AbstractTree<T>{

protected:
    node<T>* root = nullptr;

    virtual node<T>* rotateLeft(node<T> *n);
    virtual node<T>* rotateRight(node<T> *n);
    virtual node<T>* remove(node<T>*n, const T& key);
    node<T>* findNode(const T& key);
    virtual node<T>* insertNode(node<T> *_root, node<T> *n);
    virtual node<T>* findMinNode(node<T> *n);
    virtual node<T>* findMaxNode(node<T> *n);

    void cl();

public:

    BinaryTree() = default;
    explicit BinaryTree(const std::vector<T>& args);

    ~BinaryTree();

    void insert(const T& key) override;
    bool find(const T& key) override;
    void erase(const T& key) override;
    std::vector<T> dump() override;
    void clear() override;
};


template <typename T>
class RedBackTree : public BinaryTree<T> {
private:
protected:
    const unsigned char BLACK = 1;
    const unsigned char RED = 0;

    char getColor(node<T>* n);
    void setColor(node<T>* n, unsigned char color);
    bool hasRedChild(node<T>*n);
    bool isOnLeft(node<T>*n);
    node<T>* getSibling(node<T>* n);
    node<T> *getN(node<T> *n);

    void fixInsertRBTree(node<T>* n);
    void fixDeleteRBTree(node<T> *n);
    node<T>* rotateLeft(node<T>* p) override;
    node<T> *rotateRight(node<T>* ptr) override;
    node<T> *remove(node<T>* r, const T &data) override;
    void in(const T& key);

public:
    RedBackTree()= default;
    explicit RedBackTree(const std::vector<T>& args):BinaryTree<T>(args)
    {
        for (const auto& x:args)
            in(x);
    }

    void insert(const T &key) override ;
    void erase(const T &key) override;
};


template <typename T>
class AVLTree : public BinaryTree<T> {
private:

    unsigned char height(node<T>* p);
    int bFactor(node<T>* p);
    void fixHeight(node<T>* p);
    node<T>* balance(node<T>* p);
    node<T>* insert(node<T>* p, const T &k);
    node<T>* rotateRight(node<T>* p)override;
    node<T>* rotateLeft(node<T>* q)override;
    node<T>* removeMin(node<T>* p);
    node<T>* remove(node<T>* p, const T& k);
    void in(const T& key);

public:

    AVLTree() = default;
    explicit AVLTree(const std::vector<T>& args): BinaryTree<T>(args){
        for (const auto& x:args)
            this->in(x);
    }

    void insert(const T &key) override;
    void erase(const T &key) override ;
};


#endif //UNTITLED_TREES_H
