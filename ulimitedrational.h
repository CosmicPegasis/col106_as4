#pragma once
#include <string>

#include "ulimitedint.h"
using namespace std;

class UnlimitedRational {
   private:
    UnlimitedInt* p;
    UnlimitedInt* q;

   public:
    UnlimitedRational();                                      // Done
    UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den);  // Done

  ~UnlimitedRational(); // Done

  UnlimitedInt* get_p(); // Done

  UnlimitedInt* get_q(); // Done

    string get_p_str();  // Return the numerator as a string Done

    string get_q_str();  // Return the denominator as a string Done

    string get_frac_str();  // Return the rational as "p/q" Done

    // Rational arithmetic operations
  // Done
    static UnlimitedRational* add(UnlimitedRational* i1, UnlimitedRational* i2);
  // Done
    static UnlimitedRational* sub(UnlimitedRational* i1, UnlimitedRational* i2);
  // Done
    static UnlimitedRational* mul(UnlimitedRational* i1, UnlimitedRational* i2);
  // Done
    static UnlimitedRational* div(UnlimitedRational* i1, UnlimitedRational* i2);
};
