//
// Created by visan on 3/28/22.
//

#ifndef FINITE_AUTOMATA_UTIL_H
#define FINITE_AUTOMATA_UTIL_H

#include <cstdio>

typedef size_t state;
typedef char letter;

struct Edge {
    state next;
    letter transition;
};

#endif //FINITE_AUTOMATA_UTIL_H
