#include "AVL.h"

// Implement the functions declared in AVL.h
// user cant access memory in main.cpp, that's why we need helpers.

// CODE:
// calls inserthelper on root and cout "successful" or "unsuccessful".
void AVLTree::insert(const string &name, const string &ufid)
{
    // insertion
    // prints "successful" if it was inserted, else it prints "unsuccessful"
    bool inserted = false;
    root = inserthelper(root, name, ufid, inserted);
    cout << (inserted ? "successful" : "unsuccessful") << endl;
}

// calls removehelper on root and cout "successful" or "unsuccessful".
void AVLTree::remove(const string &ufid)
{
    // removal
    bool removed = false;
    root = removehelper(root, ufid, removed);
    cout << (removed ? "successful" : "unsuccessful") << endl;
}

// search by ufid.
void AVLTree::search_id(const string &id) const
{
    string result = searchidhelper(root, id);
    cout << result << endl;
}

// search by name.
void AVLTree::search_name(const string &name) const
{
    // search by name, since tree is organized by ufids and not names, we have to traverse all nodes to check if it has that name.
    vector<string> ids;
    searchnamehelper(root, name, ids);
    if (ids.empty())
    {
        cout << "unsuccessful" << endl;
    }
    else
    {
        for (const auto &id : ids)
        {
            cout << id << endl;
        }
    }
}

// print inorder, preorder, postorder traversals (comma separated of the names in the tree)
// O(n)
void AVLTree::printinorder() const
{
    // inorder traversal
    vector<AVLNode *> inordervec;
    inorderhelper(root, inordervec);
    // prints names of each object on the vector:
    for (int i = 0; i < inordervec.size(); i++)
    {
        cout << inordervec[i]->name;
        if (i != inordervec.size() - 1)
        {
            cout << ", ";
        }
        if (i == inordervec.size() - 1)
        {
            cout << endl;
        }
    }
    return;
}

void AVLTree::printpreorder() const
{
    // preorder traversal
    vector<AVLNode *> preordervec;
    preorderhelper(root, preordervec);
    // prints names of each object on the vector:
    for (int i = 0; i < preordervec.size(); i++)
    {
        cout << preordervec[i]->name;
        if (i != preordervec.size() - 1)
        {
            cout << ", ";
        }
        if (i == preordervec.size() - 1)
        {
            cout << endl;
        }
    }
    return;
}

void AVLTree::printpostorder() const
{
    // postorder traversal
    vector<AVLNode *> postordervec;
    postorderhelper(root, postordervec);
    // prints names of each object on the vector:
    for (int i = 0; i < postordervec.size(); i++)
    {
        cout << postordervec[i]->name;
        if (i != postordervec.size() - 1)
        {
            cout << ", ";
        }
        if (i == postordervec.size() - 1)
        {
            cout << endl;
        }
    }
    return;
}

// prints levelCount
// level = nodes on the longest path so add 1.
// prints the number of levels that exist in the tree.
void AVLTree::printLevelCount()
{
    if (root == nullptr)
    {
        cout << 0 << endl;
        return;
    }
    else
    {
        int levels = root->height + 1;
        cout << levels << endl;
    }
    return;
}

// finds minValueNode = inorder succesor.
AVLNode *AVLTree::minValueNode(AVLNode *node)
{
    AVLNode *current = node;
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

// balances tree by doing necessary rotations
AVLNode *AVLTree::Balance(AVLNode *node)
{
    // if node is unbalanced then perform rotations
    int balance = balanceFactor(node);
    // LL
    if (balance > 1)
    {
        // LR -> if parent > 1, and child < 0
        if (balanceFactor(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    // RR
    if (balance < -1)
    {
        // RL -> if parent < -1 and child > 0
        if (balanceFactor(node->right) > 0)
        {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    return node;
}

// Time = O (log n).
AVLNode *AVLTree::inserthelper(AVLNode *node, string name, string ufid, bool &inserted)
{
    // insertion helper
    // if nullptr just insert.
    if (node == nullptr)
    {
        inserted = true;
        return new AVLNode(name, ufid);
    }
    // if less than go left
    if (ufid < node->ufid)
    {
        node->left = inserthelper(node->left, name, ufid, inserted);
    }
    // if greater than go right
    else if (ufid > node->ufid)
    {
        node->right = inserthelper(node->right, name, ufid, inserted);
    }
    // duplicate ufid, don't insert just return the node
    else
    {
        inserted = false;
        return node;
    }

    // only update height and balance if something changed
    if (inserted)
    {
        node->height = 1 + max(height(node->left), height(node->right));

        // balance the node if it has become unbalanced
        node = Balance(node);
    }

    return node;
}

// Time = O (log n).
AVLNode *AVLTree::removehelper(AVLNode *node, string ufid, bool &removed)
{
    // no need to balance after deletion (optional)
    // check if it exists
    // return correct node or nullptr (no children) to help reconnect all the nodes.

    // checks if it is empty or not
    if (node == nullptr)
    {
        return nullptr;
    }

    // if found
    else if (ufid == node->ufid)
    {
        removed = true;
        // no child:
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            return nullptr;
        }
        // one child
        else if (node->left == nullptr || node->right == nullptr)
        {
            AVLNode *child = node->left ? node->left : node->right;
            delete node;
            return child;
        }
        // 2 children inorder successor - right subtree's leftmost child (minvaluenode).
        else
        {
            // right subtree's leftmost value.
            AVLNode *temp = minValueNode(node->right);
            node->ufid = temp->ufid;
            node->name = temp->name;
            node->right = removehelper(node->right, temp->ufid, removed);
            return node;
        }
    }
    // if less than go left
    else if (ufid < node->ufid)
    {
        node->left = removehelper(node->left, ufid, removed);
    }
    // if greater go right
    else if (ufid > node->ufid)
    {
        node->right = removehelper(node->right, ufid, removed);
    }
    // if ufid does not exist
    else
    {
        return node;
    }
    // only update height if something changed
    if (removed && node != nullptr)
    {
        node->height = 1 + max(height(node->left), height(node->right));
    }

    return node;
}

// Time: O (log n).
// input is ufid, has to return name.
string AVLTree::searchidhelper(AVLNode *node, string ufid) const
{
    if (node == nullptr)
    {
        return "unsuccessful";
    }
    if (ufid == node->ufid)
    {
        return node->name;
    }
    if (ufid < node->ufid)
    {
        return searchidhelper(node->left, ufid);
    }
    else
    {
        return searchidhelper(node->right, ufid);
    }
}

// O(n) because since the tree is ordered by ufid, we have to potentially search every node.
// input is name, have to find ALL ufid under that name, that is can have duplicates.
void AVLTree::searchnamehelper(AVLNode *node, string name, vector<string> &ids) const
{
    if (node == nullptr)
    {
        return;
    }
    searchnamehelper(node->left, name, ids);
    if (node->name == name)
    {
        ids.push_back(node->ufid);
    }
    searchnamehelper(node->right, name, ids);
    return;
}

// O(n)
void AVLTree::inorderhelper(AVLNode *node, vector<AVLNode *> &inordervec) const
{
    // inorder traversal
    // if node is nullptr just returns.
    if (node == nullptr)
    {
        return;
    }

    // Left - Root - Right
    else
    {
        inorderhelper(node->left, inordervec);
        inordervec.push_back(node);
        inorderhelper(node->right, inordervec);
    }
    return;
}

// O(n)
void AVLTree::preorderhelper(AVLNode *node, vector<AVLNode *> &preordervec) const
{
    // preorder traversal
    if (node == nullptr)
    {
        return;
    }
    // Root - Left - Right
    else
    {
        preordervec.push_back(node);
        preorderhelper(node->left, preordervec);
        preorderhelper(node->right, preordervec);
    }
    return;
}

// O(n)
void AVLTree::postorderhelper(AVLNode *node, vector<AVLNode *> &postordervec) const
{
    // postorder traversal
    if (node == nullptr)
    {
        return;
    }
    // Left - Right - Root
    else
    {
        postorderhelper(node->left, postordervec);
        postorderhelper(node->right, postordervec);
        postordervec.push_back(node);
        return;
    }
}

int AVLTree::height(AVLNode *node)
{
    // if node == nullptr then height is -1
    if (node == nullptr)
    {
        return -1;
    }
    // else return node's stored height.
    return node->height;
}

// O (1);
int AVLTree::balanceFactor(AVLNode *node)
{
    // if node is nullptr it has no children.
    if (node == nullptr)
    {
        return 0;
    }
    // else height of left subetree - height of right subtree
    return height(node->left) - height(node->right);
}

// Remove the Nth gatorID from the inorder traversal in the tree.
void AVLTree::removeInorder(int n)
{
    // get vectors with pointers to the nodes in the tree inorder.
    vector<AVLNode *> inordervec;
    inorderhelper(root, inordervec);
    // if invalid return false -> cout "unsuccesful"
    if (n < 0 || n >= inordervec.size())
    {
        cout << "unsuccessful" << endl;
        return;
    }
    bool removed = false;
    string ufid = inordervec[n]->ufid;
    root = removehelper(root, ufid, removed);
    cout << (removed ? "successful" : "unsuccessful") << endl;
    return;
}

// Rotate functions source = Aman's slides.
// TIME AND SPACE = O(1).
AVLNode *AVLTree::rotateRight(AVLNode *node)
{
    AVLNode *grandchild = node->left->right;
    AVLNode *newparent = node->left;
    newparent->right = node;
    node->left = grandchild;

    // Update heights.
    node->height = 1 + max(height(node->left), height(node->right));
    newparent->height = 1 + max(height(newparent->left), height(newparent->right));

    return newparent;
}

// TIME AND SPACE = O(1).
AVLNode *AVLTree::rotateLeft(AVLNode *node)
{
    AVLNode *grandchild = node->right->left;
    AVLNode *newparent = node->right;
    newparent->left = node;
    node->right = grandchild;

    // Update heights.
    node->height = 1 + max(height(node->left), height(node->right));
    newparent->height = 1 + max(height(newparent->left), height(newparent->right));

    return newparent;
}

// postorder traversal for destructor because it only visits each node once.
AVLTree::~AVLTree()
{
    vector<AVLNode *> po;
    postorderhelper(root, po);
    for (int i = 0; i < po.size(); i++)
    {
        delete po[i];
    }
}