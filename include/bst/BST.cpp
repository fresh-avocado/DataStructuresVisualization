#include "BST.hpp"

#include <chrono>
#include <cmath>
#include <queue>
#include <stack>
#include <thread>

void BST::insert(int value) {
  Node** current = findPointer(value);
  if ((*current)) {
    // TODO replace data
  } else {
    (*current) = new Node(value);
    nodes++;
    print();
    auto [x, y, z, color] = vertices[(*current)->key];
    vertices[(*current)->key] = {x, y, z, red};
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    vertices[(*current)->key] = {x, y, z, white};
  }
}

void BST::remove(int value) {
  Node** current = findPointer(value);
  if ((*current)) {
    removeNode(current);
    nodes--;
  }
}

void BST::removeNode(Node**& current) {
  Node* toDelete = (*current);
  bool left = toDelete->left, right = toDelete->right;
  if (!left || !right) {
    if (!left && !right)
      (*current) = nullptr;
    else if (left && !right)
      (*current) = toDelete->left;
    else if (!left && right)
      (*current) = toDelete->right;
    delete toDelete;
  } else {
    while ((*current)->right)
      current = &(*current)->left;
    swap((*current)->key, toDelete->key);
    removeNode(current);
  }
}

Node** BST::findPointer(int value) {
  Node** current = &(root);
  int h_max_curr = 0;
  while ((*current) != nullptr) {
    auto [x, y, z, color] = vertices[(*current)->key];
    vertices[(*current)->key] = {x, y, z, red};
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    vertices[(*current)->key] = {x, y, z, white};
    h_max_curr++;
    if (value == (*current)->key)
      break;
    else if (value < (*current)->key)
      current = &(*current)->left;
    else
      current = &(*current)->right;
  }
  if (h_max_curr > h_max) {
    h_max = h_max_curr;
  }
  return current;
}

void BST::displayInOrder() {
  displayInOrderRecursive(root);
}

void BST::displayInOrderRecursive(Node* current) {
  if (!current)
    return;
  displayInOrderRecursive(current->left);
  cout << current->key << " ";
  displayInOrderRecursive(current->right);
}

void BST::displayPreOrder() {
  displayPreOrderRecursive(root);
}

void BST::displayPreOrderRecursive(Node* current) {
  if (!current)
    return;
  cout << current->key << " ";
  displayPreOrderRecursive(current->left);
  displayPreOrderRecursive(current->right);
}

void BST::displayPostOrder() {
  displayPostOrderRecursive(root);
}

void BST::displayPostOrderRecursive(Node* current) {
  if (!current)
    return;
  displayPostOrderRecursive(current->left);
  displayPostOrderRecursive(current->right);
  cout << current->key << " ";
}

// ver prints

int BST::minValue() {
  Node* current = root;
  if (!current)
    throw logic_error("si");
  while (current->left)
    current = current->left;
  return current->key;
}

int BST::maxValue() {
  Node* current = root;
  if (!current)
    throw logic_error("si");
  while (current->right)
    current = current->right;
  return current->key;
}

Node* BST::find(int value) {
  Node* current = root;
  while (current != nullptr) {
    int key = current->key;
    if (value == key)
      return current;
    else if (value < key)
      current = current->left;
    else if (value > key)
      current = current->right;
  }
  throw logic_error("not found");
}

bool BST::isFull() {
  return isFullRecursive(root);
}

bool BST::isFullRecursive(Node* current) {
  if (!current)
    return true;
  Node *left = current->left, *right = current->right;
  if ((left && !right) || (!left && right))
    return false;
  return isFullRecursive(left) && isFullRecursive(right);
}

void BST::clear() {
  if (root)
    root->killself();
  root = nullptr;
  nodes = 0;
  h_max = 0;
  aristas.clear();
  vertices.clear();
}

void BST::buildFromOrderedArray(int* array, int n) {
  if (n == 0)
    return;
  int mid = n / 2;
  insert(array[mid]);
  if (n == 1)
    return;
  buildFromOrderedArray(array, mid);
  buildFromOrderedArray(array + mid + 1, n - mid - 1);

  // 1 2 3 4   5 6 7 8

  // start = x ; end = n / 2
  // start = n/2 + 1 ; end = n

  // 1 2 3 4 5 6 7 8 9
}

int BST::size() {
  return nodes;
}

BST::~BST() {
  clear();
}

bool BST::isBalanced() {
  return isBalancedRecursive(root).second;
}

// cambiar a booleano por parámetro
pair<int, bool> BST::isBalancedRecursive(Node* current) {
  if (!current)
    return {-1, true};
  pair<int, bool> left = isBalancedRecursive(current->left);
  pair<int, bool> right = isBalancedRecursive(current->right);
  if (!left.second || !right.second || abs(left.first - right.first) > 1)
    return {0, false};
  return {max(left.first, right.first) + 1, true};
}

int BST::height() {
  return heightRecursive(root);
}

int BST::heightRecursive(Node* current) {
  if (!current)
    return -1;
  int left = heightRecursive(current->left);
  int right = heightRecursive(current->right);
  return max(left, right) + 1;
}

string BST::displayBFS() {
  string bfs = "";
  if (!root)
    return bfs;
  queue<Node*> q;
  Node* current;
  q.push(root);
  while (!q.empty()) {
    current = q.front();
    if (current->left)
      q.push(current->left);
    if (current->right)
      q.push(current->right);
    bfs = bfs + " " + to_string(current->key);
    q.pop();
  }
  return bfs;
}

string BST::displayDFS() {
  string dfs = "";
  if (!root)
    return dfs;
  stack<Node*> s;
  Node* current = root;
  // pop push top
  while (!s.empty()) {
    dfs = dfs + " " + to_string(current->key);
    if (current->left) {
      current = current->left;
    } else {
    }

    s.push(root);
    if (current->left) {
    }
    s.push(root);
    current = s.top();
  }
  return dfs;
}

void BST::print() {
  aristas.clear();
  printRecursive(root, 0, (pow(2, h_max) - 1), 0, {0, 0, 0});
}

void BST::printRecursive(Node* cur,
                         float pos,
                         float factor,
                         int curr_h,
                         tuple<float, float, float> parent) {
  if (cur == nullptr)
    return;
  pos = pos + round(factor) / 2;
  if (curr_h > 0) {
    aristas.push_back({parent, {pos, curr_h * -2, 5}});
  }
  vertices[cur->key] = {pos, curr_h * -2, 5, white};
  printRecursive(cur->left, pos, -1 * abs(factor) / 2, curr_h + 1,
                 {pos, curr_h * -2, 5});
  printRecursive(cur->right, pos, abs(factor) / 2, curr_h + 1,
                 {pos, curr_h * -2, 5});
}