#include <deque>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
template <typename T>
class AbstractTree{
public:
    AbstractTree()
    {}
    AbstractTree(std::vector<T> args)
    {
        this->initVect = args;
    }
    virtual void insert(const T& key){};
    virtual bool find(const T& key){
        return true;
    };
    virtual void erase(const T& key){};
    virtual std::vector<T> dump(){ return std::vector<T>{};};
protected:
    std::vector<T> initVect;
};

template <typename T>
class RedBackTree:public AbstractTree<T> {
private:

    struct node {
        T key;
        node *parent = nullptr;
        node *left = nullptr;
        node *right = nullptr;
        char param =0;

        explicit node(const T &key) : key(key){}
    };

    const char BLACK = 1;
    const char RED = 0;
    const char DOUBLE_BLACK = 2;
    node *root = nullptr;

    char getColor(node* n) {
        if (!n)
            return BLACK;
        return n->param;
    }

    void setColor(node* n, char color) {
        if (!n)
            return;
        n->param = color;
    }

    node *insertBST(node* to,node*  ptr) {
        if (to == nullptr)
            return ptr;
        if (ptr->key < to->key) {
            to->left = insertBST(to->left, ptr);
            to->left->parent = to;
        } else if (ptr->key > to->key) {
            to->right = insertBST(to->right, ptr);
            to->right->parent = to;
        }
        return to;
    }

    void rotateLeft(node* ptr) {
        node *right_child = ptr->right;
        ptr->right = right_child->left;

        if (ptr->right != nullptr)
            ptr->right->parent = ptr;

        right_child->parent = ptr->parent;

        if (ptr->parent == nullptr)
            root = right_child;
        else if (ptr == ptr->parent->left)
            ptr->parent->left = right_child;
        else
            ptr->parent->right = right_child;

        right_child->left = ptr;
        ptr->parent = right_child;
    }

    void rotateRight(node* ptr) {
        node *left_child = ptr->left;
        ptr->left = left_child->right;

        if (ptr->left != nullptr)
            ptr->left->parent = ptr;

        left_child->parent = ptr->parent;

        if (ptr->parent == nullptr)
            root = left_child;
        else if (ptr == ptr->parent->left)
            ptr->parent->left = left_child;
        else
            ptr->parent->right = left_child;

        left_child->right = ptr;
        ptr->parent = left_child;
    }

    void fixInsertRBTree(node* ptr) {
        node *parent = nullptr;
        node *grandparent = nullptr;
        while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
            parent = ptr->parent;
            grandparent = parent->parent;
            if (parent == grandparent->left) {
                node *uncle = grandparent->right;
                if (getColor(uncle) == RED) {
                    setColor(uncle, BLACK);
                    setColor(parent, BLACK);
                    setColor(grandparent, RED);
                    ptr = grandparent;
                } else {
                    if (ptr == parent->right) {
                        rotateLeft(parent);
                        ptr = parent;
                        parent = ptr->parent;
                    }
                    rotateRight(grandparent);
                    std::swap(parent->param, grandparent->param);
                    ptr = parent;
                }
            } else {
                node *uncle = grandparent->left;
                if (getColor(uncle) == RED) {
                    setColor(uncle, BLACK);
                    setColor(parent, BLACK);
                    setColor(grandparent, RED);
                    ptr = grandparent;
                } else {
                    if (ptr == parent->left) {
                        rotateRight(parent);
                        ptr = parent;
                        parent = ptr->parent;
                    }
                    rotateLeft(grandparent);
                    std::swap(parent->param, grandparent->param);
                    ptr = parent;
                }
            }
        }
        setColor(root, BLACK);
    }

    void fixDeleteRBTree(node* n) {
        if (!n)
            return;

        if (n == root) {
            root = nullptr;
            return;
        }

        if (getColor(n) == RED || getColor(n->left) == RED || getColor(n->right) == RED) {
            node *child = n->left != nullptr ? n->left : n->right;

            if (n == n->parent->left) {
                n->parent->left = child;
                if (child != nullptr)
                    child->parent = n->parent;
                setColor(child, BLACK);
                delete (n);
            } else {
                n->parent->right = child;
                if (child != nullptr)
                    child->parent = n->parent;
                setColor(child, BLACK);
                delete (n);
            }
        } else {
            node *sibling = nullptr;
            node *parent = nullptr;
            node *ptr = n;
            setColor(ptr, DOUBLE_BLACK);
            while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
                parent = ptr->parent;
                if (ptr == parent->left) {
                    sibling = parent->right;
                    if (getColor(sibling) == RED) {
                        setColor(sibling, BLACK);
                        setColor(parent, RED);
                        rotateLeft(parent);
                    } else {
                        if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                            setColor(sibling, RED);
                            if (getColor(parent) == RED)
                                setColor(parent, BLACK);
                            else
                                setColor(parent, DOUBLE_BLACK);
                            ptr = parent;
                        } else {
                            if (getColor(sibling->right) == BLACK) {
                                setColor(sibling->left, BLACK);
                                setColor(sibling, RED);
                                rotateRight(sibling);
                                sibling = parent->right;
                            }
                            setColor(sibling, parent->param);
                            setColor(parent, BLACK);
                            setColor(sibling->right, BLACK);
                            rotateLeft(parent);
                            break;
                        }
                    }
                } else {
                    sibling = parent->left;
                    if (getColor(sibling) == RED) {
                        setColor(sibling, BLACK);
                        setColor(parent, RED);
                        rotateRight(parent);
                    } else {
                        if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                            setColor(sibling, RED);
                            if (getColor(parent) == RED)
                                setColor(parent, BLACK);
                            else
                                setColor(parent, DOUBLE_BLACK);
                            ptr = parent;
                        } else {
                            if (getColor(sibling->left) == BLACK) {
                                setColor(sibling->right, BLACK);
                                setColor(sibling, RED);
                                rotateLeft(sibling);
                                sibling = parent->left;
                            }
                            setColor(sibling, parent->param);
                            setColor(parent, BLACK);
                            setColor(sibling->left, BLACK);
                            rotateRight(parent);
                            break;
                        }
                    }
                }
            }
            if (n == n->parent->left)
                n->parent->left = nullptr;
            else
                n->parent->right = nullptr;
            delete (n);
            setColor(root, BLACK);
        }
    }

    node *deleteBST(node* r, const T &data) {
        if (!r)
            return r;
        if (data < r->key)
            return deleteBST(r->left, data);
        if (data > r->key)
            return deleteBST(r->right, data);
        if (r->left == nullptr || r->right == nullptr)
            return r;
        node *tmp = minValueNode(r->right);
        r->key = tmp->key;
        return deleteBST(r->right, tmp->key);
    }

    node *minValueNode(node* n) {
        node *ptr = n;
        while (ptr->left != nullptr)
            ptr = ptr->left;
        return ptr;
    }

public:
    RedBackTree()
    {}
    RedBackTree(std::vector<T> args) : AbstractTree<T>(args)
    {
        for(auto x : this->initVect)
            insert(x);
    }

    ~RedBackTree(){
        if(!root) return;
        std::deque<node*> q;
        q.push_back(root);
        while (!q.empty()) {
            node* p = q.front();
            if (p->left)q.push_back(p->left);
            if (p->right)q.push_back(p->right);
            delete p;
            q.pop_front();
        }
    }

    void insert(const T &key) override {
        node *n = new node(key);
        root = insertBST(root, n);
        fixInsertRBTree(n);
    }

    bool find(const T &key) override {
        node* p = root;
        while (p != nullptr) {
            if (p->key < key)p = p->right;
            else if (key < p->key)p = p->left;
            else return true;
        }
        return false;
    }

    void erase(const T &key) override {
        node *n = deleteBST(root, key);
        fixDeleteRBTree(n);
    };

    std::vector<T> dump()override {
        std::deque<node*> q;
        std::vector<T> v;
        q.push_back(root);
        while (!q.empty()) {
            node* p = q.front();
            if (p->left)q.push_back(p->left);
            if (p->right)q.push_back(p->right);
            v.push_back(p->key);
            q.pop_front();
        }
        return v;
    }
};

template <typename T>
class AVLTree :public AbstractTree<T> {
private:
    struct node {
        T key;
        unsigned char param = 1;
        node* left = nullptr;
        node* right = nullptr;
        explicit node(const T& k):key(k) {}
    };

    node* root = nullptr;

    unsigned char height(node* p){
        return p ? p->param : 0;
    }

    int bFactor(node* p){
        return height(p->right)-height(p->left);
    }

    void fixHeight(node* p){
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        p->param = (hl > hr ? hl : hr) + 1;
    }

    node* rotateRight(node* p){
        node* q = p->left;
        p->left = q->right;
        q->right = p;
        fixHeight(p);
        fixHeight(q);
        return q;
    }

    node* rotateLeft(node* q){
        node* p = q->right;
        q->right = p->left;
        p->left = q;
        fixHeight(q);
        fixHeight(p);
        return p;
    }

    node* balance(node* p) {
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

    node* insert(node* p, const T &k){
        if( !p ) return new node(k);
        if( k < p->key )p->left = insert(p->left,k);
        else p->right = insert(p->right,k);
        return balance(p);
    }

    node* findMin(node* p){
        while (p->left)p=p->left;
        return p;
    }

    node* removeMin(node* p){
        if( p->left== nullptr )
            return p->right;
        p->left = removeMin(p->left);
        return balance(p);
    }

    node* remove(node* p, T k){
        if( !p ) return nullptr;
        if( k < p->key )p->left = remove(p->left,k);
        else if( p->key < k)p->right = remove(p->right,k);
        else{
            node* q = p->left;
            node* r = p->right;
            delete p;
            if (!r) return q;
            node* min = findMin(r);
            min->right = removeMin(r);
            min->left = q;
            return balance(min);
        }
        return balance(p);
    }

public:
    AVLTree()
    {}
    AVLTree(std::vector<T> args) : AbstractTree<T>(args)
    {
        for(auto x : this->initVect)
            insert(x);
    }


    ~AVLTree(){
        if(!root) return;
        std::deque<node*> q;
        q.push_back(root);
        while (!q.empty()) {
            node* p = q.front();
            if (p->left)q.push_back(p->left);
            if (p->right)q.push_back(p->right);
            delete p;
            q.pop_front();
        }
    }

    void insert(const T &n) override {
        root = insert(root, n);
    }

    bool find(const T &n) override {
        node* p = root;
        while (p != nullptr) {
            if (p->key < n)p = p->right;
            else if (n < p->key)p = p->left;
            else return true;
        }
        return false;
    }

    void erase(const T &n) override {
        root = remove(root, n);
    }

    std::vector<T> dump()override {
        std::deque<node*> q;
        std::vector<T> v;
        q.push_back(root);
        while (!q.empty()) {
            node* p = q.front();
            if (p->left)q.push_back(p->left);
            if (p->right)q.push_back(p->right);
            v.push_back(p->key);
            q.pop_front();
        }
        return v;
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


int main(){

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