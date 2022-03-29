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

std::ostream &operator<<(std::ostream &stream, const Automaton &automaton) {
    stream << "digraph automaton{" << std::endl;
    stream << "node [shape=circle];" << std::endl;
    stream << "start [shape=none];" << std::endl;
    stream << "start -> " << automaton.start << ";" << std::endl;
    for (auto &node: automaton.graph) {
        for (const Edge &edge: node.second) {
            stream << node.first << " -> " << edge.next << " [label=" << edge.transition << "];" << std::endl;
        }
    }
    for (state final_state: automaton.final) {
        stream << final_state << " [shape=doublecircle];" << std::endl;
    }
    stream << "}" << std::endl;
    return stream;
}