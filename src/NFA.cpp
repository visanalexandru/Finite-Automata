//
// Created by visan on 3/28/22.
//

#include "NFA.h"
#include<iostream>

bool NFA::valid(const std::string &word) const {
    // The set of current states.
    std::set<state> states = {start};

    for (letter x: word) {

        // The set for the next iteration of states.
        std::set<state> next;

        // Iterate through all the current states.
        for (state s: states) {

            if (graph.find(s) == graph.end())
                continue;

            const auto &vec = graph.find(s)->second;

            for (Edge edge: vec) {
                if (edge.transition == x) {
                    next.insert(edge.next);
                }
            }
        }

        if (next.empty()) { // if there are no potential matches, reject the pattern.
            return false;
        }

        // The next set of states become the current set of states.
        states.swap(next);
    }

    // Now we need to check if at least one state is final.
    for (state s: states) {
        if (final.find(s) != final.end()) {
            return true;
        }
    }

    return false;
}


DFA NFA::to_dfa() const {
    //First get all the letters used in the graph.
    std::set<letter> letters;
    for (const auto &p: graph) {
        for (Edge x: p.second) {
            letters.insert(x.transition);
        }
    }

    //Then apply subset construction.

    //The resulted dfa.
    DFA result;

    //The nodes of the new graph.
    std::set<std::set<state>> nodes;

    //Map each subset to a new state in the new automaton.
    std::map<std::set<state>, state> indices;

    //The bfs queue.
    std::deque<std::set<state>> queue;

    //The starting set is the start point.
    size_t num_nodes = 0;
    nodes.insert({start});
    indices[{start}] = num_nodes++;
    queue.push_back({start});

    while (!queue.empty()) {
        std::set<state> current_state = queue.front();
        queue.pop_front();

        for (letter x: letters) {
            std::set<state> next_state;
            for (state s: current_state) {

                if (graph.find(s) == graph.end())
                    continue;

                const auto &edge_list = graph.find(s)->second;

                for (Edge edge: edge_list) {
                    if (edge.transition == x) {
                        next_state.insert(edge.next);
                    }
                }
            }

            if (!next_state.empty()) {
                if (nodes.find(next_state) == nodes.end()) {
                    nodes.insert(next_state);
                    queue.push_back(next_state);
                    indices[next_state] = num_nodes++;
                }
                result.add_edge(indices[current_state], indices[next_state], x);
            }
        }
    }

    //Now find all the final states.
    //A state is final if it contains a final state from the original automaton.
    for (const auto &p: indices) {
        for (state s: p.first) {
            if (final.find(s) != final.end()) {
                result.set_final(p.second);
                break;
            }
        }
    }

    result.set_initial(0);
    return result;
}