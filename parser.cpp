/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    symtable = new SymbolTable();
    //last_deleted = 0;
}

bool is_digit(string s){
    bool flag = true;
    for (char i : s){
        if (!isdigit(i)){
            return false;
        }
    }
    return true;
}

void Parser::parse(vector<string> code){
    string start = code[0];
    code.erase(code.begin());
    code.erase(code.begin());
    vector<ExprTreeNode*> prevNode;
    ExprTreeNode* root = new ExprTreeNode();
    prevNode.push_back(root);
    ExprTreeNode* currNode = root;
    for (string i : code){
        if (i == "("){
            ExprTreeNode* n = new ExprTreeNode();
            currNode->left = n;
            prevNode.push_back(currNode);
            currNode = currNode->left;
        }
        else if (i == "+"){
            currNode->type = "ADD";
            ExprTreeNode* n = new ExprTreeNode();
            currNode->right = n;
            prevNode.push_back(currNode);
            currNode = currNode->right;
        }
        else if (i == "-"){
            currNode->type = "SUB";
            ExprTreeNode* n = new ExprTreeNode();
            currNode->right = n;
            prevNode.push_back(currNode);
            currNode = currNode->right;
        }
        else if (i == "*"){
            currNode->type = "MUL";
            ExprTreeNode* n = new ExprTreeNode();
            currNode->right = n;
            prevNode.push_back(currNode);
            currNode = currNode->right;
        }
        else if (i == "/"){
            currNode->type = "DIV";
            ExprTreeNode* n = new ExprTreeNode();
            currNode->right = n;
            prevNode.push_back(currNode);
            currNode = currNode->right;
        }
        else if (i == ")"){
            currNode = prevNode.back();
            prevNode.pop_back();
        }
        else{
            if (is_digit(i)){
                currNode->num = stoi(i);
                currNode->type = "VAL";
                currNode = prevNode.back();
                prevNode.pop_back();
            }
            else{
                currNode->id = i;
                currNode->num = symtable->search(i);
                currNode->type = "VAR";
                currNode = prevNode.back();
                prevNode.pop_back();
            }
        }
    }
    ExprTreeNode* real_root = new ExprTreeNode();
    real_root->id = ":=";
    real_root->right = root;
    ExprTreeNode* lhs;
    if (start == "del"){
        lhs = new ExprTreeNode();
        lhs->type = "DEL";
        last_deleted = symtable->search(real_root->right->id);
        symtable->remove(real_root->right->id);
    }
    else if (start == "ret"){
        lhs = new ExprTreeNode();
        lhs->type = "RET";
    }
    else{
        lhs = new ExprTreeNode(start, 0);
        lhs->id = start;
        symtable->insert(start);
    }
    real_root->left = lhs;
    expr_trees.push_back(real_root);
}

void remove_for_expr(ExprTreeNode* root){
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL){
        delete root;
        return;
    }
    else{
        remove_for_expr(root->left);
        remove_for_expr(root->right);
        delete root;
    }
}

Parser::~Parser(){
    delete symtable;
    for (ExprTreeNode* root : expr_trees){
        remove_for_expr(root);
    }
}
