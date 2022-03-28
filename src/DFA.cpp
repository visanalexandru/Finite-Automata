//
// Created by visan on 3/28/22.
//

#include "DFA.h"

DFA::DFA() : graph(), final(), start(0) {

}

void DFA::set_initial(state x) {
    start = x;
}

void DFA::add_edge(state a, state b, letter s) {
    //If there is already an edge between the two states, overwrite the transition letter.
    for (Edge &edge: graph[a]) {
        if (edge.next == b) {
            edge.transition = s;
            return;
        }
    }
    //If no edge between the two states exist, just add it.
    graph[a].push_back({b, s});
}

void DFA::set_final(state x) {
    final.insert(x);
}


bool DFA::valid(const std::string &word) const {
    state current = start;

    for (letter x: word) {

        if (graph.find(current) == graph.end()) {
            return false;
        }

        const auto &vec = graph.find(current)->second;
        bool found = false;

        //Iterate through all the edges of the current state, see if an edge with the current symbol exists.
        for (const Edge &edge: vec) {
            if (edge.transition == x) {
                found = true;
                current = edge.next;
                break;
            }
        }

        //If we didn't find any edge for the current symbol, reject the word.
        if (!found) {
            return false;
        }
    }

    // If the current state is final, the word is accepted.
    if (final.find(current) != final.end()) {
        return true;
    }
    return false;
}