/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
using namespace std;
class UnlimitedNatural {
    int size;
    int capacity;
    int *unlimited_natural;

   public:
    UnlimitedNatural();
    UnlimitedNatural(std::string s);
    UnlimitedNatural(int i);  // Create from int

    UnlimitedNatural(int *ulimited_natural, int cap, int sz);

    ~UnlimitedNatural();  // Done

    // Return the size of the unlimited int
    int get_size();  // Done

    // Return the unlimited_int array
    int *get_array();  // Done

    int get_capacity();  // Done

    // Implement these integer operations as they are defined for integers in
    // mathematics (Since there are no size restrictions)
    static UnlimitedNatural *add(UnlimitedNatural *n1,
                                 UnlimitedNatural *n2);  // Done
    static UnlimitedNatural *sub(UnlimitedNatural *i1,
                                 UnlimitedNatural *i2);  // Done
    static UnlimitedNatural *mul(UnlimitedNatural *i1,
                                 UnlimitedNatural *i2);  // Done
    static UnlimitedNatural *div(UnlimitedNatural *i1, UnlimitedNatural *i2);
    static UnlimitedNatural *mod(UnlimitedNatural *i1, UnlimitedNatural *i2);
    static std::string add_string(std::string s1, std::string s2);
    static std::string sub_string(std::string s1, std::string s2);
    static std::string mul_string(std::string s1, std::string s2);
    static std::string div_string(std::string s1, std::string s2);
    static std::string mod_string(std::string s1, std::string s2);

    // Conversion Functions
    std::string to_string();  // Done
};
struct UnlimitedNaturalUtil {
    static void reverse_string(std::string &s);
    static void simpleAdd(const int c1, const int c2, const int prev_carry,
                          int &sum, int &carry);
    static std::string simpleHalfAdd(const char c1, const char c2);
    static char tensComplementSingleDigit(char c);
    static std::string tensComplement(std::string n);
    static void pad(std::string &s, int extra);
    static void lstrip(std::string &s, int size);
    static std::string remove_leading_zeroes(std::string s);
    static std::string multiply_one_row(std::string s1, char c);
    static int single_digit_multiplication(char c1, char c2);
    static void pad_right(std::string &s, int padding_size);
    static void two_by_one_division(int un_1, int un_2, int vn_1, int &quotient,
                                    int &remainder);
    static void by_n_division(std::string dividend, std::string divisor,
                              int &quotient, std::string &remainder);
    static bool is_greater_than(std::string &s1, std::string &s2);
};

struct UnlimitedIntUtil {
    static std::string get_abs_string(UnlimitedInt *ui1) {
        std::string res = ui1->to_string();
        if (res[0] == '-') {
            res.erase(0, 1);
        }
        return res;
    }
    static std::string add_string(std::string s1, std::string s2, int sign1,
                                  int sign2);
    static std::string sub_string(std::string s1, std::string s2, int sign1,
                                  int sign2);
    static std::string mul_string(std::string s1, std::string s2, int sign1,
                                  int sign2);
    static std::string div_string(std::string s1, std::string s2, int sign1,
                                  int sign2);
    static std::string mod_string(std::string s1, std::string s2, int sign1,
                                  int sign2);
};
int UnlimitedInt::get_sign() { return this->sign; }
int UnlimitedInt::get_size() { return this->size; }
int UnlimitedInt::get_capacity() { return this->capacity; }

UnlimitedInt::UnlimitedInt(int *ulimited_int, int cap, int sgn, int sz) {
    this->capacity = cap;
    this->sign = sgn;
    this->size = sz;
    this->unlimited_int = new int[size];
    for (int i = 0; i < size; i++) {
        this->unlimited_int[i] = ulimited_int[i];
    }
}  // Complete constructor

UnlimitedInt::UnlimitedInt(int i) : UnlimitedInt{std::to_string(i)} {}

UnlimitedInt::UnlimitedInt(string s) {
    if (s[0] == '-') {
        this->sign = -1;
        this->size = s.length() - 1;
        this->unlimited_int = new int[size];
        for (int i = 1; i <= size; i++) {
            unlimited_int[i - 1] = s[i] - '0';
        }
    } else {
        this->sign = 1;
        this->size = s.length();
        this->unlimited_int = new int[size];
        for (int i = 0; i < size; i++) {
            unlimited_int[i] = s[i] - '0';
        }
    }
    this->capacity = size;
}
int *UnlimitedInt::get_array() { return this->unlimited_int; }
UnlimitedInt::~UnlimitedInt() { delete[] unlimited_int; }
string UnlimitedInt::to_string() {
    int *temp = this->get_array();
    string res = "";
    for (int i = 0; i < this->size; i++) {
        res += std::to_string(temp[i]);
    }
    if (this->sign == -1 && res != "0") {
        res.insert(res.begin(), '-');
    }
    return res;
}
UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2) {
    std::string n1 = UnlimitedIntUtil::get_abs_string(i1);
    std::string n2 = UnlimitedIntUtil::get_abs_string(i2);
    return new UnlimitedInt(
        UnlimitedIntUtil::add_string(n1, n2, i1->get_sign(), i2->get_sign()));
}
UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2) {
    std::string n1 = UnlimitedIntUtil::get_abs_string(i1);
    std::string n2 = UnlimitedIntUtil::get_abs_string(i2);
    return new UnlimitedInt(
        UnlimitedIntUtil::sub_string(n1, n2, i1->get_sign(), i2->get_sign()));
}
UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2) {
    std::string n1 = UnlimitedIntUtil::get_abs_string(i1);
    std::string n2 = UnlimitedIntUtil::get_abs_string(i2);
    return new UnlimitedInt(
        UnlimitedIntUtil::mul_string(n1, n2, i1->get_sign(), i2->get_sign()));
}
UnlimitedInt *UnlimitedInt::div(UnlimitedInt *i1, UnlimitedInt *i2) {
    std::string n1 = UnlimitedIntUtil::get_abs_string(i1);
    std::string n2 = UnlimitedIntUtil::get_abs_string(i2);
    return new UnlimitedInt(
        UnlimitedIntUtil::div_string(n1, n2, i1->get_sign(), i2->get_sign()));
}
UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2) {
    std::string n1 = UnlimitedIntUtil::get_abs_string(i1);
    std::string n2 = UnlimitedIntUtil::get_abs_string(i2);
    return new UnlimitedInt(
        UnlimitedIntUtil::mod_string(n1, n2, i1->get_sign(), i2->get_sign()));
}
// ------------------------- Unlimited Int Util ----------------------
std::string UnlimitedIntUtil::add_string(std::string s1, std::string s2,
                                         int sign1, int sign2) {
    std::string res;
    if (sign1 == 1 && sign2 == 1) {
        res = UnlimitedNatural::add_string(s1, s2);
    } else if (sign1 == -1 && sign2 == -1) {
        res = UnlimitedNatural::add_string(s1, s2);
        res.insert(res.begin(), '-');
    } else if (sign1 == -1 && sign2 == 1) {
        if (UnlimitedNaturalUtil::is_greater_than(s1, s2)) {
            res = UnlimitedNatural::sub_string(s1, s2);
            res.insert(res.begin(), '-');
        } else {
            res = UnlimitedNatural::sub_string(s2, s1);
        }
    } else if (sign1 == 1 && sign2 == -1) {
        if (UnlimitedNaturalUtil::is_greater_than(s1, s2)) {
            res = UnlimitedNatural::sub_string(s1, s2);
        } else {
            res = UnlimitedNatural::sub_string(s2, s1);
            res.insert(res.begin(), '-');
        }
    }
    return res;
}
std::string UnlimitedIntUtil::sub_string(std::string s1, std::string s2,
                                         int sign1, int sign2) {
    return UnlimitedIntUtil::add_string(s1, s2, sign1, -1 * sign2);
}
std::string UnlimitedIntUtil::mul_string(std::string s1, std::string s2,
                                         int sign1, int sign2) {
    std::string res = UnlimitedNatural::mul_string(s1, s2);
    if (sign1 * sign2 == -1) {
        res.insert(res.begin(), '-');
    }
    return res;
}
std::string UnlimitedIntUtil::div_string(std::string s1, std::string s2,
                                         int sign1, int sign2) {
    std::string res = UnlimitedNatural::div_string(s1, s2);
    if (sign1 * sign2 == -1) {
        std::string remainder = UnlimitedNatural::mod_string(s1, s2);
        if (remainder != "0") {
            res = UnlimitedNatural::add_string(res, "1");
        }
        res.insert(res.begin(), '-');
    }
    return res;
}
std::string UnlimitedIntUtil::mod_string(std::string a, std::string b,
                                         int sign1, int sign2) {
    // r = a - (b * floor(a/b))
    UnlimitedInt *a_div_b =
        new UnlimitedInt(UnlimitedIntUtil::div_string(a, b, sign1, sign2));
    UnlimitedInt *b_times_a_div_b = new UnlimitedInt(
        UnlimitedIntUtil::mul_string(UnlimitedIntUtil::get_abs_string(a_div_b),
                                     b, a_div_b->get_sign(), sign2));
    std::string res = UnlimitedIntUtil::sub_string(
        a, UnlimitedIntUtil::get_abs_string(b_times_a_div_b), sign1,
        b_times_a_div_b->get_sign());
    delete a_div_b;
    delete b_times_a_div_b;
    return res;
}
// ------------------------- Unlimited Natural ------------------------

UnlimitedNatural::UnlimitedNatural(int *unlimited_natural, int size,
                                   int capacity) {
    this->size = size;
    this->capacity = capacity;
    this->unlimited_natural = new int[size];
    for (int i = 0; i < size; i++) {
        this->unlimited_natural[i] = unlimited_natural[i];
    }
}
UnlimitedNatural::UnlimitedNatural(std::string s) {
    this->unlimited_natural = new int[s.size()];
    this->size = s.size();
    this->capacity = size;
    for (size_t i = 0; i < s.size(); i++) {
        this->unlimited_natural[i] = s[i] - '0';
    }
};
UnlimitedNatural::~UnlimitedNatural() { delete[] unlimited_natural; };

UnlimitedNatural::UnlimitedNatural(int i)
    : UnlimitedNatural{std::to_string(i)} {}

int UnlimitedNatural::get_size() { return this->size; };  // Done

int *UnlimitedNatural::get_array() { return this->unlimited_natural; };  // Done

int UnlimitedNatural::get_capacity() { return this->capacity; };  // Done

UnlimitedNatural *UnlimitedNatural::add(UnlimitedNatural *n1,
                                        UnlimitedNatural *n2) {
    std::string s1 = n1->to_string();
    std::string s2 = n2->to_string();
    return new UnlimitedNatural(UnlimitedNatural::add_string(s1, s2));
}
std::string UnlimitedNatural::add_string(std::string s1, std::string s2) {
    std::string s3 = "";
    if (s1.size() == 0) {
        return s2;
    } else if (s2.size() == 0) {
        return s1;
    }
    int sum, carry;
    UnlimitedNaturalUtil::simpleAdd(s1[s1.size() - 1] - '0',
                                    s2[s2.size() - 1] - '0', 0, sum, carry);
    s3 += std::to_string(sum);
    size_t i = 1;
    while (i < std::min(s1.size(), s2.size())) {
        UnlimitedNaturalUtil::simpleAdd(s1[s1.size() - i - 1] - '0',
                                        s2[s2.size() - i - 1] - '0', carry,
                                        sum, carry);
        s3 += std::to_string(sum);
        i++;
    }
    while (i < s1.size()) {
        UnlimitedNaturalUtil::simpleAdd(s1[s1.size() - i - 1] - '0', 0,
        carry,
                                        sum, carry);
        s3 += std::to_string(sum);
        i++;
    }
    while (i < s2.size()) {
        UnlimitedNaturalUtil::simpleAdd(0, s2[s2.size() - i - 1] - '0',
        carry,
                                        sum, carry);
        s3 += std::to_string(sum);
        i++;
    }
    if (carry != 0) {
        s3 += std::to_string(carry);
    }
    UnlimitedNaturalUtil::reverse_string(s3);
    return s3;
}
// std::string UnlimitedNatural::add_string(std::string s1, std::string s2) {
//     std::string s3 = "";
//     int sum = 0, carry = 0;
//     int i = 0;
//     while (i + 8 < std::min(s1.size(), s2.size())) {
//         UnlimitedNaturalUtil::simpleAdd(std::stoi(s1.substr(i, 8)),
//                                         std::stoi(s2.substr(i, 8)), carry, sum,
//                                         carry);
//         s3 = std::to_string(sum) + s3;
//         i += 8;
//     }
//     // Terminated while loop because of s2
//     if (i < s1.size() && i < s2.size() && s1.size() > s2.size()) {
//         UnlimitedNaturalUtil::simpleAdd(std::stoi(s1.substr(i, s2.size() - i)),
//                                         std::stoi(s2.substr(i, s2.size() - i)),
//                                         carry, sum, carry);
//         s3 = std::to_string(sum) + s3;
//         i = s2.size();
//         while (i + 8 < s1.size()) {
//             UnlimitedNaturalUtil::simpleAdd(std::stoi(s1.substr(i, 8)), 0,
//                                             carry, sum, carry);
//             s3 = std::to_string(sum) + s3;
//             i += 8;
//         }
//         if (i < s1.size()) {
//             UnlimitedNaturalUtil::simpleAdd(
//                 std::stoi(s1.substr(i, s1.size() - i)), 0, carry, sum, carry);
//             s3 = std::to_string(sum) + s3;
//         }
//         // Terminated while loop because of s1
//         else if (i < s1.size() && i < s2.size() && s1.size() <= s2.size()) {
//             UnlimitedNaturalUtil::simpleAdd(
//                 std::stoi(s1.substr(i, s1.size() - i)),
//                 std::stoi(s2.substr(i, s1.size() - i)), carry, sum, carry);
//             s3 = std::to_string(sum) + s3;
//             i = s1.size();
//             while (i + 8 < s2.size()) {
//                 UnlimitedNaturalUtil::simpleAdd(std::stoi(s2.substr(i, 8)), 0,
//                                                 carry, sum, carry);
//                 s3 = std::to_string(sum) + s3;
//                 i += 8;
//             }
//             if (i < s2.size()) {
//                 UnlimitedNaturalUtil::simpleAdd(
//                     std::stoi(s2.substr(i, s2.size() - i)), 0, carry, sum,
//                     carry);
//                 s3 = std::to_string(sum) + s3;
//                 i += 8;
//             }
//         }
//     }
//     return s3;
// }
UnlimitedNatural *UnlimitedNatural::sub(UnlimitedNatural *i1,
                                        UnlimitedNatural *i2) {
    std::string s1 = i1->to_string();
    std::string s2 = i2->to_string();
    return new UnlimitedNatural(sub_string(s1, s2));
}
std::string UnlimitedNatural::sub_string(std::string s1, std::string s2) {
    UnlimitedNaturalUtil::pad(s2, s1.size() - s2.size());
    std::string i2_complement = UnlimitedNaturalUtil::tensComplement(s2);
    std::string res_with_extra_carry_raw =
        UnlimitedNatural::add_string(s1, i2_complement);
    std::string res;
    if (res_with_extra_carry_raw.size() > s1.size()) {
        res = res_with_extra_carry_raw.erase(0, 1);
    } else {
        res = res_with_extra_carry_raw;
    }
    UnlimitedNaturalUtil::lstrip(res, s1.size());
    res = UnlimitedNaturalUtil::remove_leading_zeroes(res);
    return res;
}

std::string UnlimitedNatural::mul_string(std::string s1, std::string s2) {
    std::string res = "0";
    if (s1 == "0" || s2 == "0") {
        return "0";
    }
    for (int i = s2.size() - 1; i > -1; i--) {
        std::string row_product =
            UnlimitedNaturalUtil::multiply_one_row(s1, s2[i]);

        UnlimitedNaturalUtil::pad_right(row_product, s2.size() - i - 1);
        res = UnlimitedNatural::add_string(res, row_product);
    }
    return res;
}
UnlimitedNatural *UnlimitedNatural::mul(UnlimitedNatural *i1,
                                        UnlimitedNatural *i2) {
    std::string s1 = i1->to_string();
    std::string s2 = i2->to_string();
    return new UnlimitedNatural(mul_string(s1, s2));
}
std::string UnlimitedNatural::to_string() {
    std::string s = "";
    for (int i = 0; i < this->size; i++) {
        s += std::to_string(this->unlimited_natural[i]);
    }
    return s;
};

std::string UnlimitedNatural::div_string(std::string dividend,
                                         std::string divisor) {
    std::string quotient;
    int cur_quotient;
    std::string one = "1";
    if (divisor == "0") {
        return "";
    }
    if (dividend.size() < divisor.size()) {
        return "0";
    }
    std::string remainder = dividend.substr(0, divisor.size() - 1);
    size_t cur_index = divisor.size() - 1;
    std::string cur_dividend = remainder;
    while (cur_index < dividend.size()) {
        cur_dividend += dividend[cur_index];
        // Guarantees quotient is single digit
        UnlimitedNaturalUtil::by_n_division(cur_dividend, divisor, cur_quotient,
                                            remainder);
        cur_dividend = remainder;
        if (cur_dividend == "0") {
            cur_dividend = "";
        }
        cur_index++;
        quotient += std::to_string(cur_quotient);
    }
    quotient = UnlimitedNaturalUtil::remove_leading_zeroes(quotient);
    return quotient;
}
std::string UnlimitedNatural::mod_string(std::string dividend,
                                         std::string divisor) {
    // a - b [a / b]
    std::string a_div_b = UnlimitedNatural::div_string(dividend, divisor);
    std::string b_times_a_div_b =
        UnlimitedNatural::mul_string(a_div_b, divisor);
    return UnlimitedNatural::sub_string(dividend, b_times_a_div_b);
}
UnlimitedNatural *UnlimitedNatural::div(UnlimitedNatural *i1,
                                        UnlimitedNatural *i2) {
    return new UnlimitedNatural(div_string(i1->to_string(), i2->to_string()));
}
UnlimitedNatural *UnlimitedNatural::mod(UnlimitedNatural *i1,
                                        UnlimitedNatural *i2) {
    return new UnlimitedNatural(mod_string(i1->to_string(), i2->to_string()));
}
// --------------------- Utility ----------------------------
void UnlimitedNaturalUtil::reverse_string(std::string &s) {
    for (size_t i = 0; i < s.size() / 2; i++) {
        std::swap(s[i], s[s.size() - i - 1]);
    }
}

void UnlimitedNaturalUtil::simpleAdd(const int i1, const int i2,
                                     const int prev_carry, int &sum,
                                     int &carry) {
    int res = i1 + i2 + prev_carry;
    sum = res % 10;
    carry = res / 10;
}

std::string UnlimitedNaturalUtil::simpleHalfAdd(const char c1, const char c2) {
    const int i1 = c1 - '0';
    const int i2 = c2 - '0';
    return std::to_string(i1 + i2);
}

void UnlimitedNaturalUtil::pad(std::string &s, int extra) {
    std::string zero(extra, '0');
    s.insert(0, zero);
}
char UnlimitedNaturalUtil::tensComplementSingleDigit(char c) {
    int complement = 9 - (c - '0');
    return std::to_string(complement)[0];
}

std::string UnlimitedNaturalUtil::tensComplement(std::string n) {
    std::string res = "";
    for (size_t i = 0; i < n.size(); i++) {
        res += tensComplementSingleDigit(n[i]);
    }
    std::string one = "1";
    return UnlimitedNatural::add_string(res, one);
}

void UnlimitedNaturalUtil::lstrip(std::string &s, int size) {
    s.erase(0, s.size() - size);
    if (s.size() == 0) {
        s = "0";
    }
}

std::string UnlimitedNaturalUtil::remove_leading_zeroes(std::string s) {
    std::string sout = "";
    size_t i = 0;
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

int UnlimitedNaturalUtil::single_digit_multiplication(char c1, char c2) {
    int i1 = c1 - '0';
    int i2 = c2 - '0';
    return (i1 * i2);
}
void UnlimitedNaturalUtil::pad_right(std::string &s, int padding_size) {
    for (int i = 0; i < padding_size; i++) {
        s += "0";
    }
}
std::string UnlimitedNaturalUtil::multiply_one_row(std::string s1, char c) {
    std::string res = "";
    int sum, carry = 0;

    for (int i = s1.size() - 1; i > -1; i--) {
        int raw_product(single_digit_multiplication(s1[i], c));
        sum = (raw_product + carry) % 10;
        carry = (raw_product + carry) / 10;
        res += std::to_string(sum);
    }
    if (carry != 0) {
        res += std::to_string(carry);
    }
    UnlimitedNaturalUtil::remove_leading_zeroes(res);
    UnlimitedNaturalUtil::reverse_string(res);
    return res;
}
void UnlimitedNaturalUtil::two_by_one_division(int un_1, int un_2, int vn_1,
                                               int &quotient, int &remainder) {
    int dividend = un_1 * 10 + un_2;
    quotient = dividend / vn_1;
    remainder = dividend % vn_1;
}
bool UnlimitedNaturalUtil::is_greater_than(std::string &s1, std::string &s2) {
    if (s1.size() > s2.size()) {
        return true;
    } else if (s1.size() < s2.size()) {
        return false;
    }
    for (size_t i = 0; i < s1.size(); i++) {
        if (s1[i] - '0' < s2[i] - '0') {
            return false;
        }
        if (s1[i] - '0' > s2[i] - '0') {
            return true;
        }
    }
    return false;
}
void UnlimitedNaturalUtil::by_n_division(std::string dividend,
                                         std::string divisor, int &quotient,
                                         std::string &remainder) {
    quotient = -1;
    std::string current = "0";
    std::string prev_current = "0";
    while (is_greater_than(dividend, current)) {
        prev_current = current;
        current = UnlimitedNatural::add_string(current, divisor);
        quotient++;
    }
    if (dividend == current) {
        quotient++;
        remainder = "0";
    } else {
        remainder = UnlimitedNatural::sub_string(dividend, prev_current);
    }
}
