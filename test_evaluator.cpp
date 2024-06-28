#include <fstream>
#include <iostream>
#include <string>

#include "evaluator.h"
#include "exprtreenode.h"
using namespace std;

void inOrderTraversal(ExprTreeNode* root, vector<string>& v) {
    if (!root) {
        return;
    }
    inOrderTraversal(root->left, v);
    if (root->type == "VAR") {
        v.push_back(root->id);
    } else if (root->type == "VAL") {
        v.push_back(root->val->get_frac_str());
    } else {
        v.push_back(root->type);
    }
    inOrderTraversal(root->right, v);
}
void inOrderTraversal(SymEntry* root, vector<string>& v) {
    if (!root) {
        return;
    }
    inOrderTraversal(root->left, v);
    v.push_back(root->key + ": " + root->val->get_frac_str());
    inOrderTraversal(root->right, v);
}
void print_vector(vector<string>& v) {
    for (auto& elem : v) {
        cout << elem << " ";
    }
    cout << "\n";
}
int main() {
    Evaluator eval;
    vector<string> v;
    ifstream fin;
    fin.open("tests/evaluator_tests.txt");
    if(!(fin.is_open())){
      cout << "File not found\n";
      return 1;
    }
    int n;
    fin >> n;
    vector<vector<string>> paragraph;
    for (int i = 0; i < n; i++) {
        int cur_line_tokens;
        fin >> cur_line_tokens;
        vector<string> line;
        while (cur_line_tokens--) {
            string token;
            fin >> token;
            line.push_back(token);
        }
	eval.parse(line);
        eval.eval();
        paragraph.push_back(line);
    }
    for (int i = 0; i < paragraph.size(); i++) {
        inOrderTraversal(eval.expr_trees[i], v);
        print_vector(v);
	v.clear();
    }
    inOrderTraversal(eval.symtable->get_root(), v);
    print_vector(v);
}
