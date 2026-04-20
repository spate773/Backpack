#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std;

template <typename KeyT, typename ValT>
class BSTMap {
 private:
  struct BSTNode {
    const KeyT key;
    ValT value;
    BSTNode* parent;
    BSTNode* left;
    BSTNode* right;

    BSTNode(KeyT key, ValT value, BSTNode* parent)
        : key(key), value(value), parent(parent), left(nullptr), right(nullptr) {}
  };

  BSTNode* root;
  size_t sz;

  // Utility pointer for begin and next.
  BSTNode* curr;

  // TODO_STUDENT: add private helper function definitions here
  void clear_helper(BSTNode* node) {
    if (node == nullptr) return;
    clear_helper(node->left);
    clear_helper(node->right);
    delete node;
  }

  BSTNode* copy_helper(BSTNode* node, BSTNode* parent) {
    if (node == nullptr) return nullptr;
    BSTNode* new_node = new BSTNode(node->key, node->value, parent);
    new_node->left = copy_helper(node->left, new_node);
    new_node->right = copy_helper(node->right, new_node);
    return new_node;
  }

  void to_string_helper(BSTNode* node, ostringstream& ss) const {
    if (node == nullptr) return;
    to_string_helper(node->left, ss);
    ss << node->key << ": " << node->value << "\n";
    to_string_helper(node->right, ss);
  }

 public:
  /**
   * Creates an empty `BSTMap`. Runs in O(1).
   */
  BSTMap() {
    // TODO_STUDENT
    root = nullptr;
    sz = 0;
    curr = nullptr;
  }

  /**
   * Checks if the `BSTMap` is empty. Runs in O(1).
   */
  bool empty() const {
    // TODO_STUDENT
    return sz == 0;
  }

  /**
   * Returns the number of mappings in the `BSTMap`. Runs in O(1).
   */
  size_t size() const {
    // TODO_STUDENT
    return sz;
  }

  /**
   * Adds the mapping `{key -> value}` to the `BSTMap`. If the key already
   * exists, does not update the mapping (like the C++ STL map).
   *
   * Uses the key to determine the location in the underlying BST. Creates
   * exactly one new node.
   *
   * Runs in O(H), where H is the height of the tree.
   */
  void insert(KeyT key, ValT value) {
    // TODO_STUDENT
    if (root == nullptr) {
      root = new BSTNode(key, value, nullptr);
      sz++;
      return;
    }

    BSTNode* cur = root;
    BSTNode* parent = nullptr;

    while (cur != nullptr) {
      parent = cur;
      if (key == cur->key) return;  // no overwrite
      else if (key < cur->key)
        cur = cur->left;
      else
        cur = cur->right;
    }

    BSTNode* new_node = new BSTNode(key, value, parent);
    if (key < parent->key)
      parent->left = new_node;
    else
      parent->right = new_node;

    sz++;
  }

  /**
   * Return a reference to the value stored for `key` in the map.
   *
   * If key is not present in the map, throw `out_of_range` exception.
   *
   * Runs in O(H), where H is the height of the tree.
   */
  ValT& at(const KeyT& key) const {
    // TODO_STUDENT
    BSTNode* cur = root;
    while (cur != nullptr) {
      if (key == cur->key)
        return cur->value;
      else if (key < cur->key)
        cur = cur->left;
      else
        cur = cur->right;
    }
    throw out_of_range("Key not found in BSTMap");
  }

  /**
   * Returns `true` if the key is present in the map, and false otherwise.
   *
   * Runs in O(H), where H is the height of the tree.
   */
  bool contains(const KeyT& key) const {
    // TODO_STUDENT
    BSTNode* cur = root;
    while (cur != nullptr) {
      if (key == cur->key)
        return true;
      else if (key < cur->key)
        cur = cur->left;
      else
        cur = cur->right;
    }
    return false;
  }

  /**
   * Empties the `BSTMap`, freeing all memory it controls.
   *
   * Runs in O(N), where N is the number of mappings.
   */
  void clear() {
    // TODO_STUDENT
    clear_helper(root);
    root = nullptr;
    sz = 0;
  }

  /**
   * Destructor, cleans up the `BSTMap`.
   *
   * Runs in O(N), where N is the number of mappings.
   */
  ~BSTMap() {
    // TODO_STUDENT
    clear();
  }

  /**
   * Converts the `BSTMap` to a string representation, with the values
   * in-order by key.
   */
  string to_string() const {
    // TODO_STUDENT
    ostringstream ss;
    to_string_helper(root, ss);
    return ss.str();
  }

  /**
   * Copy constructor.
   */
  BSTMap(const BSTMap& other) {
    // TODO_STUDENT
    if (other.root == nullptr) {
      root = nullptr;
      sz = 0;
      curr = nullptr;
    } else {
      root = copy_helper(other.root, nullptr);
      sz = other.sz;
      curr = nullptr;
    }
  }

  /**
   * Assignment operator; `operator=`.
   */
  BSTMap& operator=(const BSTMap& other) {
    // TODO_STUDENT
    if (this == &other) return *this;  // protect self-assignment
    clear();
    if (other.root == nullptr) {
      root = nullptr;
      sz = 0;
    } else {
      root = copy_helper(other.root, nullptr);
      sz = other.sz;
    }
    curr = nullptr;
    return *this;
  }

  // =========================================================================

  pair<KeyT, ValT> remove_min() {
    // TODO_STUDENT
    throw runtime_error("remove_min not implemented yet");
  }

  bool operator==(const BSTMap& other) const {
    // TODO_STUDENT
    throw runtime_error("operator== not implemented yet");
  }

  void begin() {
    // TODO_STUDENT
    curr = nullptr;
  }

  bool next(KeyT& key, ValT& val) {
    // TODO_STUDENT
    return false;
  }

  ValT erase(const KeyT& key) {
    // TODO_STUDENT
    throw runtime_error("erase not implemented yet");
  }

  void* getRoot() const {
    return this->root;
  }
};