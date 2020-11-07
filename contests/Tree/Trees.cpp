#include <deque>

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

    struct node{
        T& key;
        char color;
        node *parent = nullptr;
        node *left = nullptr;
        node *right = nullptr;

        node(T key, char color, node *parent) : key(key), color(color), parent(parent) {}

    };

    const char BLACK = 1;
    const char RED = 0;

    node *root = nullptr;

    node *tree_search(T key){
        node *x = root ;
        while(x != nullptr && x->key != key){
            if(key < x->key)x = x->left;
            else x = x->right;
        }
        return x;
    }

    node *tree_minimum(node *x){
        while(x->left != nullptr)x = x->left;
        return x;
    }

    void red_black_insert(T key){
        node *z, *x, *y;

        z = new node(key,RED, nullptr);
        x = root;
        y = nullptr;

        while(x != nullptr){
            y = x;
            if(z->key <= x->key)x = x->left;
            else x = x->right;
        }

        if(!y)root = z;
        else if(z->key <= y->key)y->left = z;
        else y->right = z;
        z->parent = y;
        red_black_insert_fixup(z);
    }

    void red_black_insert_fixup(node *z){
        while(z->parent->color == RED){
            if(z->parent == z->parent->parent->left){
                if(z->parent->parent->right->color == RED){
                    z->parent->color = BLACK;
                    z->parent->parent->right->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }else{
                    if(z == z->parent->right){
                        z = z->parent;
                        left_rotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    right_rotate(z->parent->parent);
                }
            }else{
                if(z->parent->parent->left->color == RED){
                    z->parent->color = BLACK;
                    z->parent->parent->left->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }else{
                    if(z == z->parent->left){
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    left_rotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void left_rotate(node *x){
        node *y;

        y = x->right;
        x->right = y->left;
        if(y->left)y->left->parent = x;

        y->parent = x->parent;
        if(!y->parent)root = y;
        else if(x == x->parent->left)x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void right_rotate(node *x){
        node *y;

        y = x->left;
        x->left = y->right;
        if(y->right) y->right->parent = x;

        y->parent = x->parent;
        if(!y->parent)root = y;
        else if(x == x->parent->left)x->parent->left = y;
        else x->parent->right = y;
        y->right = x;
        x->parent = y;
    }

    void red_black_delete(node *z){
        node *y, *x;
        int yOriginalColor;

        y = z;
        yOriginalColor = y->color;

        if(!z->left){
            x = z->right;
            red_black_transplant(z, z->right);
        }
        else if(!z->right){
            x = z->left;
            red_black_transplant(z, z->left);
        }else{
            y = tree_minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if(y->parent == z)x->parent = y;
            else{
                red_black_transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            red_black_transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if(yOriginalColor == BLACK)red_black_delete_fixup(x);
    }

    void red_black_delete_fixup(node *x){
        node *w;

        while(x != root && x->color == BLACK){
            if(x == x->parent->left){
                w = x->parent->right;
                if(w->color == RED){
                    w->color = BLACK;
                    x->parent->color = RED;
                    left_rotate(x->parent);
                    w = x->parent->right;
                }
                if(w->left->color == BLACK && w->right->color == BLACK){
                    w->color = RED;
                    x->parent->color = BLACK;
                    x = x->parent;
                }else{
                    if(w->right->color == BLACK){
                        w->color = RED;
                        w->left->color = BLACK;
                        right_rotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    x->right->color = BLACK;
                    left_rotate(x->parent);
                    x = root;
                }
            }else{
                w = x->parent->left;
                if(w->color == RED){
                    w->color = BLACK;
                    x->parent->color = BLACK;
                    right_rotate(x->parent);
                    w = x->parent->left;
                }

                if(w->left->color == BLACK && w->right->color == BLACK){
                    w->color = RED;
                    x->parent->color = BLACK;
                    x = x->parent;
                }else{
                    if(w->left->color == BLACK){
                        w->color = RED;
                        w->right->color = BLACK;
                        left_rotate(w);
                        w = x->parent->left;
                    }

                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    right_rotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void red_black_transplant(node *u, node *v){
        if(u->parent == nullptr)root = v;
        else if(u == u->parent->left)u->parent->left = v;
        else u->parent->right = v;
        v->parent = u->parent;
    }

public:
    
    ~RedBackTree() override {
        delete root;
    }

    T &insert(T &n) override {
        if (!root)root = new node(n,BLACK, nullptr);
        else red_black_insert(n);
        return n;
    }

    bool find(const T &n) override {
        return tree_search(n);
    }

    T &erase(const T &n) override {
        red_black_delete(n);
        return n;
    }

};


template <typename T>
class AVLTree : AbstractTree<T> {
private:
    struct node {
        T key;
        unsigned char height;
        node* left;
        node* right;
        explicit node(T k) { key = k; left = right = 0; height = 1; }
    };

    node* root = nullptr;

    unsigned char height(node* p){
        return p?p->height:0;
    }

    int bFactor(node* p){
        return height(p->right)-height(p->left);
    }

    void fixHeight(node* p){
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        p->height = (hl>hr?hl:hr)+1;
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

    node* insert(node* p, T &k){
        if( !p ) return new node(k);
        if( k < p->key )p->left = insert(p->left,k);
        else p->right = insert(p->right,k);
        return balance(p);
    }

    node* remove(node* p, T k){
        if( !p ) return 0;
        if( k < p->key )p->left = remove(p->left,k);
        else if( p->key < k)p->right = remove(p->right,k);
        else{
            node* q = p->left;
            node* r = p->right;
            delete p;
            if( !r ) return q;
            node* min = findmin(r);
            min->right = removemin(r);
            min->left = q;
            return balance(min);
        }
        return balance(p);
    }

public:

    ~AVLTree() override {
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

    T &insert(T &n) override {
        root = insert(root, n);
        return n;
    }

    bool find(const T &n) override {
        node* p = root;
        while (p != nullptr) {
            if (p->key < n)p = p->left;
            else if (n < p->key)p = p->right;
            else return true;
        }
        return false;
    }

    T &erase(const T &n) override {
        root = remove(root, n);
        return n;
    }

};

int main(){
    return 0;
}