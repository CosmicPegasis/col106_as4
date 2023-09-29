#include <string>
class UnlimitedNatural {
  int size;
  int capacity;
  int *unlimited_natural;

public:
  UnlimitedNatural();
  UnlimitedNatural(std::string s){
    this->unlimited_natural = new int[s.size()];
    this->size = s.size();
    this->capacity = size;
    for(int i = 0; i < s.size(); i++){
      this->unlimited_natural[i] = s[i] - '0';
    }
  }; // Create from string
  UnlimitedNatural(int i);         // Create from int
  UnlimitedNatural(int *ulimited_int, int cap, int sgn,
                   int sz); //
  ~UnlimitedNatural(){
    delete[] unlimited_natural;
  };

  // Return the size of the unlimited int
  int get_size() { return this->size; }; // Done

  // Return the unlimited_int array
  int *get_array() { return this->unlimited_natural; }; // Done

  int get_capacity() { return this->capacity; }; // Done

  // Implement these integer operations as they are defined for integers in
  // mathematics (Since there are no size restrictions)
  static std::string simpleHalfAdd(const char c1, const char c2) {
    const int i1 = c1 - '0';
    const int i2 = c2 - '0';
    return std::to_string(i1 + i2);
  }
  static void simpleAdd(const char c1, const char c2, const char prev_carry,
                        char &sum, char &carry) {
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
        carry = simpleHalfAdd(carry_res[0], add_res[0])[0]; // Guaranteed to be <= 2;
        sum = carry_res[1];
      }
      // carry_res = "X" add_res = "XX"
      else {
        carry = add_res[0];
        sum = carry_res[0];
      }
    }
  }
  static void reverse_string(std::string& s){
    for(int i = 0; i < s.size() / 2; i++){
      std::swap(s[i], s[s.size() - i - 1]);
    }
  }
  static char tensComplementSingleDigit(char c){
    int complement = 9 - (c - '0');
    return std::to_string(complement)[0];
  }
  static UnlimitedNatural* tensComplement(std::string n){
    std::string res = "";
    for(int i = 0; i < n.size(); i++){
      res += tensComplementSingleDigit(n[i]);
    }
    UnlimitedNatural complement(res);
    UnlimitedNatural one("1");
    return UnlimitedNatural::add(&complement, &one);
  }
  static std::string pad(std::string s, int extra){
    std::string zero = "";
    for(int i = 0; i < extra; i++){
      zero += "0";
    }
    s = zero + s;
    return s;
  }
  static std::string lstrip(std::string s, int size){
    std::string sout = "";
    for(int i = s.size() - size; i < s.size(); i++){
      sout += s[i];
    }
    return sout;
  }
  static std::string remove_leading_zeroes(std::string s){
    std::string sout = "";
    int i = 0;
    while(i < s.size() && s[i] == '0'){
      i++;
    };
    for(; i < s.size(); i++){
      sout += s[i];
    }
    if (sout.size() == 0){
      sout = "0";
    }
    return sout;
  }
  static UnlimitedNatural *add(UnlimitedNatural *n1, UnlimitedNatural *n2){
    std::string s1 = n1->to_string();
    std::string s2 = n2->to_string();
    std::string s3 = "";
    if(s1.size() == 0){
      return new UnlimitedNatural(s2);
    }
    else if(s2.size() == 0){
      return new UnlimitedNatural(s1);
    }
    char sum, carry;
    simpleAdd(s1[s1.size() - 1], s2[s2.size() - 1], '0', sum, carry);
    s3 += sum;
    int i = 1;
    while(i < std::min(s1.size(), s2.size())){
      simpleAdd(s1[s1.size() - i - 1], s2[s2.size() - i - 1], carry, sum, carry);
      s3 += sum;
      i++;
    }
    while(i < s1.size()){
      simpleAdd(s1[s1.size() - i - 1], '0', carry, sum, carry);
      s3 += sum;
      i++;
    }
    while(i < s2.size()){
      simpleAdd('0', s2[s2.size() - i - 1], carry, sum, carry);
      s3 += sum;
      i++;
    }
    if(carry != '0'){
      s3 += carry;
    }
    reverse_string(s3);
    return new UnlimitedNatural(s3);
  }
  static UnlimitedNatural *sub(UnlimitedNatural *i1, UnlimitedNatural *i2){
    std::string s1 = i1->to_string();
    std::string s2 = i2->to_string();
    s2 = UnlimitedNatural::pad(s2, s1.size() - s2.size());
    UnlimitedNatural *i2_complement = UnlimitedNatural::tensComplement(s2);
    UnlimitedNatural *res_with_extra_carry = UnlimitedNatural::add(i1, i2_complement);
    std::string res_with_extra_carry_raw = res_with_extra_carry->to_string();
    std::string res;
    if(res_with_extra_carry_raw.size() > s1.size()){
      res = res_with_extra_carry_raw.erase(0,1);
    }
    else{
      res =  res_with_extra_carry_raw;
    }
    res = UnlimitedNatural::lstrip(res, s1.size());
    res = UnlimitedNatural::remove_leading_zeroes(res);
    delete res_with_extra_carry;
    delete i2_complement;
    return new UnlimitedNatural(res);
  }
  static UnlimitedNatural *mul(UnlimitedNatural *i1, UnlimitedNatural *i2);
  static UnlimitedNatural *div(UnlimitedNatural *i1, UnlimitedNatural *i2);

  // Conversion Functions
  std::string to_string(){
    std::string s = "";
    for(int i = 0; i < this->size; i++){
      s += std::to_string(this->unlimited_natural[i]);
    }
    return s;
  };
};
