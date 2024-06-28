#include <gtest/gtest.h>

#include <fstream>
#include <vector>

#include "symtable.h"

using std::string;
using std::vector;
// using namespace std;
void inOrderTraversal(SymEntry* root, vector<string>& v) {
    if (!root) {
        return;
    }
    inOrderTraversal(root->left, v);
    v.push_back(root->key);
    inOrderTraversal(root->right, v);
}

TEST(BSTInsertion, BasicTest) {
    SymbolTable st;
    string s1("1");
    string s2("2");
    string s3("3");
    UnlimitedInt i1("1");
    UnlimitedInt i2("1");
    UnlimitedRational u(&i1, &i2);
    st.insert(s2, &u);
    st.insert(s1, &u);
    st.insert(s3, &u);
    vector<string> v;
    inOrderTraversal(st.get_root(), v);
    for (int i = 0; i < 3; i++) {
        ASSERT_EQ(v[i], std::to_string(i + 1));
    }
}

TEST(BSTInsertion, Ultimate) {
    SymbolTable st;
    std::ifstream fin;
    UnlimitedInt i1("1");
    UnlimitedInt i2("1");
    UnlimitedRational u(&i1, &i2);
    fin.open("tests/bst_test_cases.txt");
    int n;
    fin >> n;
    std::string s1;
    while (n--) {
        fin >> s1;
	st.insert(s1, &u);
    }
    vector<string> v;
    inOrderTraversal(st.get_root(), v);
    for(int i = 1; i < v.size(); i++){
      ASSERT_LE(v[i-1],v[i]);
    }
}

TEST(BSTSearch, Ultimate){
    SymbolTable st;
    std::ifstream fin;
    UnlimitedInt i1("1");
    UnlimitedInt i2("1");
    UnlimitedRational u(&i1, &i2);
    fin.open("tests/bst_test_cases.txt");
    int n;
    fin >> n;
    std::string s1;
    while (n--) {
        fin >> s1;
	st.insert(s1, &u);
    }
    vector<string> v;
    inOrderTraversal(st.get_root(), v);
    for(int i = 0; i < v.size(); i++){
      ASSERT_NE(st.search(v[i]), nullptr);
    }
}

TEST(BSTDelete, LeafNode){
    SymbolTable st;
    string s1("1");
    string s2("2");
    string s3("3");
    UnlimitedInt i1("1");
    UnlimitedInt i2("1");
    UnlimitedRational u(&i1, &i2);
    st.insert(s2, &u);
    st.insert(s1, &u);
    st.insert(s3, &u);
    vector<string> v;
    st.remove("1");
    inOrderTraversal(st.get_root(), v);
    ASSERT_EQ("2", v[0]);
    ASSERT_EQ("3", v[1]);
}

TEST(BSTDelete, RootDeletetionLeftChild){
    SymbolTable st;
    string s1("1");
    string s2("2");
    UnlimitedInt i1("1");
    UnlimitedInt i2("1");
    UnlimitedRational u(&i1, &i2);
    st.insert(s2, &u);
    st.insert(s1, &u);
    vector<string> v;
    st.remove("2");
    inOrderTraversal(st.get_root(), v);
    ASSERT_EQ("1", v[0]);
}
TEST(BSTDelete, RootDeletetionRightChild){
    SymbolTable st;
    string s1("1");
    string s2("2");
    UnlimitedInt i1("1");
    UnlimitedInt i2("1");
    UnlimitedRational u(&i1, &i2);
    st.insert(s1, &u);
    st.insert(s2, &u);
    vector<string> v;
    st.remove("1");
    inOrderTraversal(st.get_root(), v);
    ASSERT_EQ("2", v[0]);
}
TEST(BSTDelete, RootDeletetionBothChildren){
    SymbolTable st;
    string s1("1");
    string s2("2");
    string s3("3");
    UnlimitedInt i1("1");
    UnlimitedInt i2("1");
    UnlimitedRational u(&i1, &i2);
    st.insert(s2, &u);
    st.insert(s1, &u);
    st.insert(s3, &u);
    vector<string> v;
    st.remove("2");
    inOrderTraversal(st.get_root(), v);
    ASSERT_EQ("1", v[0]);
    ASSERT_EQ("3", v[1]);
}
TEST(BSTDelete, DeletetionBothChildren){
    SymbolTable st;
    string s1("1"); //          3
    string s2("3"); //        1   5 
    string s3("5"); //          4   7
    string s4("4"); //             6  8
    string s5("7"); //
    string s6("8"); //
    string s7("6");
    UnlimitedInt i1("1");
    UnlimitedInt i2("1");
    UnlimitedRational u(&i1, &i2);
    st.insert(s2, &u);
    st.insert(s1, &u);
    st.insert(s3, &u);
    st.insert(s4, &u);
    st.insert(s5, &u);
    st.insert(s6, &u);
    st.insert(s7, &u);
    vector<string> v;
    st.remove("5");
    inOrderTraversal(st.get_root(), v);
    ASSERT_EQ(v[0], "1");
    ASSERT_EQ(v[1], "3");
    ASSERT_EQ(v[2], "4");
    ASSERT_EQ(v[3], "6");
    ASSERT_EQ(v[4], "7");
    ASSERT_EQ(v[5], "8");
}
TEST(BSTDeletion, Ultimate) {
    SymbolTable st;
    std::ifstream fin;
    UnlimitedInt i1("1");
    UnlimitedInt i2("1");
    UnlimitedRational u(&i1, &i2);
    fin.open("tests/bst_test_cases.txt");
    int n;
    fin >> n;
    std::string s1;
    while (n--) {
        fin >> s1;
	st.insert(s1, &u);
    }
    vector<string> v;
    inOrderTraversal(st.get_root(), v);
    for(int i = 0; i < v.size(); i+=2){
      st.remove(v[i]);
    }
    vector<string> after_deletion;
    inOrderTraversal(st.get_root(), after_deletion);
    for(int i = 0; i < after_deletion.size(); i++){
      ASSERT_EQ(v[2*i+1], after_deletion[i]) << "i is: " << i << "\n";
    }
}
