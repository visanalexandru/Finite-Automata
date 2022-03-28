//
// Created by visan on 3/28/22.
//

#ifndef FINITE_AUTOMATA_NFA_H
#define FINITE_AUTOMATA_NFA_H

#include"Util.h"
#include<vector>
#include<map>
#include<set>
#include<deque>
#include"DFA.h"

//This class implements a non-deterministic finite automaton.
class NFA {
private:
    // The graph of the automaton.
    std::map<state, std::vector<Edge>> graph;

    //The set of final states.
    std::set<state> final;

    state start;
public:
    NFA();

    //Sets the initial state to the given one.
    void set_initial(state x);

    //Adds a new edge into the automaton.
    void add_edge(state a, state b, letter s);

    //Adds a new final state to the automaton.
    void set_final(state x);

    //Checks if the word is accepted by the automaton.
    bool valid(const std::string &word) const;

    //Converts the automaton to a deterministic automaton.
    DFA to_dfa() const;
};


#endif //FINITE_AUTOMATA_NFA_H
