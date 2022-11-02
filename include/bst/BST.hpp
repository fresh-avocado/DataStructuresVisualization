#ifndef BST_H
#define BST_H

#include <unistd.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "Node.hpp"
//#include "BST.hpp"
using namespace std;

class Node;
enum color { red, white };

class BST {
 private:
  Node* root;
  int nodes, h_max;
  Node** findPointer(int value);
  void displayInOrderRecursive(Node* current);
  void displayPreOrderRecursive(Node* current);
  void displayPostOrderRecursive(Node* current);
  bool isFullRecursive(Node* current);
  void removeNode(Node**& current);
  int heightRecursive(Node* current);
  pair<int, bool> isBalancedRecursive(Node* current);

 public:
  unordered_map<int, tuple<float, float, float, color>> vertices;
  vector<pair<tuple<float, float, float>, tuple<float, float, float>>> aristas;
  void print();
  void printRecursive(Node* cur,
                      float pos,
                      float factor,
                      int curr_h,
                      tuple<float, float, float> parent);
  BST() : root(nullptr), nodes(0), h_max(0) {}
  ~BST();

  void insert(int value);
  void remove(int value);
  Node* find(int value);
  void buildFromOrderedArray(int* array, int n);

  void displayInOrder();
  void displayPreOrder();   // revisar
  void displayPostOrder();  // revisar

  int minValue();
  int maxValue();

  int size();
  int height();
  void clear();

  bool isBalanced();
  bool isFull();

  string displayBFS();
  string displayDFS();  // falta

  /*
      int successor(int value); // Retornar el valor siguiente de "value" en el
     arbol int predecessor(int value); // Retornar el valor anterior de "value"
     en el arbol
  */
};

#endif