#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <fstream>
// #include "./ulimitedint.h"
#include "test.h"

TEST(NaturalHalfAdd, Basic) {
  ASSERT_EQ("3", UnlimitedNatural::simpleHalfAdd('1', '2'));
}
TEST(NaturalHalfAdd, Carry) {
  ASSERT_EQ("12", UnlimitedNatural::simpleHalfAdd('6', '6'));
}
TEST(NaturalFullAdd, NoCarry) {
  char sum, carry;
  UnlimitedNatural::simpleAdd('1', '2', '0', sum, carry);
  ASSERT_EQ(sum, '3');
  ASSERT_EQ(carry, '0');
}
TEST(NaturalFullAdd, WithCarry) {
  char sum, carry;
  UnlimitedNatural::simpleAdd('1', '2', '3', sum, carry);
  ASSERT_EQ('6', sum);
  ASSERT_EQ('0', carry);
}
TEST(NaturalFullAdd, WithCarryOverflowandCarryOver){
  char sum, carry;
  UnlimitedNatural::simpleAdd('5','3', '2', sum, carry);
  ASSERT_EQ('1', carry);
  ASSERT_EQ('0', sum);
}
TEST(NaturalFullAdd, WithCarryandCarryOverOverflow){
  char sum, carry;
  UnlimitedNatural::simpleAdd('5','5', '2', sum, carry);
  ASSERT_EQ('1', carry);
  ASSERT_EQ('2', sum);
}

TEST(NaturalFullAdd, WithCarryOverflowAndCarryOverOverFlow){
  char sum, carry;
  UnlimitedNatural::simpleAdd('9', '9', '9', sum, carry);
  ASSERT_EQ('2', carry);
  ASSERT_EQ('7', sum);
}
TEST(NaturalFullAdd, WithCarryandCarryOverOverFlow){
  char sum, carry;
  UnlimitedNatural::simpleAdd('1', '1', '9', sum, carry);
  ASSERT_EQ('1', carry);
  ASSERT_EQ('1', sum);
}
TEST(UnlimitedNaturalConstructorTest, Basic){
  std::string s = "1023";
  UnlimitedNatural n(s);
  ASSERT_EQ(n.to_string(), s);
}
TEST(UnlimitedNaturalSum, Basic){
  UnlimitedNatural n1("2332");
  UnlimitedNatural n2("232");
  UnlimitedNatural* n3 = UnlimitedNatural::add(&n1, &n2);
  ASSERT_EQ("2564", n3->to_string());
  delete n3;
}
TEST(UnlimitedNaturalSum, LongLong){
  long long i1 = 2102330999939481029;
  long long i2 = 2304923099234809298;
  std::string s1 = std::to_string(i1);
  std::string s2 = std::to_string(i2);
  UnlimitedNatural n1(s1);
  UnlimitedNatural n2(s2);
  std::string res = std::to_string(i1 + i2);
  UnlimitedNatural* n3 = UnlimitedNatural::add(&n1, &n2);
  ASSERT_EQ(n3->to_string(), res);
  delete n3;
}
// TEST(UnlimitedNaturalSum, LongLongUltimate){
//   std::ifstream fin;
//   std::ofstream fout;
//   fin.open("tests/test_cases.txt");
//   fout.open("tests/addition_cpp.txt");
//   std::string s1;
//   std::string s2;
//   while(!(fin.eof())){
//     fin >> s1;
//     fin >> s2;
//     UnlimitedNatural n1(s1);
//     UnlimitedNatural n2(s2);
//     UnlimitedNatural* n3 = UnlimitedNatural::add(&n1, &n2);
//     fout << n3->to_string() << "\n";
//     delete n3;
//   }

// }
TEST(ReverseString, Basic){
  std::string s = "hello";
  UnlimitedNatural::reverse_string(s);
  ASSERT_EQ("olleh", s);
}

TEST(tensComplementSingleDigit, Basic){
  char c = '5';
  char complement = UnlimitedNatural::tensComplementSingleDigit(c);
  ASSERT_EQ(complement, '4');
}

TEST(tensComplement, Basic){
  UnlimitedNatural n("45");
  UnlimitedNatural* complement = UnlimitedNatural::tensComplement(n.to_string());
  ASSERT_EQ(complement->to_string(), "55");
  delete complement;
}

TEST(pad, Basic){
  std::string s = "1234";
  ASSERT_EQ(UnlimitedNatural::pad(s, 4), "00001234");
}

TEST(UnlimitedNaturalLStrip, Basic){
  ASSERT_EQ(UnlimitedNatural::lstrip("123", 2), "23");
}
TEST(UnlimitedNaturalRemoveLeadingZeroes, Basic){
  ASSERT_EQ(UnlimitedNatural::remove_leading_zeroes("000012"), "12");
}
TEST(UnlimitedNaturalRemoveLeadingZeroes, ZeroTest){
  ASSERT_EQ(UnlimitedNatural::remove_leading_zeroes("00000"), "0");
}
TEST(UnlimitedNaturalSub, Basic){
  UnlimitedNatural i1("4");
  UnlimitedNatural i2("3");
  UnlimitedNatural* i3 = UnlimitedNatural::sub(&i1, &i2);
  ASSERT_EQ(i3->to_string(), "1");
  delete i3;
}
TEST(UnlimitedNaturalSub, LeadingZeroes){
  UnlimitedNatural i1("11");
  UnlimitedNatural i2("11");

  UnlimitedNatural* i3 = UnlimitedNatural::sub(&i1, &i2);
  ASSERT_EQ(i3->to_string(), "0");
  delete i3;
}

TEST(UnlimitedNaturalSub, LongLongTest){
  UnlimitedNatural i1("239873418237498");
  UnlimitedNatural i2("239048092384");
  long long li1 = 239873418237498;
  long long li2 = 239048092384;
  UnlimitedNatural* i3 = UnlimitedNatural::sub(&i1, &i2);
  ASSERT_EQ(std::to_string(li1 - li2), i3->to_string());
  delete i3;
}
