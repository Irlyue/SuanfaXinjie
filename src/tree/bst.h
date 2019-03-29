//
// Created by wenfeng on 19-3-29.
//

#ifndef SUANFAXINJIE_TREE_BST_H
#define SUANFAXINJIE_TREE_BST_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
class BSTNode {
public:
    T mKey;
    BSTNode *mLeft, *mRight;
    BSTNode *mParent;

    explicit BSTNode(T key, BSTNode *left=nullptr, BSTNode *right=nullptr, BSTNode *parent=nullptr);

    ~BSTNode();
};

template<typename T>
class BSTree {
private:
    BSTNode<T> *mRoot;
public:

    BSTree(const initializer_list<T> &keys);

    explicit BSTree(BSTNode<T> *root=nullptr);

    ~BSTree();

    BSTNode<T> *insert(T key);

    bool remove(T key);

    bool remove(BSTNode<T> *p);

    void releaseNode(BSTNode<T> *p);

    BSTNode<T> *findMin(BSTNode<T> *p);

    const BSTNode<T> *find(T key);

    const BSTNode<T> *getRoot();
};


/**************************************
 *           definition               *
 **************************************
 */


template<typename T>
BSTNode<T>::BSTNode(T key, BSTNode *left, BSTNode *right, BSTNode *parent): mKey(key), mLeft(left), mRight(right), mParent(parent){}

template<typename T>
BSTNode<T>::~BSTNode() {
    delete mLeft;
    delete mRight;
}

/*
 * 1. Create the leaf node
 * 2. If root is null, assign it to root
 * 3. otherwise traverse down to a leaf node and insert the new node
 *
 * Return: a pointer to the inserted node.
 *
 */
template<typename T>
BSTNode<T> *BSTree<T>::insert(T key) {
    auto *leaf = new BSTNode<T>(key);
    if (!mRoot) {
        mRoot = leaf;
        return mRoot;
    }
    BSTNode<T> *cur = mRoot, *prev = nullptr;
    while (cur) {
        prev = cur;
        cur = (key < cur->mKey) ? cur->mLeft : cur->mRight;
    }
    // check whether to put it to the left or right
    if (key < prev->mKey) {
        prev->mLeft = leaf;
    } else {
        prev->mRight = leaf;
    }
    leaf->mParent = prev;
    return leaf;
}

template<typename T>
ostream &traverseInOrder(const BSTNode<T> *root, ostream &os) {
    if (!root)
        return os;
    traverseInOrder(root->mLeft, os);
    os << root->mKey << ' ';
    traverseInOrder(root->mRight, os);
    return os;
}

template<typename T>
ostream &traversePreOrder(const BSTNode<T> *root, ostream &os) {
    if (!root)
        return os;
    os << root->mKey << ' ';
    traversePreOrder(root->mLeft, os);
    traversePreOrder(root->mRight, os);
    return os;
}

template<typename T>
ostream &traversePostOrder(const BSTNode<T> *root, ostream &os) {
    if (!root)
        return os;
    traversePostOrder(root->mLeft, os);
    traversePostOrder(root->mRight, os);
    os << root->mKey << ' ';
    return os;
}

template<typename T>
const BSTNode<T> *BSTree<T>::getRoot() {
    return mRoot;
}

template<typename T>
BSTree<T>::~BSTree() {
    delete mRoot;
}

template<typename T>
BSTree<T>::BSTree(const initializer_list<T> &keys): mRoot(nullptr) {
    for (const auto &key: keys) {
        insert(key);
    }
}

template<typename T>
BSTree<T>::BSTree(BSTNode<T> *root): mRoot(root){

}

template<typename T>
const BSTNode<T> *BSTree<T>::find(T key) {
    BSTNode<T> *root = mRoot;
    while(root && root->mKey != key){
        root = (key < root->mKey) ? root->mLeft : root->mRight;
    }
    return root;
}

/*
 * 1. Find the target node
 * 2. Call the overloaded version to remove the target node.
 *
 * Return: true if step 1 successfully find the target else false.
 */
template<typename T>
bool BSTree<T>::remove(T key) {
    BSTNode<T> *root = mRoot;
    while(root && root->mKey != key){
        root = (key < root->mKey) ? root->mLeft : root->mRight;
    }
    return remove(root);
}

/*
 * Always remember to change two pointers of the node *p to be removed.
 *   1. p's parent's child;
 *   2. p's child's parent;
 *
 * Return: false if `p` is NULL else true.
 */
template<typename T>
bool BSTree<T>::remove(BSTNode<T> *p){
    if(p){
        // if at least one of the children is NULL
        if(!p->mLeft || !p->mRight){
            BSTNode<T> *oldP = p, *parent = p->mParent;
            p = (!p->mLeft) ? p->mRight : p->mLeft;
            // 1. if the parent is null, reset the root of the tree
            // otherwise change the child of parent
            if(!parent)
                mRoot = p;
            else{
                if(parent->mLeft == oldP)
                    parent->mLeft = p;
                else
                    parent->mRight = p;
            }
            // 2. if the children is not null, change its parent
            if(p)
                p->mParent = parent;
            releaseNode(oldP);
        }else{
            BSTNode<T> *min = findMin(p->mRight);
            p->mKey = min->mKey;
            // 1. change parent's child
            if(p == min->mParent){
                p->mRight = min->mRight;
            }else{
                min->mParent->mLeft = min->mRight;
            }
            // 2. change child's parent
            if(p->mRight)
                p->mRight->mParent = p;
            releaseNode(min);
        }
        return true;
    }
    return false;
}

template<typename T>
void BSTree<T>::releaseNode(BSTNode<T> *p){
    if(p) {
        p->mLeft = nullptr;
        p->mRight = nullptr;
        delete p;
    }
}

template<typename T>
BSTNode<T> *BSTree<T>::findMin(BSTNode<T> *p){
    while(p && p->mLeft){
        p = p->mLeft;
    }
    return p;
}

void testBSTWithInteger(){
    BSTree<int> t{0, 9, 7, 4, 3, 5, -1};
    cout << "In order output: "; traverseInOrder(t.getRoot(), cout) << endl;
    cout << " Desired output: -1 0 3 4 5 7 9" << endl;
    printf("%d %s in the tree.\n", 0, t.find(0) ? "" : "not");
    printf("%d %s in the tree.\n", 1, t.find(1) ? "" : "not");

    printf("%d %s the tree.\n", 0, t.remove(0) ? "removed from" : "not in");
    traverseInOrder(t.getRoot(), cout) << endl;
    printf("%d %s the tree.\n", 1, t.remove(1) ? "removed from" : "not in");
    traverseInOrder(t.getRoot(), cout) << endl;

    cout << endl;
}

void testBSTWithString(){
    BSTree<string> t{"justin", "jake", "selena", "gomez"};
    cout << "In order output: "; traverseInOrder(t.getRoot(), cout) << endl;
    cout << " Desired output: gomez jake justin selena" << endl;

    cout << endl;
}

void testBSTree(){
    testBSTWithInteger();
    testBSTWithString();
}

#endif //SUANFAXINJIE_BS_H
