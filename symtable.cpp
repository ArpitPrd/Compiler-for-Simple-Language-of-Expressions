/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

SymbolTable::SymbolTable(){
    size = 0;
    root = nullptr;
}

int height(SymNode* & root){
    if (root == NULL){
        return -1;
    }
    else return max(height(root->left), height(root->right)) + 1;
}

SymNode* LLR(SymNode* & root){
    SymNode* head = root->right;
    SymNode* init_root_par = root->par;
    root->right = head->left;
    root->height = height(root);
    if (root->right != NULL) root->right->par = root;
    head->left = root;
    root->par = head;
    root = head;
    head->height = height(head);
    head->par = init_root_par;
    return root;
}

SymNode* RRR(SymNode* & root){
    SymNode* head = root->left;
    SymNode* init_root_par = root->par;
    root->left = head->right;
    if (root->left != NULL) root->left->par = root;
    head->right = root;
    root->par = head;
    root->height = height(root);
    root = head;
    head->height = height(head);
    head->par = init_root_par;
    return root;
}

SymNode* LRR(SymNode* & root){
    RRR(root->right);
    LLR(root);
    return root;
}

SymNode* RLR(SymNode* & root){
    LLR(root->left);
    RRR(root);
    return root;
}

int bal(SymNode* & root){
    if (root == NULL) return -25;
    return (height(root->left) - height(root->right));
}



void height_balance(SymNode* & root){
    if (root == nullptr) return;
    if (bal(root) == 2){
        if (bal(root->left) >= 0){
            RRR(root);
        }
        else{
            RLR(root);
        }
    }
    else if (bal(root) == -2) {
        if (bal(root->right) <= 0){
            LLR(root);
        }
        else{
            LRR(root);
        }
    }
}

void insertion(SymNode* & root, string k, SymNode* & proot, bool left){
    if (root == NULL){
        if (proot->height == -1){
            root = new SymNode(k);
        }
        else{
            root = new SymNode(k);
            root->par = proot;
            if (left){
                proot->left = root;
            }
            else{
                proot->right = root;
            }
        }
    }
    else if (root->key < k){
        insertion(root->right, k, root, false);
    }
    else if (root->key > k){
        insertion(root->left, k, root, true);
    }
    height_balance(root);
}

void SymbolTable::insert(string k){
if (search(k) == -2){
    SymNode* proot = new SymNode();
    insertion(root, k, proot, false);
    size++;
    delete proot;
}
}

SymNode* find_s(SymNode* node){
    node = node->right;
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

void deletion( SymNode* & root, string k){
    if (root == NULL) return ;
    if (root->key > k) deletion(root->left, k);
    else if (root->key < k) deletion(root->right, k);
    else{
        if (root->right != NULL && root->left != NULL){
            SymNode* succ = find_s(root);
            root->key = succ->key;
		root->address = succ->address;
            deletion(root->right, succ->key);
        }
        else{
            
            SymNode* to_delete = root;
            SymNode* next_root;
            SymNode* parent_to_delete = root->par;
            if (root->left != NULL) {
                parent_to_delete = root->left;
                root->left->par = parent_to_delete;
                next_root = root->left;
            }
            else if (root->right != NULL) {
                parent_to_delete = root->right;
                root->right->par = parent_to_delete;
                next_root = root->right;
            }
            else{
                next_root = NULL;
            }
            delete to_delete;
            root = next_root;
            /*
            SymNode* oldNode = root;
            SymNode* parent = root->par;
            if (root->left != nullptr){
                if (parent != nullptr){
                    if (parent->left == root){
                        parent->left = root->left;
                    }
                    else{
                        parent->right = root->left;
                    }
                    root->left->par = parent;
                }
                else{
                    root->left->par = nullptr;
                }
                delete oldNode;
                root = parent->left;
            }
            else if (root->right != nullptr){
                if (parent != nullptr){
                    if (parent->left != nullptr){
                        if (parent->left == root){
                            parent->left = root->right;
                        }
                        else{
                            parent->right = root->right;
                        }
                        root->left->par = parent;
                    }
                    else{
                        root->right->par = parent;
                    }
                }
                else{
                    root->right->par = nullptr;
                }
                delete oldNode;
                root = root->right;
            }
            else{
                delete root;
                root->left = nullptr;
                root->right = nullptr;
            }
	*/
        }
    }
    height_balance(root);
}

void SymbolTable::remove(string k){
    if (search(k) != -2) {
        size--;
        deletion(root, k);
    }
}

int SymbolTable::search(string k){
    SymNode* e = root;
    if (e == NULL) return -2;
    while (true){
        if (k > e->key){
            if (e->right == NULL) return -2;
            else{
                e = e->right;
            }
        }
        else if (k < e->key){
            if (e->left == NULL) return -2;
            else{
                e = e->left;
            }
        }
        else{
            return e->address;
        }
    }
    return -2;
}

SymNode* find_node(string variable, SymNode* &root){
    SymNode* e = root;
    if (e == NULL) {
        return NULL;
    }
    while (true){
        if (variable > e->key){
            if (e->right == NULL) return NULL;
            else{
                e = e->right;
            }
        }
        else if (variable < e->key){
            if (e->left == NULL) return NULL;
            else{
                e = e->left;
            }
        }
        else{
            return e;
        }
    }
    return NULL;
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* location_of_vark = find_node(k, root);
    if (location_of_vark == NULL){
        insert(k);
        location_of_vark = find_node(k, root);
    }
    location_of_vark->address = idx;
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    while (size > 1){   
        remove(root->key);
    }
    if (root != NULL) remove(root->key);
    root = NULL;
}

