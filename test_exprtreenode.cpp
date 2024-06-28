#include <gtest/gtest.h>

#include "exprtreenode.h"

TEST(ExprTreeNode, BasicTest){
  UnlimitedInt i("1");
  ExprTreeNode n("1", &i);
  ASSERT_EQ(n.val->get_frac_str(), "1/1");

  ExprTreeNode n2("-2", &i);
  ASSERT_EQ(n2.val->get_frac_str(), "-2/1");

  ExprTreeNode n3("-223098420384", &i);
  ASSERT_EQ(n3.val->get_frac_str(), "-223098420384/1");

  ExprTreeNode n4("32923098423", &i);
  ASSERT_EQ(n4.val->get_frac_str(), "32923098423/1");

  ExprTreeNode n5("+", &i);
  ASSERT_EQ(n5.type,"ADD");
  ExprTreeNode n6("-", &i);
  ASSERT_EQ(n6.type,"SUB");
  ExprTreeNode n7("*", &i);
  ASSERT_EQ(n7.type,"MUL");
  ExprTreeNode n8("/", &i);
  ASSERT_EQ(n8.type,"DIV");
  ExprTreeNode n9(":=", &i);
  ASSERT_EQ(n9.type,"ASSIGN");
  ExprTreeNode n10("(", &i);
  ASSERT_EQ(n10.type,"LB");
  ExprTreeNode n11(")", &i);
  ASSERT_EQ(n11.type,"RB");
  ExprTreeNode n12("asfkj", &i);
  ASSERT_EQ(n12.type,"VAR");
  ExprTreeNode n13("v", &i);
  ASSERT_EQ(n13.type,"VAR");
}
