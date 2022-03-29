//
// Created by visan on 3/29/22.
//

#ifndef FINITE_AUTOMATA_AUTOMATON_H
#define FINITE_AUTOMATA_AUTOMATON_H

#include<map>
#include<set>
#include<vector>
#include<ostream>
#include"Util.h"

//This class is the base class for all the automatons.
class Automaton {
protected:
    // The graph of the automaton.
    std::map<state, std::vector<Edge>> graph;

    //The set of final states.
    std::set<state> final;

    //The start state.
    state start;

    //Returns the set of states that are not final.
    std::set<state> non_final() const;

    //Returns the alphabet of the automaton.
    std::set<letter> alphabet() const;

private:
public:
    Automaton();

    //Sets the initial state to the given one.
    virtual void set_initial(state x);

    //Adds a new final state to the automaton.
    virtual void set_final(state x);

    //Adds a new edge into the automaton.
    virtual void add_edge(state a, state b, letter s);

    //Checks if the word is accepted by the automaton.
    virtual bool valid(const std::string &word) const = 0;

    //Outputs the automaton to the given stream.
    friend std::ostream &operator<<(std::ostream &stream, const Automaton &automaton);
};


#endif //FINITE_AUTOMATA_AUTOMATON_H
