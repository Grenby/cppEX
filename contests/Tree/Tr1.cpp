#include <deque>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <set>
#include <random>

template <typename T>
class AbstractTree{
public:
    virtual void insert(const T& key){
        std::cout<<"You're doing something right:)"<<std::endl;
    };

    virtual bool find(const T& key){
        std::cout<<"You're doing something right:)"<<std::endl;
        return false;
    };

    virtual void erase(const T& key){
        std::cout<<"You're doing something right:)"<<std::endl;
    };

    virtual void clear(){
        std::cout<<"You're doing something right:)"<<std::endl;
    };

    virtual std::vector<T> dump(){
        std::cout<<"You're doing something right:)"<<std::endl;
        return std::vector<T>{};
    }
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

    virtual node<T>* rotateLeft(node<T> *n){
        //TODO
        return nullptr;
    };
    virtual node<T>* rotateRight(node<T> *n){
        //TODO
        return nullptr;
    };
    virtual node<T>* remove(node<T>*n, const T& key){
        return nullptr;
    };

    node<T>* findNode(const T& key);
    virtual node<T>* insertNode(node<T> *_root, node<T> *n);
    virtual node<T>* findMinNode(node<T> *n);
    virtual node<T>* findMaxNode(node<T> *n);

    void cl(){
        clear();
    }

public:

    BinaryTree()= default;

    explicit BinaryTree(const std::vector<T>& args){
    }

    ~BinaryTree(){
        cl();
    }

    void insert(const T& key) override{
        //TODO something
    }

    bool find(const T& key) override{
        return findNode(key);
    }

    void erase(const T& key) override{
        //TODO something
    }

    std::vector<T> dump() override;

    void clear() override;
};

template<typename T>
node<T>* BinaryTree<T>::findNode(const T &key) {
    node<T>* p = root;
    while (p) {
        if (p->key < key)p = p->right;
        else if (key < p->key)p = p->left;
        else return p;
    }
    return nullptr;
}

template<typename T>
node<T> *BinaryTree<T>::insertNode(node<T> *_root, node<T> *n) {
    if (_root == nullptr)
        return n;
    if (n->key < _root->key) {
        _root->left = insertNode(_root->left, n);
        _root->left->parent = _root;
    } else if (_root->key < n->key) {
        _root->right = insertNode(_root->right, n);
        _root->right->parent = _root;
    }
    return _root;
}

template<typename T>
node<T> *BinaryTree<T>::findMinNode(node<T> *n) {
    node<T> *ptr = n;
    while (ptr->left != nullptr)
        ptr = ptr->left;
    return ptr;
}

template<typename T>
node<T> *BinaryTree<T>::findMaxNode(node<T> *n) {
    node<T> *ptr = n;
    while (ptr->right != nullptr)
        ptr = ptr->right;
    return ptr;
}

template<typename T>
std::vector<T> BinaryTree<T>::dump() {
    std::deque<node<T>*> q;
    std::vector<T> v;
    q.push_back(root);
    while (!q.empty()) {
        node<T>* p = q.front();
        if (p->left)q.push_back(p->left);
        if (p->right)q.push_back(p->right);
        v.push_back(p->key);
        q.pop_front();
    }
    return v;
}

template<typename T>
void BinaryTree<T>::clear() {
    if (!root)return;
    std::deque<node<T>*> q;
    q.push_back(root);
    while (!q.empty()) {
        node<T>* p = q.front();
        if (p->left)q.push_back(p->left);
        if (p->right)q.push_back(p->right);
        delete p;
        q.pop_front();
    }
}



template <typename T>
class RedBackTree : public BinaryTree<T> {
private:
    protected:
    const unsigned char BLACK = 1;
    const unsigned char RED = 0;
    const unsigned char DOUBLE_BLACK = 2;

    char getColor(node<T>* n) {
        if (!n)
            return BLACK;
        return n->param;
    }

    void setColor(node<T>* n, unsigned char color) {
        if (!n)
            return;
        n->param = color;
    }

    bool hasRedChild(node<T>*n) {
        return (n->left != nullptr && getColor(n->left) == RED) ||
               (n->right != nullptr && getColor(n->right) == RED);
    }

    bool isOnLeft(node<T>*n) { return n == n->parent->left; }

    node<T>* getSibling(node<T>* n){
        if (n->parent == nullptr)
            return nullptr;
        if (isOnLeft(n))
            return n->parent->right;
        return n->parent->left;
    }

    node<T> *getN(node<T> *n) {
        if (n->left != nullptr && n->right != nullptr)
            return this->findMinNode(n->right);
        if (n->left == nullptr && n->right == nullptr)
            return nullptr;
        if (n->left != nullptr)
            return n->left;
        else
            return n->right;
    }

    void fixInsertRBTree(node<T>* n) {
        node<T> *parent = nullptr;
        node<T> *grandparent = nullptr;
        while (n != this->root && getColor(n) == RED && getColor(n->parent) == RED) {
            parent = n->parent;
            grandparent = parent->parent;
            if (parent == grandparent->left) {
                node<T> *uncle = grandparent->right;
                if (getColor(uncle) == RED) {
                    setColor(uncle, BLACK);
                    setColor(parent, BLACK);
                    setColor(grandparent, RED);
                    n = grandparent;
                } else {
                    if (n == parent->right) {
                        rotateLeft(parent);
                        n = parent;
                        parent = n->parent;
                    }
                    rotateRight(grandparent);
                    std::swap(parent->param, grandparent->param);
                    n = parent;
                }
            } else {
                node<T> *uncle = grandparent->left;
                if (getColor(uncle) == RED) {
                    setColor(uncle, BLACK);
                    setColor(parent, BLACK);
                    setColor(grandparent, RED);
                    n = grandparent;
                } else {
                    if (n == parent->left) {
                        rotateRight(parent);
                        n = parent;
                        parent = n->parent;
                    }
                    rotateLeft(grandparent);
                    std::swap(parent->param, grandparent->param);
                    n = parent;
                }
            }
        }
        setColor(this->root, BLACK);
    }

    void fixDeleteRBTree(node<T> *n) {
        if (n == this->root)
            return;
        node<T> *sibling = getSibling(n), *parent = n->parent;
        if (sibling == nullptr){
            fixDeleteRBTree(parent);
        }else{
            if (getColor(sibling) == RED) {
                setColor(parent,RED);
                setColor(sibling,BLACK);
                if (isOnLeft(sibling)) {
                    rotateRight(parent);
                } else {
                    rotateLeft(parent);
                }
                fixDeleteRBTree(n);
            } else {
                if (hasRedChild(sibling)) {
                    if (sibling->left != nullptr && getColor(sibling->left) == RED) {
                        if (isOnLeft(sibling)) {
                            setColor(sibling->left,getColor(sibling));
                            setColor(sibling,getColor(parent));
                            rotateRight(parent);
                        } else {
                            setColor(sibling->left,getColor(parent));
                            rotateRight(sibling);
                            rotateLeft(parent);
                        }
                    } else {
                        if (isOnLeft(sibling)) {
                            setColor(sibling->right,getColor(parent));
                            rotateLeft(sibling);
                            rotateRight(parent);
                        } else {
                            setColor(sibling->right, getColor(sibling));
                            setColor(sibling, getColor(parent));
                            rotateLeft(parent);
                        }
                    }
                    setColor(parent, BLACK);
                } else {
                    setColor(sibling, RED);
                    if (getColor(parent) == BLACK)
                        fixDeleteRBTree(parent);
                    else
                        setColor(parent, BLACK);
                }
            }
        }
    }

    node<T>* rotateLeft(node<T>* p) override {
        node<T> *right_child = p->right;
        p->right = right_child->left;

        if (p->right != nullptr)
            p->right->parent = p;

        right_child->parent = p->parent;

        if (p->parent == nullptr)
            this->root = right_child;
        else if (p == p->parent->left)
            p->parent->left = right_child;
        else
            p->parent->right = right_child;

        right_child->left = p;
        p->parent = right_child;
        return nullptr;
    }

    node<T> *rotateRight(node<T>* ptr) override {
        node<T> *left_child = ptr->left;
        ptr->left = left_child->right;

        if (ptr->left != nullptr)
            ptr->left->parent = ptr;

        left_child->parent = ptr->parent;

        if (ptr->parent == nullptr)
            this->root = left_child;
        else if (ptr == ptr->parent->left)
            ptr->parent->left = left_child;
        else
            ptr->parent->right = left_child;

        left_child->right = ptr;
        ptr->parent = left_child;
        return nullptr;
    }

    node<T> *remove(node<T>* r, const T &data) override {
        node<T> * v =this->findNode(data);
        if (v == nullptr)
            return nullptr;
        node<T> *u = getN(v);
        bool uvBlack = ((u == nullptr || getColor(u) == BLACK) && (getColor(v) == BLACK));
        node<T> *parent = v->parent;
        if (u == nullptr) {
            if (v == this->root) {
                this->root = nullptr;
            }else {
                if (uvBlack){
                    fixDeleteRBTree(v);
                }else {
                    if (getSibling(v) != nullptr) {
                        setColor(getSibling(v), RED);
                    }
                }
                if (isOnLeft(v))parent->left = nullptr;
                else parent->right = nullptr;
            }
            delete v;
        }
        return nullptr;
    }

    void in(const T& key){
        insert(key);
    }

public:
    RedBackTree()= default;
    explicit RedBackTree(const std::vector<T>& args):BinaryTree<T>(args)
    {
        for (const auto& x:args)
            in(x);
    }

    void insert(const T &key) override {
        auto *n = new node<T>(key);
        n->param = RED;
        this->root = this->insertNode(this->root, n);
        fixInsertRBTree(n);
    }

    void erase(const T &key) override {
        remove(this->root,key);
    };
};

template <typename T>
class AVLTree : public BinaryTree<T> {
private:

    unsigned char height(node<T>* p){
        return p ? p->param : 0;
    }

    int bFactor(node<T>* p){
        return height(p->right)-height(p->left);
    }

    void fixHeight(node<T>* p){
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        p->param = (hl > hr ? hl : hr) + 1;
    }

    node<T>* balance(node<T>* p) {
        fixHeight(p);
        if(bFactor(p) == 2 ){
            if(bFactor(p->right) < 0 )
                p->right = rotateRight(p->right);
            return rotateLeft(p);
        }
        if(bFactor(p) == -2 ){
            if(bFactor(p->left) > 0  )
                p->left = rotateLeft(p->left);
            return rotateRight(p);
        }
        return p;
    }

    node<T>* insert(node<T>* p, const T &k){
        if( !p ) return new node<T>(k);
        if (k<p->key)
            p->left = insert(p->left,k);
        else if(p->key<k)
            p->right = insert(p->right,k);
        return balance(p);
    }

    node<T>* rotateRight(node<T>* p)override {
        node<T>* q = p->left;
        p->left = q->right;
        q->right = p;
        fixHeight(p);
        fixHeight(q);
        return q;
    }

    node<T>* rotateLeft(node<T>* q)override {
        node<T>* p = q->right;
        q->right = p->left;
        p->left = q;
        fixHeight(q);
        fixHeight(p);
        return p;
    }

    node<T>* removeMin(node<T>* p){
        if( p->left== nullptr )
            return p->right;
        p->left = removeMin(p->left);
        return balance(p);
    }

    node<T>* remove(node<T>* p, const T& k)override {
        if( !p ) return nullptr;
        if( k < p->key )p->left = remove(p->left,k);
        else if( p->key < k)p->right = remove(p->right,k);
        else{
            node<T>* q = p->left;
            node<T>* r = p->right;
            delete p;
            if (!r) return q;
            node<T>* min = this->findMinNode(r);
            min->right = removeMin(r);
            min->left = q;
            return min;
        }
        return p;
    }

    void in(const T& key){
        insert(key);
    }

public:

    AVLTree() = default;

    explicit AVLTree(const std::vector<T>& args){
        for (const auto& x:args)
            this->in(x);
    }

    void insert(const T &key) override {
        this->root = insert(this->root, key);
    }

    void erase(const T &key) override {
        this->root = remove(this->root, key);
    }

};


int profileInitTree(AbstractTree<int> &tree)
{
    std::stringstream ss;
    for (int i = 0; i <12 ; ++i)
        ss<<tree.find(i);
    return (ss.str() == "011100000000" );
}

int profileInitTree(AbstractTree<std::string> &tree)
{
    std::stringstream ss;
    for (int i = 0; i <12 ; ++i)
        ss<<tree.find(std::to_string(i));
    return (ss.str() == "000100000000" );
}

int profileInitTree(AbstractTree<std::vector<int>> &tree)
{
    std::stringstream ss;
    for (int i = 0; i < 12; i++)
        ss<<tree.find(std::vector<int>(1,i));
    return (ss.str() == "010000000000" );
}

double get_time()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}

int randInt(int min, int max)
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}


void t(const int NUM){
    std::cout<<NUM<<'\n';

    std::vector<int> numbers(NUM);

    AVLTree<int> avl;
    RedBackTree<int> rb;
    std::set<int> s;

    double time =0.0;
    bool correct = true;

    //step 1 : insert
    {
        for (int i = 0; i < NUM; ++i)numbers[i] = randInt(-NUM, NUM);

        std::cout << "insert\n";
        time = get_time();
        for (int i = 0; i < NUM; ++i)avl.insert(numbers[i]);
        std::cout << "AVL: " << get_time() - time << "\n";

        time = get_time();
        for (int i = 0; i < NUM; ++i)rb.insert(numbers[i]);
        std::cout << "RB: " << get_time() - time << "\n";

        time = get_time();
        for (int i = 0; i < NUM; ++i)s.insert(numbers[i]);
        std::cout << "sdt::set " << get_time() - time << "\n";
    }
    //step 2 : find
    {
        for (int i = 0; i < NUM; ++i)numbers[i] = randInt(-NUM, NUM);

        std::cout << "\nfind\n";
        time = get_time();
        for (int i = 0; i < NUM; ++i)avl.find(numbers[i]);
        std::cout << "AVL: " << get_time() - time << "\n";

        time = get_time();
        for (int i = 0; i < NUM; ++i)rb.find(numbers[i]);
        std::cout << "RB: " << get_time() - time << "\n";

        time = get_time();
        for (int i = 0; i < NUM; ++i)s.find(numbers[i]);
        std::cout << "sdt::set: " << get_time() - time << "\n";

        correct = true;
        for (int i = 0; i < NUM; ++i) {
            int value = randInt(-NUM, NUM);
            bool find = s.find(value) != s.end();
            if (find != rb.find(value) || find != avl.find(value)) {
                correct = false;
                std::cout << "Finding is incorrect\n";
                break;
            }
        }
        if (correct)
            std::cout << "All findings are correct\n\n";
    }
    //step 3 : erase
    {
        for (int i = 0; i < NUM; ++i)numbers[i] = randInt(-NUM, NUM);

        std::cout << "erase\n";
        time = get_time();
        for (int i = 0; i < NUM; ++i)avl.erase(numbers[i]);
        std::cout << "AVL: " << get_time() - time << "\n";

        time = get_time();
        for (int i = 0; i < NUM; ++i)rb.erase(numbers[i]);
        std::cout << "RB: " << get_time() - time << "\n";

        time = get_time();
        for (int i = 0; i < NUM; ++i)s.erase(numbers[i]);
        std::cout << "sdt::set: " << get_time() - time << "\n";

        correct = true;
        for (const auto &x : s) {
            if (!avl.find(x) || !rb.find(x)) {
                std::cout << "erase is incorrect";
                correct = false;
                break;
            }
        }
        if (correct) {
            std::cout << "All erasings are correct\n\n";
        } else std::cout << "\n\n";
    }
}

int main(){
    t(100);
    t(100000);
    t(10000000);


    std::vector<int> tst = {1,2,3};
    AVLTree<int> tree1a(tst);
    RedBackTree<int> tree1k(tst);
    AVLTree<std::string> tree2a({"a","b","3"});
    RedBackTree<std::string> tree2k({"a","b","3"});
    AVLTree<std::vector<int>> tree3a({{1},{1,2},{2,2}});
    RedBackTree<std::vector<int>> tree3k({{1},{1,2},{2,2}});
    if(profileInitTree(tree1a)) std::cout << "AVLTree int init passed!" << std::endl;
    else std::cout << "!!!!!WARNING!!!!! AVLTree int init didn't pass! ---------" << std::endl;
    if(profileInitTree(tree1k)) std::cout << "RBTree int init passed!" << std::endl;
    else std::cout << "!!!!!WARNING!!!!! RBTree int init didn't pass! ---------" << std::endl;
    if(profileInitTree(tree2a)) std::cout << "AVLTree string init passed!" << std::endl;
    else std::cout << "!!!!!WARNING!!!!! AVLTree string init didn't pass! ---------" << std::endl;
    if(profileInitTree(tree2k)) std::cout << "RBTree string init passed!" << std::endl;
    else std::cout << "!!!!!WARNING!!!!! RBTree string init didn't pass! ---------" << std::endl;
    if(profileInitTree(tree3a)) std::cout << "AVLTree someshi.. vector<int> init passed!" << std::endl;
    else std::cout << "!!!!!WARNING!!!!! AVLTree has seen some shit ---------" << std::endl;
    if(profileInitTree(tree3k)) std::cout << "RBTree someshi.. vector<int> init passed!" << std::endl;
    else std::cout << "!!!!!WARNING!!!!! RBTree has seen some shit ---------" << std::endl;

    return 0;
}