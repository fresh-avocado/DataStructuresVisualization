#include "BST.hpp"

class Node {
 private:
  Node* left;
  Node* right;

  friend class BST;

 public:
  int key;
  void killself() {
    if (left)
      left->killself();
    if (right)
      right->killself();
    delete this;
  }
  Node(int key, Node* left, Node* right) : key(key), left(left), right(right){};
  Node(int key) : key(key) { left = right = nullptr; }

  bool isLeaf() { return !left && !right; }
};