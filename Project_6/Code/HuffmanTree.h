#include <iostream>
#include <string>
#include <list>
#include <cstdlib>

using namespace std;

class Node
{
protected:
  int freq; // 儲存 terminal node 的字頻，或 internal node 所有子節點的字頻總和。
  string code;

public:
  Node(int i);
  virtual ~Node();

  int getFreq();
  void setcode(string s);
  string getcode();

  virtual int getNodeType() = 0; // 0: terminal node 1: internal node
  virtual char getValue() = 0;
  virtual Node *getLChild() = 0;
  virtual Node *getRChild() = 0;
};

class TerminalNode : public Node
{
private:
  char value; // 儲存這個 node 代表的字元

public:
  TerminalNode(int i, char c);
  virtual ~TerminalNode();

  char getValue();
  int getNodeType(); // 0: terminal node 1: internal node
  Node *getLChild(); // terminal node 沒有 LChild，因此請印出提示訊息，並且 return NULL。
  Node *getRChild(); // terminal node 沒有 RChild。
};

class InternalNode : public Node
{
private:
  Node *lChild; // left child
  Node *rChild; // right child

public:
  InternalNode(int, Node *left, Node *right);
  virtual ~InternalNode();

  char getValue();   // internal node 沒有 value，因此請印出提示訊息，並且 return 0。
  int getNodeType(); // 0: terminal node 1: internal node
  Node *getLChild();
  Node *getRChild();
};

class HuffmanTree
{
private:
  Node *root;
  string code[95];

public:
  HuffmanTree(const string &s);
  ~HuffmanTree();

  void del(Node *root);
  void init();
  void build(list<Node *> &leaf);
  void coding(Node *root, string s);

  string traverse(const char c, const int size);
  string encode(const string &s) const;
  string decode(const string &s) const;
  static bool compare(Node *one, Node *two);
};
