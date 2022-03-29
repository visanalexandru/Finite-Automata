//
// Created by visan on 3/28/22.
//

#ifndef FINITE_AUTOMATA_NFA_H
#define FINITE_AUTOMATA_NFA_H

#include<queue>
#include"Automaton.h"
#include"DFA.h"

//This class implements a non-deterministic finite automaton.
class NFA : public Automaton {
public:
    //Checks if the word is accepted by the automaton.
    bool valid(const std::string &word) const override;

    //Converts the automaton to a deterministic automaton.
    DFA to_dfa() const;
};


#endif //FINITE_AUTOMATA_NFA_H
