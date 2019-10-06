#include "HuffmanTree.h"

using namespace std;

Node::Node(int i = 0)
{
    freq = i;
    code = "\0";
}

Node::~Node()
{
}

int Node::getFreq()
{
    return freq;
}

void Node::setcode(string s)
{
    code = s;
}

string Node::getcode()
{
    return code;
}

///////////////////////////////////////////////

TerminalNode::TerminalNode(int i, char c) : Node(i)
{
    value = c;
}

TerminalNode::~TerminalNode()
{
}

char TerminalNode::getValue()
{
    return value;
}

int TerminalNode::getNodeType()
{
    if (getValue() != 0)
        return 0;
    else
        return 1;
}

Node *TerminalNode::getLChild()
{
    if (getNodeType() == 0)
    {
        //cout << "This is a terminal node and there is no LChild" << endl;
        return NULL;
    }
}

Node *TerminalNode::getRChild()
{
    if (getNodeType() == 0)
    {
        //cout << "This is a terminal node and there is no RChild" << endl;
        return NULL;
    }
}

//////////////////////////////////////////////

InternalNode::InternalNode(int i, Node *left = NULL, Node *right = NULL) : Node(i)
{
    lChild = left;
    rChild = right;
}

InternalNode::~InternalNode()
{
    lChild = NULL;
    rChild = NULL;
}

char InternalNode::getValue()
{
    if (lChild != NULL && rChild != NULL)
    {
        //cout << "This is an internal node, no value" << endl;
        return 0;
    }
    else
        return 1;
}

int InternalNode::getNodeType()
{
    if (getValue() == 0)
        return 1;
    else
        return 0;
}

Node *InternalNode::getLChild()
{
    if (getNodeType() == 1)
        return lChild;
    else
        return NULL;
}

Node *InternalNode::getRChild()
{
    if (getNodeType() == 1)
        return rChild;
    else
        return NULL;
}

//////////////////////////////////////////////

void HuffmanTree::init()
{
    for (int i = 0; i < 95; i++)
        code[i] = "\0";
}

bool HuffmanTree::compare(Node *one, Node *two)
{
    if (one->getFreq() < two->getFreq())
        return true;
    else
        return false;
}

void HuffmanTree::coding(Node *root, string s)
{
    if (root->getLChild() != NULL)
    {
        string ns;
        ns = s + "0";
        coding(root->getLChild(), ns);
    }
    if (root->getRChild() != NULL)
    {
        string ns;
        ns = s + "1";
        coding(root->getRChild(), ns);
    }
    if ((root->getLChild() == NULL) && (root->getRChild() == NULL))
    {
        root->setcode(s);
        code[root->getValue() - 32] = s;
    }
}

void HuffmanTree::build(list<Node *> &leaf)
{
    if (leaf.size() == 0)
        return;
    else if (leaf.size() == 1)
        root = leaf.front();
    else
    {
        Node *right = leaf.front();
        leaf.pop_front();
        Node *left = leaf.front();
        leaf.pop_front();

        Node *newnode = new InternalNode((int)left->getFreq() + (int)right->getFreq(), left, right);

        leaf.push_back(newnode);
        leaf.sort(compare);
        build(leaf);
    }
}

HuffmanTree::HuffmanTree(const string &s)
{
    int i = 0;
    int len = s.size();
    int ch[95] = {0};
    Node *leaf;
    list<Node *> nodelist;

    init();

    for (i = 0; i < len; i++)
        if (s[i] >= 32 && s[i] <= 126)
            ch[s[i] - 32]++;

    for (i = 0; i < 95; i++)
        if (ch[i] > 0)
        {
            leaf = new TerminalNode(ch[i], i + 32);
            nodelist.push_back(leaf);
        }

    nodelist.sort(compare);
    build(nodelist);
    coding(root, "");
}

void HuffmanTree::del(Node *treeroot)
{
    if (treeroot->getLChild() != NULL)
        del(treeroot->getLChild());

    if (treeroot->getRChild() != NULL)
        del(treeroot->getRChild());

    if (treeroot->getRChild() == NULL && treeroot->getLChild() == NULL)
        delete treeroot;
    else if (treeroot->getNodeType() == 1)
        delete treeroot;
}

HuffmanTree::~HuffmanTree()
{
    del(root);
}

string HuffmanTree::encode(const string &s) const
{
    int len = s.size();
    int i;
    string output = "\0";
    string temp;

    for (i = 0; i < len; i++)
    {
        temp = code[s[i] - 32];
        if (temp != "\0")
            output += temp;
        else
        {
            cout << "This string can not be encoded" ;
            return "";
        }
    }

    return output;
}

string HuffmanTree::decode(const string &s) const
{
    string output = "\0";
    int len = s.size();
    int i = 0;
    Node *temp = root;

    for (i = 0; i < len; i++)
    {
        if (temp == NULL)
        {
            cout << "This code can not be decoded" ;
            return "";
        }

        if (temp->getNodeType() == 0)
        {
            output += temp->getValue();
            temp = root;
        }

        if (s[i] == '0')
            temp = temp->getLChild();

        else
            temp = temp->getRChild();
    }

    if (temp->getNodeType() == 0)
    {
        output += temp->getValue();
        return output;
    }
    else
    {
        cout << "This code can not be decoded" ;
        return "";
    }
}
