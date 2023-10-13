/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"
//Write your code below this line

// remove

int height1(SymNode* root){
    if (root == NULL){
        return -1;
    }
    else return max(height1(root->left), height1(root->right)) + 1;
}

SymNode::SymNode(){
    key = "";
    height = -1;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode::SymNode(string k){
    key = k;
    height = 0;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode* SymNode::LeftLeftRotation(){
    return NULL;
} // case 1
SymNode* SymNode::RightRightRotation(){
    return NULL;
} // case 2
SymNode* SymNode::LeftRightRotation(){
    return NULL;
} // case 3
SymNode* SymNode::RightLeftRotation(){
    return NULL;
}// case 4



SymNode::~SymNode(){
    ;
}
