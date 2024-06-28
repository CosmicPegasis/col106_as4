/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

#include "ulimitedint.h"
#include "ulimitedrational.h"

ExprTreeNode::ExprTreeNode() {
    val = nullptr;
    evaluated_value = nullptr;
    type = "";
    id = "";
    left = nullptr;
    right = nullptr;
};

ExprTreeNode::ExprTreeNode(string token, UnlimitedInt* v) : ExprTreeNode{} {
    bool is_number = false;
    if (token.size() == 1) {
        if (token == "+") {
            type = "ADD";
        } else if (token == "-") {
            type = "SUB";
        } else if (token == "*") {
            type = "MUL";
        } else if (token == "/") {
            type = "DIV";
        } else if (token == "%") {
            type = "MOD";
        } else if (token == "(") {
            type = "LB";
        } else if (token == ")") {
            type = "RB";
        } else if (token[0] >= '0' && token[0] <= '9') {
            type = "VAL";
            is_number = true;
        } else {
            type = "VAR";
        }
    } else {
        if ((token[0] >= '0' && token[0] <= '9') || token[0] == '-') {
            is_number = true;
            type = "VAL";
        } else if (token == ":=") {
            is_number = false;
            type = "ASSIGN";
        } else {
            is_number = false;
            type = "VAR";
        }
    }
    if (is_number) {
        UnlimitedInt p(token);
        UnlimitedInt q("1");
        this->val = new UnlimitedRational(&p, &q);
        this->evaluated_value = new UnlimitedRational(&p, &q);
    }
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v) {
    if (t == "VAL") {
        UnlimitedInt* p = v->get_p();
        UnlimitedInt* q = v->get_q();
        val = new UnlimitedRational(p, q);
        evaluated_value = new UnlimitedRational(p, q);
        this->type = "VAL";
    } else {
        type = t;
        val = nullptr;
        evaluated_value = nullptr;
    }
    left = nullptr;
    right = nullptr;
}
ExprTreeNode::~ExprTreeNode() {
    delete val;
    delete evaluated_value;
    delete left;
    delete right;
};
