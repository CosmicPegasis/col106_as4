/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"

SymEntry::SymEntry(){
  val = nullptr;
  left = nullptr;
  right = nullptr;
};
SymEntry::SymEntry(string k, UnlimitedRational* v) {
    this->key = k;
    UnlimitedInt* p = v->get_p();
    UnlimitedInt* q = v->get_q();
    val = new UnlimitedRational(p, q);
    left = nullptr;
    right = nullptr;
};
SymEntry::~SymEntry(){
  delete val;
  delete left;
  delete right;
};
