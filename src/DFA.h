//
// Created by visan on 3/28/22.
//

#ifndef FINITE_AUTOMATA_DFA_H
#define FINITE_AUTOMATA_DFA_H

#include"Automaton.h"

//This class implements a deterministic finite automaton.
class DFA : public Automaton {
public:
    //Adds a new edge into the automaton.
    void add_edge(state a, state b, letter s) override;

    //Checks if the word is accepted by the automaton.
    bool valid(const std::string &word) const override;

    // Returns a minimized version of the automaton.
    DFA minimize() const;
};


#endif //FINITE_AUTOMATA_DFA_H
