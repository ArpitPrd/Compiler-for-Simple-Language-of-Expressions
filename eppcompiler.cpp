/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){
    memory_size = 0;
    output_file = "";
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    memory_size = mem_limit;
    output_file = out_file;
    for (int i = 0; i < memory_size; i++){
        mem_loc.push_back(i);
    }
}

void alloc_addr(Parser& targ, int i, vector<int>& mem_loc){
    ExprTreeNode* root = targ.expr_trees[i];
    vector<ExprTreeNode*> supp;
    while (root != nullptr || !supp.empty()){
        while (root != nullptr){
            supp.push_back(root);
            root = root->left;
        }
        root = supp.back();
        supp.pop_back();
        if (root->type == "VAR") {
            int addr = targ.symtable->search(root->id);
            if (addr == -1){
                // TODO: Bonus Minheap
                targ.symtable->assign_address(root->id, mem_loc.back());
                mem_loc.pop_back();
            }
            else{
                targ.symtable->assign_address(root->id, addr);
            }
        }
        root = root->right;
    }
}

void EPPCompiler::compile(vector<vector<string>> code){
    for (int i = 0; i < code.size(); i++){
        targ.parse(code[i]);
        if (targ.expr_trees[i]->left->type == "DEL"){
        }
        else{
            alloc_addr(targ, i, mem_loc);
        }
        
        vector<string> set_of_instr = generate_targ_commands();
        write_to_file(set_of_instr);
        if (targ.expr_trees[i]->left->type == "DEL"){
            mem_loc.push_back(targ.last_deleted);
        }
    }
}

void gen_targ_commands(ExprTreeNode* & root, Parser & targ, vector<string>& commands){
    if (root->left == NULL && root->right == NULL){
        if (root->type == "VAL"){
            string instruction = "PUSH " + std::to_string(root->num);
            commands.push_back(instruction);
        }
        else{
            int memory_index = targ.symtable->search(root->id);
            string instruction = "PUSH mem[" + std::to_string(memory_index) + "]";
            commands.push_back(instruction);
        }
    }
    else{
        gen_targ_commands(root->right, targ, commands);
        gen_targ_commands(root->left, targ, commands);
        string instruction = root->type;
        commands.push_back(instruction);
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    vector<string> commands;
    int index_in_expr = targ.expr_trees.size() - 1;
    ExprTreeNode* action_node = targ.expr_trees[index_in_expr]->left;
    
    if (action_node->type == "VAR"){
        int memory_index = targ.symtable->search(action_node->id);
        gen_targ_commands(targ.expr_trees[index_in_expr]->right, targ, commands);
        if (memory_index == -1){
            memory_index = mem_loc.back();
            mem_loc.pop_back();
        }
        string instruction = "mem[" + std::to_string(memory_index) + "] = POP";
        commands.push_back(instruction);
    }
    else if (action_node->type == "DEL"){
        string instruction = "DEL = mem[" + std::to_string(targ.last_deleted) + "]";
        commands.push_back(instruction);
    }
    else if (action_node->type == "RET"){
        gen_targ_commands(targ.expr_trees[index_in_expr]->right, targ, commands);
        string instruction = "RET = POP";
        commands.push_back(instruction);
    }
    return commands;
}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream of;
    of.open(output_file, ios::app);
    for (int i = 0; i < commands.size(); i++){
        of << commands[i] << endl;
       //std::cout << commands[i] << std::endl;
    }
    of.close();
}

EPPCompiler::~EPPCompiler(){
    ;
}

