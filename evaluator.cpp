/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

#include "exprtreenode.h"
#include "symtable.h"
#include "ulimitedrational.h"

// ExprTreeNode* create_non_number_node(string token, string& type) {
//     return new ExprTreeNode(type, (UnlimitedInt*)nullptr);
// }
ExprTreeNode* create_rational_node(string p, string q) {
    UnlimitedInt num(p);
    UnlimitedInt den(q);
    UnlimitedRational rational(&num, &den);
    return new ExprTreeNode("VAL", &rational);
}

void create_subtree(vector<ExprTreeNode*>& expr_trees) {
    vector<ExprTreeNode*> assignment_arr;
    while (expr_trees.back()->type != "LB") {
        assignment_arr.push_back(expr_trees.back());
        expr_trees.pop_back();
    }
    ExprTreeNode* left_bracket = expr_trees.back();
    delete left_bracket;
    expr_trees.pop_back();
    if (assignment_arr.size() == 3) {
        ExprTreeNode* right = assignment_arr[0];
        ExprTreeNode* op = assignment_arr[1];
        ExprTreeNode* left = assignment_arr[2];
        op->right = right;
        op->left = left;
        expr_trees.push_back(op);
    }
}

Evaluator::Evaluator() { symtable = new SymbolTable(); };

Evaluator::~Evaluator() {
    delete symtable;
    for (ExprTreeNode* ptr : expr_trees) {
        delete ptr;
    }
};

// Read an input vector of tokens (strings)
// Parse it and convert it to a parse tree
// Push the root of the tree in the expr_trees
void Evaluator::parse(vector<string> code) {
    vector<ExprTreeNode*> stk;
    string type;
    UnlimitedInt i1("1");
    ExprTreeNode* var = new ExprTreeNode(code[0], &i1);
    var->id = code[0];
    ExprTreeNode* assign = new ExprTreeNode(code[1], &i1);
    for (long unsigned int i = 2; i < code.size(); i++) {
        if (code[i] == ")") {
            create_subtree(stk);
        } else {
            ExprTreeNode* node = new ExprTreeNode(code[i], &i1);
            if (node->type == "VAR") {
                node->id = code[i];
            }
            stk.push_back(node);
        }
    }
    // Guaranteed that the last operator will be the root;
    assign->left = var;
    assign->right = stk[0];
    expr_trees.push_back(assign);
};

void postOrderTraversal(ExprTreeNode* cur, SymbolTable* sym_table) {
    if (!cur) {
        return;
    } else if (cur->type == "VAR") {
        UnlimitedRational* original = (sym_table->search(cur->id));
        if (original) {
            UnlimitedInt p(original->get_p_str());
            UnlimitedInt q(original->get_q_str());
            cur->evaluated_value = new UnlimitedRational(&p, &q);
        }
    } else if (cur->type == "VAL") {
        return;
    } else {
        postOrderTraversal(cur->left, sym_table);
        postOrderTraversal(cur->right, sym_table);
        UnlimitedRational* left_eval = cur->left->evaluated_value;
        UnlimitedRational* right_eval = cur->right->evaluated_value;
        UnlimitedRational* res;
        if (cur->type == "ASSIGN") {
            sym_table->insert(cur->left->id, right_eval);
        } else if (cur->type == "ADD") {
            res = UnlimitedRational::add(left_eval, right_eval);
            cur->evaluated_value = res;
        } else if (cur->type == "SUB") {
            res = UnlimitedRational::sub(left_eval, right_eval);
            cur->evaluated_value = res;
        } else if (cur->type == "MUL") {
            res = UnlimitedRational::mul(left_eval, right_eval);
            cur->evaluated_value = res;
        } else if (cur->type == "DIV") {
            res = UnlimitedRational::div(left_eval, right_eval);
            cur->evaluated_value = res;
        }
    }
}
// Evaluate the last element of the expr_trees
// This function is guaranteed to be called immediately
// after a call to parse, and will be only called ONCE
// for a tree
// Also populate the symbol tables
void Evaluator::eval() { postOrderTraversal(expr_trees.back(), symtable); };
