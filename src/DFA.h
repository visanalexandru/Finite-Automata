//
// Created by visan on 3/28/22.
//

#ifndef FINITE_AUTOMATA_DFA_H
#define FINITE_AUTOMATA_DFA_H

#include"Util.h"
#include<map>
#include<vector>
#include<set>

//This class implements a deterministic finite automaton.
class DFA {
private:
    std::map<state, std::vector<Edge>> graph;

    //The set of final states.
    std::set<state> final;

    state start;
public:
    DFA();

    //Sets the initial state to the given one.
    void set_initial(state x);

    //Adds a new edge into the automaton.
    void add_edge(state a, state b, letter s);

    //Adds a new final state to the automaton.
    void set_final(state x);

    //Checks if the word is accepted by the automaton.
    bool valid(const std::string &word) const;
};


#endif //FINITE_AUTOMATA_DFA_H
