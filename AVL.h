#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>
using namespace std;

// Here are just function declarations. Comments + implementations on cpp.
struct AVLNode
{
    string name;
    string ufid;
    AVLNode *left;
    AVLNode *right;
    int height;
    int balanceFactor;

    AVLNode(string name, string ufid)
    {
        this->name = name;
        this->ufid = ufid;
        left = nullptr;
        right = nullptr;
        height = 0;
        balanceFactor = 0;
    }
};

class AVLTree
{
private:
    AVLNode *root = nullptr;
    AVLNode *inserthelper(AVLNode *node, string name, string ufid, bool &inserted);
    AVLNode *removehelper(AVLNode *node, string ufid, bool &removed);
    string searchidhelper(AVLNode *node, string ufid) const;
    void searchnamehelper(AVLNode *node, string name, vector<string> &ids) const;
    void inorderhelper(AVLNode *node, vector<AVLNode *> &inordervec) const;
    void preorderhelper(AVLNode *node, vector<AVLNode *> &preordervec) const;
    void postorderhelper(AVLNode *node, vector<AVLNode *> &postordervec) const;
    AVLNode *minValueNode(AVLNode *node);
    AVLNode *Balance(AVLNode *node);
    int balanceFactor(AVLNode *node);
    int height(AVLNode *node);
    AVLNode *rotateRight(AVLNode *node);
    AVLNode *rotateLeft(AVLNode *node);

public:
    void insert(const string &name, const string &ufid);
    void remove(const string &ufid);
    void search_id(const string &id) const;
    void search_name(const string &name) const;
    void printinorder() const;
    void printpreorder() const;
    void printpostorder() const;
    void printLevelCount();
    void removeInorder(int n);
    ~AVLTree();
};
