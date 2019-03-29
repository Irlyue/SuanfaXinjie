//
// Created by wenfeng on 19-3-29.
//

#ifndef SUANFAXINJIE_STL_UTILS_H
#define SUANFAXINJIE_STL_UTILS_H

#include <vector>
#include <iostream>

using namespace std;

template<typename T>
ostream &printVector(T start, T end, ostream &os){
    while(start != end){
        os << *start++ << ' ';
    }
    return os;
}


#endif //SUANFAXINJIE_STL_UTILS_H
