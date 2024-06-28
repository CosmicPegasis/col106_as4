#include <gtest/gtest.h>

#include <fstream>
#include <numeric>

#include "ulimitedrational.cpp"
#include "ulimitedrational.h"

TEST(UnlimitedRationalGCD, Basic) {
    UnlimitedInt p("12");
    UnlimitedInt q("8");
    UnlimitedInt* g = UnlimitedRationalUtil::gcd(&p, &q);
    ASSERT_EQ(g->to_string(), "4");
}

// TEST(UnlimitedRationalGCD,LongLongUltimate){
//   std::ifstream fin;
//   std::ofstream fout;
//   fin.open("tests/test_cases.txt");
//   fout.open("tests/gcd_cpp.txt");
//   std::string s1;
//   std::string s2;
//   while(!(fin.eof())){
//     fin >> s1;
//     fin >> s2;
//     UnlimitedInt n1(s1);
//     UnlimitedInt n2(s2);
//     UnlimitedInt* n3 = UnlimitedRationalUtil::gcd(&n1, &n2);
//     fout << n3->to_string() << "\n";
//     delete n3;
//   }
// }

TEST(UnlimitedRationalConstructor, Basic) {
    UnlimitedInt* p = new UnlimitedInt("8");
    UnlimitedInt* q = new UnlimitedInt("12");

    UnlimitedRational res(p, q);
    delete p;
    delete q;

    ASSERT_EQ(res.get_frac_str(), "2/3");
}
TEST(URConstructor, LongLongUltimate) {
    std::ifstream fin;
    std::ofstream fout;
    fin.open("tests/test_cases.txt");
    fout.open("tests/rational_cpp.txt");
    std::string s1;
    std::string s2;
    while (!(fin.eof())) {
        fin >> s1;
        fin >> s2;
        UnlimitedInt n1(s1);
        UnlimitedInt n2(s2);
        UnlimitedRational* n3 = new UnlimitedRational(&n1, &n2);
        fout << n3->get_frac_str() << "\n";
        delete n3;
    }
}

// TEST(UnlimitedRationalUtilLCM, Basic){
//   UnlimitedInt p("9");
//   UnlimitedInt q("6");
//   ASSERT_EQ(UnlimitedRationalUtil::lcm_string(&p, &q), "18");
// }

// TEST(UnlimitedRationalUtilLCM, LongLong){
//   long long i1 = 230909832049;
//   long long i2 = 23832310;
//   UnlimitedInt p(std::to_string(i1));
//   UnlimitedInt q(std::to_string(i2));
//   ASSERT_EQ(UnlimitedRationalUtil::lcm_string(&p, &q), std::to_string(std::lcm(i1, i2)));
// }

// TEST(UnlimitedRationalUtilLCM, LongLongUltimate){
//   std::ifstream fin;
//   std::ofstream fout;
//   fin.open("tests/test_cases.txt");
//   fout.open("tests/lcm_cpp.txt");
//   std::string s1;
//   std::string s2;
//   while(!(fin.eof())){
//     fin >> s1;
//     fin >> s2;
//     UnlimitedInt n1(s1);
//     UnlimitedInt n2(s2);
//     UnlimitedInt* n3 = UnlimitedRationalUtil::lcm(&n1, &n2);
//     fout << n3->to_string() << "\n";
//     delete n3;
//   }
// }

TEST(UnlimitedRationalAdd, Basic) {
    UnlimitedInt p1("2");
    UnlimitedInt p2("3");
    UnlimitedInt q1("2");
    UnlimitedInt q2("4");
    UnlimitedRational i1(&p1, &q1);  // 1/1
    UnlimitedRational i2(&p2, &q2);  // 3/4
    UnlimitedRational* i3 = UnlimitedRational::add(&i1, &i2);
    ASSERT_EQ("7/4", i3->get_frac_str());
    delete i3;
}

TEST(UnlimitedRationalAdd, LongLongUltimate) {
    std::ifstream fin;
    std::ofstream fout;
    fin.open("tests/rational_test_cases.txt");
    fout.open("tests/addition_rational_cpp.txt");
    std::string p1;
    std::string q1;
    std::string p2;
    std::string q2;
    while (!(fin.eof())) {
        fin >> p1;
        fin >> q1;
        fin >> p2;
        fin >> q2;
        UnlimitedInt i1(p1);
        UnlimitedInt i2(q1);
        UnlimitedInt i3(p2);
        UnlimitedInt i4(q2);
        UnlimitedRational r1(&i1, &i2);
        UnlimitedRational r2(&i3, &i4);
        UnlimitedRational* r3 = UnlimitedRational::add(&r1, &r2);
        fout << r3->get_frac_str() << "\n";
        delete r3;
    }
}
TEST(UnlimitedRationalDiv, LongLongUltimate) {
    std::ifstream fin;
    std::ofstream fout;
    fin.open("tests/rational_test_cases.txt");
    fout.open("tests/division_rational_cpp.txt");
    std::string p1;
    std::string q1;
    std::string p2;
    std::string q2;
    while (!(fin.eof())) {
        fin >> p1;
        fin >> q1;
        fin >> p2;
        fin >> q2;
        UnlimitedInt i1(p1);
        UnlimitedInt i2(q1);
        UnlimitedInt i3(p2);
        UnlimitedInt i4(q2);
        UnlimitedRational r1(&i1, &i2);
        UnlimitedRational r2(&i3, &i4);
        UnlimitedRational* r3 = UnlimitedRational::div(&r1, &r2);
        fout << r3->get_frac_str() << "\n";
        delete r3;
    }
}

TEST(UnlimitedRationalZeroZero, Constructor){
  UnlimitedInt i1("0");
  UnlimitedInt i2("0");
  // UnlimitedInt i3("32089");
  // UnlimitedInt i4("324098");
  UnlimitedRational r1(&i1, &i2);
  ASSERT_EQ(r1.get_frac_str(), "0/0");
}

TEST(UnlimitedRationalZeroZero, Addition){
  UnlimitedInt i1("0");
  UnlimitedInt i2("0");
  UnlimitedInt i3("32089");
  UnlimitedInt i4("324098");
  UnlimitedRational r1(&i1, &i2);
  UnlimitedRational r2(&i3, &i4);
  UnlimitedRational* r3 = UnlimitedRational::add(&r1, &r2);
  ASSERT_EQ(r1.get_frac_str(), "0/0");
  delete r3;
}
TEST(UnlimitedRationalZeroZero, Subtraction){
  UnlimitedInt i1("0");
  UnlimitedInt i2("0");
  UnlimitedInt i3("32089");
  UnlimitedInt i4("324098");
  UnlimitedRational r1(&i1, &i2);
  UnlimitedRational r2(&i3, &i4);
  UnlimitedRational* r3 = UnlimitedRational::sub(&r1, &r2);
  ASSERT_EQ(r1.get_frac_str(), "0/0");
  delete r3;
}

TEST(UnlimitedRationalZeroZero, Multiplication){
  UnlimitedInt i1("0");
  UnlimitedInt i2("0");
  UnlimitedInt i3("32089");
  UnlimitedInt i4("324098");
  UnlimitedRational r1(&i1, &i2);
  UnlimitedRational r2(&i3, &i4);
  UnlimitedRational* r3 = UnlimitedRational::mul(&r1, &r2);
  ASSERT_EQ(r1.get_frac_str(), "0/0");
  delete r3;
}

TEST(UnlimitedRationalZeroZero, Division){
  UnlimitedInt i1("0");
  UnlimitedInt i2("0");
  UnlimitedInt i3("32089");
  UnlimitedInt i4("324098");
  UnlimitedRational r1(&i1, &i2);
  UnlimitedRational r2(&i3, &i4);
  UnlimitedRational* r3 = UnlimitedRational::div(&r1, &r2);
  ASSERT_EQ(r1.get_frac_str(), "0/0");
  delete r3;
}
