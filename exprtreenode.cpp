/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    left = nullptr;
    right = nullptr;
    num = 0;
    id = "";
    type = "";
}

ExprTreeNode::ExprTreeNode(string t,int v){
    type = "VAR";
    num = v;
    left = nullptr;
    right = nullptr;
    id = t;
}

ExprTreeNode::~ExprTreeNode(){
    ;
}

