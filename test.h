#include <string>
#define UN UnlimitedNatural
class UN {
  int size;
  int capacity;
  int *unlimited_natural;

public:
  UN();
  UN(std::string s);
  UN(int i); // Create from int

  UN(int *ulimited_int, int cap, int sz);
                   
  ~UN();

  // Return the size of the unlimited int
  int get_size();

  // Return the unlimited_int array
  int *get_array();

  int get_capacity();

  // Implement these integer operations as they are defined for integers in
  // mathematics (Since there are no size restrictions)
  static UN *add(UN *n1, UN *n2);
  static UN *sub(UN *i1, UN *i2);
  static UN *mul(UN *i1, UN *i2);
  static UN *div(UN *i1, UN *i2);

  // Conversion Functions
  std::string to_string();
};
struct UNUtil {
  static void reverse_string(std::string &s);
  static void simpleAdd(const char c1, const char c2, const char prev_carry,
                        char &sum, char &carry);
  static std::string simpleHalfAdd(const char c1, const char c2);
  static char tensComplementSingleDigit(char c);
  static UN *tensComplement(std::string n);
  static std::string pad(std::string s, int extra);
  static std::string lstrip(std::string s, int size);
  static std::string remove_leading_zeroes(std::string s);
  static UN* multiply_one_row(UN* i1, char c);
  static std::string single_digit_multiplication(char c1, char c2);
  static std::string pad_right(std::string s, int padding_size);
};

UN::UN(std::string s) {
  this->unlimited_natural = new int[s.size()];
  this->size = s.size();
  this->capacity = size;
  for (int i = 0; i < s.size(); i++) {
    this->unlimited_natural[i] = s[i] - '0';
  }
}; 
UN::~UN() { delete[] unlimited_natural; };

int UN::get_size() { return this->size; }; // Done

int *UN::get_array() { return this->unlimited_natural; }; // Done

int UN::get_capacity() { return this->capacity; }; // Done

UN *UN::add(UN *n1,
                                        UN *n2) {
  std::string s1 = n1->to_string();
  std::string s2 = n2->to_string();
  std::string s3 = "";
  if (s1.size() == 0) {
    return new UN(s2);
  } else if (s2.size() == 0) {
    return new UN(s1);
  }
  char sum, carry;
  UNUtil::simpleAdd(s1[s1.size() - 1], s2[s2.size() - 1], '0',
                                     sum, carry);
  s3 += sum;
  int i = 1;
  while (i < std::min(s1.size(), s2.size())) {
    UNUtil::simpleAdd(
        s1[s1.size() - i - 1], s2[s2.size() - i - 1], carry, sum, carry);
    s3 += sum;
    i++;
  }
  while (i < s1.size()) {
    UNUtil::simpleAdd(s1[s1.size() - i - 1], '0', carry, sum,
                                       carry);
    s3 += sum;
    i++;
  }
  while (i < s2.size()) {
    UNUtil::simpleAdd('0', s2[s2.size() - i - 1], carry, sum,
                                       carry);
    s3 += sum;
    i++;
  }
  if (carry != '0') {
    s3 += carry;
  }
  UNUtil::reverse_string(s3);
  return new UN(s3);
}
UN *UN::sub(UN *i1,
                                        UN *i2) {
  std::string s1 = i1->to_string();
  std::string s2 = i2->to_string();
  s2 = UNUtil::pad(s2, s1.size() - s2.size());
  UN *i2_complement = UNUtil::tensComplement(s2);
  UN *res_with_extra_carry =
      UN::add(i1, i2_complement);
  std::string res_with_extra_carry_raw = res_with_extra_carry->to_string();
  std::string res;
  if (res_with_extra_carry_raw.size() > s1.size()) {
    res = res_with_extra_carry_raw.erase(0, 1);
  } else {
    res = res_with_extra_carry_raw;
  }
  res = UNUtil::lstrip(res, s1.size());
  res = UNUtil::remove_leading_zeroes(res);
  delete res_with_extra_carry;
  delete i2_complement;
  return new UN(res);
}

UN *UN::mul(UN* i1, UN* i2){
  std::string s2 = i2->to_string();
  UN* res = new UN("0");
  UN* temp;
  for(int i = s2.size() - 1; i > -1; i--){
    temp = UNUtil::multiply_one_row(i1, s2[i]);
    std::string raw_unpadded_row_product = temp->to_string();
    delete temp;

    std::string raw_row_product = UNUtil::pad_right(raw_unpadded_row_product, s2.size() - i - 1);
    UN row_product(raw_row_product);
    temp = UN::add(res, &row_product);
    delete res;
    res = temp;
  }
  return res;
}
std::string UN::to_string() {
  std::string s = "";
  for (int i = 0; i < this->size; i++) {
    s += std::to_string(this->unlimited_natural[i]);
  }
  return s;
};



// --------------------- Utility ----------------------------
void UNUtil::reverse_string(std::string &s) {
  for (int i = 0; i < s.size() / 2; i++) {
    std::swap(s[i], s[s.size() - i - 1]);
  }
}

void UNUtil::simpleAdd(const char c1, const char c2,
                                        const char prev_carry, char &sum,
                                        char &carry) {
  std::string add_res = simpleHalfAdd(c1, c2);
  std::string carry_res;
  if (add_res.size() == 1) {
    carry_res = simpleHalfAdd(add_res[0], prev_carry);
    // carry = "XX" add_res = "X"
    if (carry_res.size() == 2) {
      sum = carry_res[1];
      carry = carry_res[0];
    }
    // carry_res = "X" add_res = "X"
    else {
      sum = carry_res[0];
      carry = '0';
    }
  } else {
    carry_res = simpleHalfAdd(add_res[1], prev_carry);
    // carry_res = "XX" add_res = "XX"
    if (carry_res.size() == 2) {
      carry = simpleHalfAdd(carry_res[0],
                            add_res[0])[0]; // Guaranteed to be <= 2;
      sum = carry_res[1];
    }
    // carry_res = "X" add_res = "XX"
    else {
      carry = add_res[0];
      sum = carry_res[0];
    }
  }
}

std::string UNUtil::simpleHalfAdd(const char c1,
                                                   const char c2) {
  const int i1 = c1 - '0';
  const int i2 = c2 - '0';
  return std::to_string(i1 + i2);
}

std::string UNUtil::pad(std::string s, int extra) {
  std::string zero = "";
  for (int i = 0; i < extra; i++) {
    zero += "0";
  }
  s = zero + s;
  return s;
}
char UNUtil::tensComplementSingleDigit(char c) {
  int complement = 9 - (c - '0');
  return std::to_string(complement)[0];
}

UN *UNUtil::tensComplement(std::string n) {
  std::string res = "";
  for (int i = 0; i < n.size(); i++) {
    res += tensComplementSingleDigit(n[i]);
  }
  UN complement(res);
  UN one("1");
  return UN::add(&complement, &one);
}

std::string UNUtil::lstrip(std::string s, int size) {
  std::string sout = "";
  for (int i = s.size() - size; i < s.size(); i++) {
    sout += s[i];
  }
  return sout;
}

std::string UNUtil::remove_leading_zeroes(std::string s) {
  std::string sout = "";
  int i = 0;
  while (i < s.size() && s[i] == '0') {
    i++;
  };
  for (; i < s.size(); i++) {
    sout += s[i];
  }
  if (sout.size() == 0) {
    sout = "0";
  }
  return sout;
}

std::string UNUtil::single_digit_multiplication(char c1, char c2){
  int i1 = c1 - '0';
  int i2 = c2 - '0';
  return std::to_string(i1 * i2);
}
std::string UNUtil::pad_right(std::string s, int padding_size){
  std::string res = s;
  for(int i = 0; i < padding_size; i++){
    res += "0";
  }
  return res;
}
UN* UNUtil::multiply_one_row(UN* i1, char c){
  std::string s1 = i1->to_string();
  UN* initial = new UN("0");
  UN* temp;
  for(int i = s1.size() - 1; i > -1; i--){
    std::string raw_product(single_digit_multiplication(s1[i], c));
    raw_product = pad_right(raw_product, s1.size() - i - 1);
    UN product(raw_product);
    temp = UN::add(&product, initial);
    delete initial;
    initial = temp;
  }
  return initial;
}
