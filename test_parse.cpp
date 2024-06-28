#include "evaluator.h"

#include <gtest/gtest.h>

TEST(Evaluator, BasicTest){
  Evaluator e; 
  vector<string> code = {"v", ":=", "(", "-1", "+", "5", ")"};
  e.parse(code);
  e.eval();

  code = {"u", ":=", "3"};

  code = {"k", ":=", "(", "320984", "/", "(", "9203843902", "+", "(", "5", "+", "(", "-3", "+", "(", "1", "*", "(", "3", "/", "4", ")", ")", ")", ")", ")", ")"};
  string code_str  = " ( 320984/(9203843902+(5+(-3+(1*(3/4))))))";
  e.parse(code);
  e.eval();
  std::cout << e.symtable->search("k")->get_frac_str();
}
