#include <iostream>
#include <string>
#include <list>
#include <cstdlib>

using namespace std;

class Node
{
protected:
  int freq; // �x�s terminal node ���r�W�A�� internal node �Ҧ��l�`�I���r�W�`�M�C
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
  char value; // �x�s�o�� node �N���r��

public:
  TerminalNode(int i, char c);
  virtual ~TerminalNode();

  char getValue();
  int getNodeType(); // 0: terminal node 1: internal node
  Node *getLChild(); // terminal node �S�� LChild�A�]���ЦL�X���ܰT���A�åB return NULL�C
  Node *getRChild(); // terminal node �S�� RChild�C
};

class InternalNode : public Node
{
private:
  Node *lChild; // left child
  Node *rChild; // right child

public:
  InternalNode(int, Node *left, Node *right);
  virtual ~InternalNode();

  char getValue();   // internal node �S�� value�A�]���ЦL�X���ܰT���A�åB return 0�C
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
