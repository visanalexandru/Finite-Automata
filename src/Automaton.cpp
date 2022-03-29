//
// Created by visan on 3/29/22.
//

#include "Automaton.h"

Automaton::Automaton() : start(0) {

}

void Automaton::set_initial(state x) {
    start = x;
}

void Automaton::set_final(state x) {
    final.insert(x);
}

void Automaton::add_edge(state a, state b, letter s) {
    graph[a].push_back({b, s});
}
