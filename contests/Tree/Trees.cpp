
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
        int color;
        node *parent = nullptr;
        node *left = nullptr;
        node *right = nullptr;

        node(T key, int color, node *parent) : key(key), color(color), parent(parent) {}

        virtual ~node() {
            delete left;
            delete right;
        }

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

    void left_rotate(struct node *x){
        struct node *y;

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

    void right_rotate(struct node *x){
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

    void red_black_delete(struct node *z){
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

    void red_black_delete_fixup(struct node *x){
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