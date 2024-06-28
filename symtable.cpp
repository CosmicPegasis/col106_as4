/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

struct SymbolTableUtil {
    static SymEntry* search(SymEntry* root, string k);
  static SymEntry* del(SymEntry* root, SymEntry* parent, SymEntry* to_delete);
    static void insert(SymEntry* root, string k, UnlimitedRational* v);
    static void deleteNodeWithBothChildren(SymEntry* cur, SymEntry* parent);
  static SymEntry* deleteNodeWithLeftChild(SymEntry* cur, SymEntry* parent, SymEntry* root);
  static SymEntry* deleteNodeWithRightChild(SymEntry* cur, SymEntry* parent, SymEntry* root);
  static void deleteLeafNode(SymEntry* cur, SymEntry* parent);
    static bool isRightChild(SymEntry* cur, SymEntry* parent);
    static void fixParent(SymEntry* cur, SymEntry* parent, SymEntry* replacer);
    static void findSuccessor(SymEntry* cur, SymEntry* parent,
                              SymEntry** successor,
                              SymEntry** successor_parent, SymEntry** successor_right_child);
    static void inOrderTraversal(SymEntry* cur);
  static SymEntry* search_with_parent(SymEntry* cur,SymEntry* parent, SymEntry** to_assign_parent, string k);
};

SymbolTable::SymbolTable() {
    size = 0;
    root = nullptr;
};
SymbolTable::~SymbolTable() { delete root; };

int SymbolTable::get_size() { return this->size; }

void SymbolTable::insert(string k, UnlimitedRational* v) {
    if (size == 0) {
        root = new SymEntry(k, v);
    } else {
        SymbolTableUtil::insert(root, k, v);
    }
    size++;
}

UnlimitedRational* SymbolTable::search(string k) {
    SymEntry* node = SymbolTableUtil::search(root, k);
    if(node){
      return node->val;
    }
    else{
      return nullptr;
    }
};

void SymbolTable::remove(string k) {
  SymEntry* parent = nullptr;
  SymEntry* to_delete = SymbolTableUtil::search_with_parent(this->root,nullptr, &parent,  k);
  if(to_delete == root && !(root->left) && !(root->right)){
    delete this->root;
    root = nullptr;
  }
    this->root = SymbolTableUtil::del(root, parent, to_delete);
    size--;
}

SymEntry* SymbolTable::get_root() { return this->root; };

// -------------------------------- utility -----------------------------

SymEntry* SymbolTableUtil::search(SymEntry* root, string k) {
    if (!root) {
        return nullptr;
    }
    if (root->key < k) {
        if (root->right) {
            return search(root->right, k);
        } else {
            return nullptr;
        }
    } else if (root->key > k) {
        if (root->left) {
            return search(root->left, k);
        } else {
            return nullptr;
        }
    } else {
        return root;
    }
};
SymEntry* SymbolTableUtil::search_with_parent(SymEntry* cur,SymEntry* parent, SymEntry** to_assign_parent, string k){
    if (!cur) {
        return nullptr;
    }
    if (cur->key < k) {
        if (cur->right) {
	  *to_assign_parent = cur;
	  return search_with_parent(cur->right, cur, to_assign_parent,k);
        } else {
            return nullptr;
        }
    } else if (cur->key > k) {
	*to_assign_parent = cur;
        if (cur->left) {
            return search_with_parent(cur->left, cur, to_assign_parent,k);
        } else {
            return nullptr;
        }
    } else {
        return cur;
    }
}
SymEntry* SymbolTableUtil::del(SymEntry* root, SymEntry* parent,
                          SymEntry* to_delete) {
    if (!to_delete) {
        return nullptr;
    }
    if (to_delete->left && to_delete->right) {
       SymbolTableUtil::deleteNodeWithBothChildren(to_delete, parent);
    } else if (to_delete->left) {
      root =  SymbolTableUtil::deleteNodeWithLeftChild(to_delete, parent,root);
    } else if (to_delete->right) {
      root =  SymbolTableUtil::deleteNodeWithRightChild(to_delete, parent,root);
    } else {
        SymbolTableUtil::deleteLeafNode(to_delete, parent);
    }
    return root;
};
void SymbolTableUtil::insert(SymEntry* root, string k, UnlimitedRational* v) {
    if (!root) {
        return;
    }
    if (root->key < k) {
        if (root->right) {
            insert(root->right, k, v);
        } else {
            root->right = new SymEntry(k, v);
        }
    } else {
        if (root->left) {
            insert(root->left, k, v);
        } else {
            root->left = new SymEntry(k, v);
        }
    }
};
void SymbolTableUtil::deleteLeafNode(SymEntry* cur, SymEntry* parent) {
    fixParent(cur, parent, nullptr);
    delete cur;
}
SymEntry* SymbolTableUtil::deleteNodeWithLeftChild(SymEntry* cur, SymEntry* parent, SymEntry* root) {
  if(!parent){
    root = cur->left;
  }
    fixParent(cur, parent, cur->left);
    cur->left = nullptr;
    delete cur;
    return root;
}
SymEntry* SymbolTableUtil::deleteNodeWithRightChild(SymEntry* cur,
						    SymEntry* parent, SymEntry* root) {
  if(!parent){
    root = cur->right;
  }
    fixParent(cur, parent, cur->right);
    cur->right = nullptr;
    delete cur;
    return root;
}
void SymbolTableUtil::deleteNodeWithBothChildren(SymEntry* cur,
                                                 SymEntry* parent) {
  SymEntry *successor, *successor_parent, *successor_right_child;
  SymbolTableUtil::findSuccessor(cur->right, cur, &successor, &successor_parent, &successor_right_child);
  cur->key  = successor->key;
  UnlimitedInt p(successor->val->get_p_str());
  UnlimitedInt q(successor->val->get_q_str());
  delete cur->val;
  cur->val = new UnlimitedRational(&p, &q);
  if(successor_right_child){
    SymEntry* temp = nullptr;
    deleteNodeWithRightChild(successor, successor_parent,temp);
  }
  else{
    deleteLeafNode(successor, successor_parent);
  }
}
void SymbolTableUtil::fixParent(SymEntry* cur, SymEntry* parent,
                                SymEntry* replacer) {
    if (parent) {
        if (SymbolTableUtil::isRightChild(cur, parent)) {
            parent->right = replacer;
        } else {
            parent->left = replacer;
        }
    }
}
void SymbolTableUtil::findSuccessor(SymEntry* cur, SymEntry* parent,
                                    SymEntry** successor,
				    SymEntry** successor_parent, SymEntry** successor_right_child) {
  if(!cur){
    return;
  }
  else{
    if(cur->left){
      findSuccessor(cur->left, cur, successor, successor_parent, successor_right_child);
    }
    else if(cur->right){
      *successor = cur;
      *successor_parent = parent;
      *successor_right_child = cur->right;
    }
    else{
      *successor = cur;
      *successor_parent = parent;
      *successor_right_child = nullptr;
    }
  }
}

bool SymbolTableUtil::isRightChild(SymEntry* cur, SymEntry* parent) {
    if (parent->right == cur) {
        return true;
    } else {
        return false;
    }
};

