/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

struct UnlimitedRationalUtil {
    static std::string gcd_string(UnlimitedInt* p, UnlimitedInt* q);
    static UnlimitedInt* gcd(UnlimitedInt* p, UnlimitedInt* q);
    static std::string get_abs_string(UnlimitedInt* ui1);
};
UnlimitedRational::UnlimitedRational() {
    p = nullptr;
    q = nullptr;
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den) {
    if (den->to_string() == "0") {
        p = new UnlimitedInt("0");
        q = new UnlimitedInt("0");
    } else {
        if (num->get_sign() * den->get_sign() == -1) {
            p = new UnlimitedInt(num->get_array(), num->get_capacity(), -1,
                                 num->get_size());
            q = new UnlimitedInt(den->get_array(), den->get_capacity(), 1,
                                 den->get_size());
        } else {
            p = new UnlimitedInt(num->get_array(), num->get_capacity(), 1,
                                 num->get_size());
            q = new UnlimitedInt(den->get_array(), den->get_capacity(), 1,
                                 den->get_size());
        }
        UnlimitedInt* g = UnlimitedRationalUtil::gcd(p, q);
        UnlimitedInt* tempp = p;
        UnlimitedInt* tempq = q;
        p = UnlimitedInt::div(p, g);
        q = UnlimitedInt::div(q, g);
        delete tempp;
        delete tempq;
        delete g;
    }
}
UnlimitedRational::~UnlimitedRational() {
    delete p;
    delete q;
}
UnlimitedInt* UnlimitedRational::get_p() { return p; }
UnlimitedInt* UnlimitedRational::get_q() { return q; }

string UnlimitedRational::get_p_str() { return p->to_string(); }

string UnlimitedRational::get_q_str() { return q->to_string(); }

string UnlimitedRational::get_frac_str() {
    return get_p_str() + "/" + get_q_str();
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1,
                                          UnlimitedRational* i2) {
    // Assumming both are simplified
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* q2 = i2->get_q();

    UnlimitedInt* p1q2 = UnlimitedInt::mul(p1, q2);
    UnlimitedInt* p2q1 = UnlimitedInt::mul(p2, q1);
    UnlimitedInt* num = UnlimitedInt::add(p1q2, p2q1);
    delete p1q2;
    delete p2q1;
    UnlimitedInt* den = UnlimitedInt::mul(q1, q2);
    UnlimitedRational* res = new UnlimitedRational(num, den);
    delete den;
    delete num;

    return res;
}
UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1,
                                          UnlimitedRational* i2) {
    UnlimitedInt neg_one("-1");
    UnlimitedInt* neg_q2 = UnlimitedInt::mul(i2->get_q(), &neg_one);
    UnlimitedRational neg_i2(i2->get_p(), neg_q2);
    UnlimitedRational* res = UnlimitedRational::add(i1, &neg_i2);
    delete neg_q2;

    return res;
}
UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1,
                                          UnlimitedRational* i2) {
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* q2 = i2->get_q();
    UnlimitedInt* prod_p = UnlimitedInt::mul(p1, p2);
    UnlimitedInt* prod_q = UnlimitedInt::mul(q1, q2);
    UnlimitedRational* res = new UnlimitedRational(prod_p, prod_q);
    delete prod_p;
    delete prod_q;
    return res;
}
UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1,
                                          UnlimitedRational* i2) {
    UnlimitedRational reciprocal_i2(i2->get_q(), i2->get_p());
    UnlimitedRational* res = UnlimitedRational::mul(i1, &reciprocal_i2);
    return res;
}
string UnlimitedRationalUtil::gcd_string(UnlimitedInt* p, UnlimitedInt* q) {
    UnlimitedInt* rp = UnlimitedInt::mod(p, q);
    if (rp->to_string() == "0") {
        delete rp;
        return get_abs_string(q);
    }
    UnlimitedInt r(rp->get_array(), rp->get_capacity(), rp->get_sign(),
                   rp->get_size());
    delete rp;
    return gcd_string(q, &r);
}

UnlimitedInt* UnlimitedRationalUtil::gcd(UnlimitedInt* p, UnlimitedInt* q) {
    return new UnlimitedInt(gcd_string(p, q));
}

std::string UnlimitedRationalUtil::get_abs_string(UnlimitedInt* ui1) {
    std::string res = ui1->to_string();
    if (res[0] == '-') {
        res.erase(0, 1);
    }
    return res;
}
