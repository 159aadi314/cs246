#include<bits/stdc++.h>
using namespace std;

#define SIZE 1000

class Node
{
private:
  friend class BPTree;
  vector<int> keys;
  Node* parent;
  vector<Node* > children;
  bool isDataNode = false;
  int num_keys = 0;

public:
  Node(bool data_or_index);
  ~Node();
};

class BPTree
{
private:
  int d;
  int t;
  Node* root;
public:
  // BPTree();
  int num_index_nodes = 0;
  int num_data_nodes = 0;
  BPTree(int d, int t);
  void insert_internal(Node* where_to_insert, Node* newchildptr, Node* oldchildptr, int value);
  void insert(int value);
  void display();
};


Node::Node(bool isDNode)
{
  parent = nullptr;
  isDataNode = isDNode;
  keys.clear();
  children.clear();
  keys.resize(SIZE, 1000000000);
  children.resize(SIZE, nullptr);
}

Node::~Node()
{
}

BPTree::BPTree(int dee, int tee) {
  d = dee;
  t = tee;
  root = new Node(false);
}

void BPTree::display() {
  cout << num_index_nodes << " " << num_data_nodes << " ";
  for(int i = 0; i < root->num_keys; i++) {
    cout << root->keys[i] << " ";
  }cout << endl;
}

void BPTree::insert_internal(Node* w, Node* p, Node* curr, int value) {
  if(w == nullptr) {
    Node* k = new Node(false);
    curr->isDataNode = true;
    p->isDataNode = true;
    curr->parent = k;
    p->parent = k;
    root = k;
    root->keys[0] = value;
    root->children[0] = curr;
    root->children[1] = p;
    root->num_keys++;
    num_index_nodes++;
    return;
  }
  w->num_keys++;
  w->keys[w->num_keys] = value;
  w->children[w->num_keys + 1] = p;
  for(int i = w->num_keys; i > 0; i--) {
    if(w->keys[i] < w->keys[i - 1]) {
      int tmp = w->keys[i];
      w->keys[i] = w->keys[i - 1];
      w->keys[i - 1] = tmp;
      Node* tmp1 = w->children[i + 1];
      w->children[i + 1] = w->children[i];
      w->children[i] = tmp1;
    } else {
      break;
    }
  }
  if(w->num_keys < 2*t + 2) {
    return;
  } else {
    Node* p1 = new Node(false);
    num_index_nodes++;
    p1->parent = w->parent;
    int push_up = w->keys[t];
    w->keys[t] = 1000000000;
    for(int i = t + 1; i < 2*t + 2; i++) {
      int a = w->keys[i];
      w->keys[i] = 1000000000;
      Node* b = w->children[i];
      w->children[i] = nullptr;
      p1->keys[i - t - 1] = a;
      p1->children[i - t - 1] = b;
    }
    p1->children[t + 1] = w->children[2*t + 2];
    w->children[2*t + 2] = nullptr;
    w->num_keys  = t;
    p1->num_keys = t + 1;
    insert_internal(w->parent, p1, w, push_up);
  }
}

void BPTree::insert(int value) {
  if(root->num_keys == 0) {
    root->keys[0] = value;
    root->isDataNode = true;
    num_data_nodes++;
    root->num_keys++;
    return;
  } else {
    Node* curr = root;
    while(true) {
      if(curr->isDataNode == true) {
        curr->num_keys++;
        curr->keys[curr->num_keys] = value;
        for(int i = curr->num_keys; i > 0; i--) {
          if(curr->keys[i] < curr->keys[i - 1]) {
            int tmp = curr->keys[i];
            curr->keys[i] = curr->keys[i - 1];
            curr->keys[i - 1] = tmp;
          } else {
            break;
          }
        }
        if(curr->num_keys < 2*d + 1) {
          break;
        } else {
          Node* p = new Node(true);
          num_data_nodes++;
          p->parent = curr->parent;
          for(int i = d; i < 2*d + 1; i++) {
            int a = curr->keys[i];
            curr->keys[i] = 1000000000;
            p->keys[i-d] = a;
          }
          p->num_keys = d + 1;
          curr->num_keys = d;
          int push_up = p->keys[0];
          insert_internal(curr->parent, p, curr, push_up);
          break;
        }
      } else {
        if(value <= curr->keys[0]) {
          curr = curr->children[0];
        } else if(value > curr->keys[curr->num_keys - 1]) {
          curr = curr->children[curr->num_keys];
        }
        else {
          for(int i = 1; i < curr->num_keys; i++) {
            if(value > curr->keys[i - 1] && value <= curr->keys[i]) {
              curr = curr->children[i]; break;
            }
          }
        }
      }
    }
  }
}

int main() {
  int d, t;
  cin >> d >> t;
  BPTree* T = new BPTree(d, t);
  
  while(true) {
    int a;
    cin >> a;
    int b;
    switch (a)
    {
    case 1:
      cin >> b;
      T->insert(b);
      break;
    case 2:
      T->display();
      break;
    case 3:
      return 0;
    default:
      break;
    }
  }
}