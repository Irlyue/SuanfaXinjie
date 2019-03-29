//
// Created by wenfeng on 19-3-29.
//

#ifndef SUANFAXINJIE_BST_UTILS_H
#define SUANFAXINJIE_BST_UTILS_H

#include "bst.h"
#include "stl_utils.h"

template<typename T>
int findInInOrder(const vector<T> &in, T key, int l, int r){
    for(int i = l; i < r; i++){
        if(in[i] == key)
            return i;
    }
    return -1;
}

template<typename T>
BSTNode<T> *fromInPreOrder(const vector<T> &in, const vector<T> &pre, int il, int ir, int pl, int pr){
    if(il >= ir) return nullptr;
    int i = findInInOrder(in, pre[pl], il, ir);
    int nbLeft = i - il;
    //           il       [il, i)       i      [i+1, ir)      il
    // In order: -----------------------*----------------------
    //                    [pl+1, pl+nbLeft+1), [pl+nbLeft+1, pr)
    //Pre order: *---------------------------------------------
    auto *left = fromInPreOrder(in, pre, il, i, pl + 1, pl + nbLeft + 1);
    auto *right = fromInPreOrder(in, pre, i + 1, ir, pl + 1 + nbLeft, pr);
    auto *root = new BSTNode<T>(pre[pl], left, right);
    return root;
}

template<typename T>
BSTNode<T> *reconstructBinaryTreeFromInPreOrder(const vector<T> &in, const vector<T> &pre){
    return fromInPreOrder(in, pre, 0, in.size(), 0, pre.size());
}

/*
 * The binary tree looks like:
 *                 1
 *                / \
 *               2   3
 *              /   / \
 *             4   5  6
 */
void testReconstructBSTreeFromInPreOrder(){
    vector<int> pre{1, 2, 4, 3, 5, 6};
    vector<int> in{4, 2, 1, 5, 3, 6};
    BSTNode<int> *root = reconstructBinaryTreeFromInPreOrder(in, pre);
    cout << " Pre order: ";
    printVector(pre.cbegin(), pre.cend(), cout) << endl;
    cout << "  In order: ";
    printVector(in.cbegin(), in.cend(), cout) << endl;
    cout << "After reconstruction" << endl;
    cout << " Pre order: ";
    traversePreOrder(root, cout) << endl;
    cout << "  In order: ";
    traverseInOrder(root, cout) << endl;
    cout << "Post order: ";
    traversePostOrder(root, cout) << endl;
}


#endif //SUANFAXINJIE_BST_UTILS_H
