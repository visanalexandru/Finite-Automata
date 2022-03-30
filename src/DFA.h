//
// Created by visan on 3/28/22.
//

#ifndef FINITE_AUTOMATA_DFA_H
#define FINITE_AUTOMATA_DFA_H

#include<deque>
#include"Automaton.h"

//This class implements a deterministic finite automaton.
class DFA : public Automaton {
private:
    //Keep a transposed version of the graph to help find the dead states.
    std::map<state, std::vector<state>> transposed;

    //Returns the states of the automaton from which we can get to a final state.
    std::set<state> alive_states() const;

    //Returns the states of the automaton that are reachable from the initial state.
    std::set<state> reachable_states() const;

    //Returns the states that are reachable and alive.
    std::set<state> valid_states() const;

public:
    //Adds a new edge into the automaton.
    void add_edge(state a, state b, letter s) override;

    //Checks if the word is accepted by the automaton.
    bool valid(const std::string &word) const override;

    // Returns a minimized version of the automaton.
    DFA minimize() const;
};


#endif //FINITE_AUTOMATA_DFA_H
