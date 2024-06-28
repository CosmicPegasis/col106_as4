#include "string"
#include "ulimitedrational.h"
using namespace std;

class SymEntry {
public:
    string key;
    UnlimitedRational* val;
    
    SymEntry* left;
    SymEntry* right;

  SymEntry(); // Done
  SymEntry(string k, UnlimitedRational* v); // Done;

  ~SymEntry(); // Done;
    
};
