struct Node { int value; Node* next; }; void push_back(Node current_node, int value);

Node *mergeLists(Node *first_node, Node *second_node){
    Node * n = new Node();
    if (first_node== nullptr && second_node== nullptr){
        return nullptr;
    }else if (first_node== nullptr){
        n->value=second_node->value;
        n->next=mergeLists(first_node,second_node->next);
    }else if (second_node == nullptr){
        n->value=first_node->value;
        n->next=mergeLists(first_node->next,second_node);
    }else if (second_node->value>first_node->value){
        n->value=first_node->value;
        n->next=mergeLists(first_node->next,second_node);
    }else if (second_node->value<first_node->value){
        n->value=second_node->value;
        n->next=mergeLists(first_node,second_node->next);
    }else if (second_node->value==first_node->value){
        return mergeLists(first_node,second_node->next);
    }
    return n;
}