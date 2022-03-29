//
// Created by visan on 3/28/22.
//

#ifndef FINITE_AUTOMATA_UTIL_H
#define FINITE_AUTOMATA_UTIL_H

#include <cstdio>
#include<algorithm>

typedef size_t state;
typedef char letter;

struct Edge {
    state next;
    letter transition;
};

template<class x>
std::set<x> intersection(const std::set<x> &a, const std::set<x> &b) {
    std::set<x> result;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
    return result;
}

template<class x>
std::set<x> difference(const std::set<x> &a, const std::set<x> &b) {
    std::set<x> result;
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
    return result;
}

#endif //FINITE_AUTOMATA_UTIL_H
