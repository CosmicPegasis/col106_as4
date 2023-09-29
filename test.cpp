#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <fstream>
// #include "./ulimitedint.h"
#include "test.h"

TEST(NaturalHalfAdd, Basic) {
  ASSERT_EQ("3", UNUtil::simpleHalfAdd('1', '2'));
}
TEST(NaturalHalfAdd, Carry) {
  ASSERT_EQ("12", UNUtil::simpleHalfAdd('6', '6'));
}
TEST(NaturalFullAdd, NoCarry) {
  char sum, carry;
  UNUtil::simpleAdd('1', '2', '0', sum, carry);
  ASSERT_EQ(sum, '3');
  ASSERT_EQ(carry, '0');
}
TEST(NaturalFullAdd, WithCarry) {
  char sum, carry;
  UNUtil::simpleAdd('1', '2', '3', sum, carry);
  ASSERT_EQ('6', sum);
  ASSERT_EQ('0', carry);
}
TEST(NaturalFullAdd, WithCarryOverflowandCarryOver){
  char sum, carry;
  UNUtil::simpleAdd('5','3', '2', sum, carry);
  ASSERT_EQ('1', carry);
  ASSERT_EQ('0', sum);
}
TEST(NaturalFullAdd, WithCarryandCarryOverOverflow){
  char sum, carry;
  UNUtil::simpleAdd('5','5', '2', sum, carry);
  ASSERT_EQ('1', carry);
  ASSERT_EQ('2', sum);
}

TEST(NaturalFullAdd, WithCarryOverflowAndCarryOverOverFlow){
  char sum, carry;
  UNUtil::simpleAdd('9', '9', '9', sum, carry);
  ASSERT_EQ('2', carry);
  ASSERT_EQ('7', sum);
}
TEST(NaturalFullAdd, WithCarryandCarryOverOverFlow){
  char sum, carry;
  UNUtil::simpleAdd('1', '1', '9', sum, carry);
  ASSERT_EQ('1', carry);
  ASSERT_EQ('1', sum);
}
TEST(UNConstructorTest, Basic){
  std::string s = "1023";
  UN n(s);
  ASSERT_EQ(n.to_string(), s);
}
TEST(UNSum, Basic){
  UN n1("2332");
  UN n2("232");
  UN* n3 = UN::add(&n1, &n2);
  ASSERT_EQ("2564", n3->to_string());
  delete n3;
}
TEST(UNSum, LongLong){
  long long i1 = 2102330999939481029;
  long long i2 = 2304923099234809298;
  std::string s1 = std::to_string(i1);
  std::string s2 = std::to_string(i2);
  UN n1(s1);
  UN n2(s2);
  std::string res = std::to_string(i1 + i2);
  UN* n3 = UN::add(&n1, &n2);
  ASSERT_EQ(n3->to_string(), res);
  delete n3;
}
// TEST(UNSum, LongLongUltimate){
//   std::ifstream fin;
//   std::ofstream fout;
//   fin.open("tests/test_cases.txt");
//   fout.open("tests/addition_cpp.txt");
//   std::string s1;
//   std::string s2;
//   while(!(fin.eof())){
//     fin >> s1;
//     fin >> s2;
//     UN n1(s1);
//     UN n2(s2);
//     UN* n3 = UN::add(&n1, &n2);
//     fout << n3->to_string() << "\n";
//     delete n3;
//   }

// }
TEST(ReverseString, Basic){
  std::string s = "hello";
  UNUtil::reverse_string(s);
  ASSERT_EQ("olleh", s);
}

TEST(tensComplementSingleDigit, Basic){
  char c = '5';
  char complement = UNUtil::tensComplementSingleDigit(c);
  ASSERT_EQ(complement, '4');
}

TEST(tensComplement, Basic){
  UN n("45");
  UN* complement = UNUtil::tensComplement(n.to_string());
  ASSERT_EQ(complement->to_string(), "55");
  delete complement;
}

TEST(pad, Basic){
  std::string s = "1234";
  ASSERT_EQ(UNUtil::pad(s, 4), "00001234");
}

TEST(UNLStrip, Basic){
  ASSERT_EQ(UNUtil::lstrip("123", 2), "23");
}
TEST(UNRemoveLeadingZeroes, Basic){
  ASSERT_EQ(UNUtil::remove_leading_zeroes("000012"), "12");
}
TEST(UNRemoveLeadingZeroes, ZeroTest){
  ASSERT_EQ(UNUtil::remove_leading_zeroes("00000"), "0");
}
TEST(UNSub, Basic){
  UN i1("4");
  UN i2("3");
  UN* i3 = UN::sub(&i1, &i2);
  ASSERT_EQ(i3->to_string(), "1");
  delete i3;
}
TEST(UNSub, LeadingZeroes){
  UN i1("11");
  UN i2("11");

  UN* i3 = UN::sub(&i1, &i2);
  ASSERT_EQ(i3->to_string(), "0");
  delete i3;
}

TEST(UNSub, LongLongTest){
  UN i1("239873418237498");
  UN i2("239048092384");
  long long li1 = 239873418237498;
  long long li2 = 239048092384;
  UN* i3 = UN::sub(&i1, &i2);
  ASSERT_EQ(std::to_string(li1 - li2), i3->to_string());
  delete i3;
}
// TEST(UNSubtraction, LongLongUltimate){
//   std::ifstream fin;
//   std::ofstream fout;
//   fin.open("tests/sub_test_cases.txt");
//   fout.open("tests/subtraction_cpp.txt");
//   std::string s1;
//   std::string s2;
//   while(!(fin.eof())){
//     fin >> s1;
//     fin >> s2;
//     UN n1(s1);
//     UN n2(s2);
//     UN* n3 = UN::sub(&n1, &n2);
//     fout << n3->to_string() << "\n";
//     delete n3;
//   }

// }

TEST(UNSingleDigitMultiplication, Basic){
  ASSERT_EQ("8", UNUtil::single_digit_multiplication('4', '2'));
}
TEST(UNMultiplyOneRow, Basic){
  int i1 = 13248;
  int i2 = 4;
  UN n1(std::to_string(i1));
  UN* res = UNUtil::multiply_one_row(&n1, std::to_string(4)[0]);
  ASSERT_EQ(res->to_string(), std::to_string(i1 * i2));
  delete res;
}
TEST(UNMulitplyOneRow, LongLong){
  long long i1 = 182309489300239797;
  int i2 = 9;
  UN n1(std::to_string(i1));
  UN* res = UNUtil::multiply_one_row(&n1, std::to_string(i2)[0]);
  ASSERT_EQ(res->to_string(), std::to_string(i1 * i2));
  delete res;
}
TEST(UNMultiply, Basic){
  int i1 = 456;
  int i2 = 541;

  UN n1(std::to_string(i1));
  UN n2(std::to_string(i2));
  UN* res = UN::mul(&n1, &n2);
  ASSERT_EQ(res->to_string(), std::to_string(i1 * i2));
  delete res;
}

TEST(UNMultiply, LongLong){
  long long i1 = 247509250298;
  long long i2 = 32423480;
  UN n1(std::to_string(i1));
  UN n2(std::to_string(i2));
  UN* res = UN::mul(&n1, &n2);
  ASSERT_EQ(res->to_string(), std::to_string(i1 * i2));
  delete res;
}
