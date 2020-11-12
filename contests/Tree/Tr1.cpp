#include <deque>
#include <iostream>

template <typename T>
struct node {
    T key;
    unsigned char param = 1;
    node* left = nullptr;
    node* right = nullptr;
    node* parent = nullptr;
    explicit node(const T& k):key(k) {}
};

template <typename T>
class AbstractTree{
private:
    node<T> *root = nullptr;
protected:
    virtual node<T> *insertNode(node<T>* to,node<T> *&ptr);
    virtual node<T> *minValueNode(node<T>* n);

    virtual node<T>* rotateRight(node<T>* p){};
    virtual node<T>* rotateLeft(node<T>* p){};
    virtual node<T>* remove(node<T> *p,const T&k){};

    void setRoot(node<T> *_root) {
        root = _root;
    }

public:

    virtual ~AbstractTree(){
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

    virtual void insert(const T& key){
        auto *n = new node<T>{key};
        insertNode(root,n);
    };

    bool find(const T& key){
        node<T>* p =this->getRoot();
        while (p != nullptr) {
            if (p->key < key)p = p->left;
            else if (key < p->key)p = p->right;
            else return true;
        }
        return false;
    };

    virtual void erase(const T& key){};

    node<T> *getRoot() const {
        return root;
    }
};

template<typename T>
node<T> *AbstractTree<T>::insertNode(node<T> *to, node<T> *&ptr) {
    if (to == nullptr)
        return ptr;
    if (ptr->key < to->key) {
        to->left = insertNode(to->left, ptr);
        to->left->parent = to;
    } else if (ptr->key > to->key) {
        to->right = insertNode(to->right, ptr);
        to->right->parent = to;
    }
    return to;
}

template<typename T>
node<T> *AbstractTree<T>::minValueNode(node<T> *n) {
    node<T> *ptr = n;
    while (ptr->left != nullptr)
        ptr = ptr->left;
    return ptr;
}

template <typename T>
class RedBackTree : protected AbstractTree<T> {
protected:

    const char BLACK = 1;
    const char RED = 0;
    const char DOUBLE_BLACK = 2;

    char getColor(node<T>* n) {
        if (!n)
            return BLACK;
        return n->param;
    }

    void setColor(node<T>* n, char color) {
        if (!n)
            return;
        n->param = color;
    }

    void fixInsertRBTree(node<T>* ptr) {
        node<T> *parent = nullptr;
        node<T> *grandparent = nullptr;
        while (ptr != this->getRoot() && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
            parent = ptr->parent;
            grandparent = parent->parent;
            if (parent == grandparent->left) {
                node<T> *uncle = grandparent->right;
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
                node<T> *uncle = grandparent->left;
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
        setColor(this->getRoot(), BLACK);
    }

    void fixDeleteRBTree(node<T>* n) {
        if (!n)
            return;

        if (n == this->getRoot()) {
            this->setRoot(nullptr);
            return;
        }

        if (getColor(n) == RED || getColor(n->left) == RED || getColor(n->right) == RED) {
            node<T> *child = n->left != nullptr ? n->left : n->right;

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
            node<T> *sibling = nullptr;
            node<T> *parent = nullptr;
            node<T> *ptr = n;
            setColor(ptr, DOUBLE_BLACK);
            while (ptr != this->getRoot() && getColor(ptr) == DOUBLE_BLACK) {
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
            setColor(this->getRoot(), BLACK);
        }
    }

    node<T>* rotateLeft(node<T>* p) override {
        node<T> *right_child = p->right;
        p->right = right_child->left;

        if (p->right != nullptr)
            p->right->parent = p;

        right_child->parent = p->parent;

        if (p->parent == nullptr)
            this->setRoot(right_child);
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
            this->setRoot(left_child);
        else if (ptr == ptr->parent->left)
            ptr->parent->left = left_child;
        else
            ptr->parent->right = left_child;

        left_child->right = ptr;
        ptr->parent = left_child;
    }

    node<T> *remove(node<T>* r, const T &data) override {
        if (!r)
            return r;
        if (data < r->key)
            return remove(r->left, data);
        if (data > r->key)
            return remove(r->right, data);
        if (r->left == nullptr || r->right == nullptr)
            return r;
        node<T> *tmp = this->minValueNode(r->right);
        r->key = tmp->key;
        return remove(r->right, tmp->key);
    }

public:

    void insert(const T &key) override {
        auto *n = new node<T>(key);
        this->setRoot(this->insertNode(this->getRoot(), n));
        fixInsertRBTree(n);
    }

    void erase(const T &key) override {
        node<T> *n = remove(this->getRoot(), key);
        fixDeleteRBTree(n);
    };
};

template <typename T>
class AVLTree : AbstractTree<T> {
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
        if(!p)return p;
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
        return balance(p->parent);
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
            node<T>* min = findMin(r);
            min->right = removeMin(r);
            min->left = q;
            return min;
        }
        return p;
    }

public:

    void insert(const T &key) override {
        auto * n = new node<T>{key};
        this->setRoot(this->insertNode(this->getRoot(), n));
        balance(n);
    }

    bool find(const T &n) override {
        node<T>* p =this->getRoot();
        while (p != nullptr) {
            if (p->key < n)p = p->left;
            else if (n < p->key)p = p->right;
            else return true;
        }
        return false;
    }

    void erase(const T &key) override {
        node<T> *n = remove(this->getRoot(), key);
        balance(n);
    }

};

int main(){

    RedBackTree<int> tree;
    for (int i = 0; i <10 ; ++i) {
        tree.insert(i);
    }
    for (int i = 0; i <12 ; ++i) {
        //   std::cout<<(AbstractTree)tree(i);
    }

    return 0;
}