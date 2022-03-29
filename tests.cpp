//
// Created by visan on 2/25/22.
//

#define CATCH_CONFIG_MAIN

#include"catch.hpp"
#include"src/NFA.h"
#include"src/DFA.h"

TEST_CASE("DFA-Words that start with 0 and end in 1") {
    DFA dfa;
    dfa.add_edge(1, 4, '1');
    dfa.add_edge(4, 4, '1');
    dfa.add_edge(4, 4, '0');
    dfa.add_edge(1, 2, '0');
    dfa.add_edge(2, 2, '0');
    dfa.add_edge(2, 3, '1');
    dfa.add_edge(3, 2, '0');
    dfa.add_edge(3, 3, '1');
    dfa.set_final(3);
    dfa.set_initial(1);

    REQUIRE(dfa.valid("0000101010101111") == true);
    REQUIRE(dfa.valid("10111010101") == false);
    REQUIRE(dfa.valid("00") == false);
    REQUIRE(dfa.valid("001") == true);
    REQUIRE(dfa.valid("01000000") == false);
}

TEST_CASE("DFA-Words with the first and last letter equal") {
    DFA dfa;
    dfa.add_edge(0, 1, 'a');
    dfa.add_edge(1, 1, 'a');
    dfa.add_edge(1, 2, 'b');
    dfa.add_edge(2, 1, 'a');
    dfa.add_edge(2, 2, 'b');
    dfa.add_edge(0, 3, 'b');
    dfa.add_edge(3, 3, 'b');
    dfa.add_edge(3, 4, 'a');
    dfa.add_edge(4, 3, 'b');
    dfa.add_edge(4, 4, 'a');
    dfa.set_final(1);
    dfa.set_final(3);
    dfa.set_initial(0);
    REQUIRE(dfa.valid("abababaaaabab") == false);
    REQUIRE(dfa.valid("a") == true);
    REQUIRE(dfa.valid("b") == true);
    REQUIRE(dfa.valid("ababababaaaabba") == true);
    REQUIRE(dfa.valid("babaaababa") == false);
    REQUIRE(dfa.valid("bbabab") == true);


}

TEST_CASE("DFA-Words that start with three consecutive 0's.") {
    DFA dfa;
    dfa.add_edge(0, 0, '1');
    dfa.add_edge(0, 1, '0');
    dfa.add_edge(1, 2, '0');
    dfa.add_edge(2, 3, '0');
    dfa.add_edge(3, 1, '0');
    dfa.add_edge(3, 3, '1');
    dfa.set_final(3);
    dfa.set_initial(0);
    REQUIRE(dfa.valid("") == false);
    REQUIRE(dfa.valid("110001111") == true);
    REQUIRE(dfa.valid("0010001010010") == false);
    REQUIRE(dfa.valid("010100101010") == false);
    REQUIRE(dfa.valid("11111111111111111000") == true);
}

TEST_CASE("DFA-Words with even numbers of 0 and 1.") {
    DFA dfa;
    dfa.add_edge(0, 1, '0');
    dfa.add_edge(1, 0, '0');
    dfa.add_edge(0, 3, '1');
    dfa.add_edge(3, 0, '1');
    dfa.add_edge(3, 2, '0');
    dfa.add_edge(2, 3, '0');
    dfa.add_edge(2, 1, '1');
    dfa.add_edge(1, 2, '1');
    dfa.set_final(0);
    dfa.set_initial(0);
    REQUIRE(dfa.valid("10101000010101101010") == false);
    REQUIRE(dfa.valid("11010101010000") == true);
    REQUIRE(dfa.valid("0000") == true);
    REQUIRE(dfa.valid("11") == true);
    REQUIRE(dfa.valid("0001010001") == false);
    REQUIRE(dfa.valid("") == true);
}

TEST_CASE("NFA-Words that contain 00 or 11 as a substring") {
    NFA ndfa;
    ndfa.add_edge(1, 1, '0');
    ndfa.add_edge(1, 1, '1');
    ndfa.add_edge(1, 2, '0');
    ndfa.add_edge(2, 4, '0');
    ndfa.add_edge(1, 3, '1');
    ndfa.add_edge(3, 4, '1');
    ndfa.add_edge(4, 4, '0');
    ndfa.add_edge(4, 4, '1');
    ndfa.set_final(4);
    ndfa.set_initial(1);

    REQUIRE(ndfa.valid("0101010101") == false);
    REQUIRE(ndfa.valid("01011") == true);
    REQUIRE(ndfa.valid("01") == false);
    REQUIRE(ndfa.valid("00") == true);
    REQUIRE(ndfa.valid("10") == false);
    REQUIRE(ndfa.valid("10101101010") == true);

    //Test conversion.
    DFA dfa = ndfa.to_dfa();

    REQUIRE(dfa.valid("0101010101") == false);
    REQUIRE(dfa.valid("01011") == true);
    REQUIRE(dfa.valid("01") == false);
    REQUIRE(dfa.valid("00") == true);
    REQUIRE(dfa.valid("10") == false);
    REQUIRE(dfa.valid("10101101010") == true);

}

TEST_CASE("NFA-Words that end with 101") {
    NFA ndfa;
    ndfa.add_edge(1, 1, '0');
    ndfa.add_edge(1, 1, '1');
    ndfa.add_edge(1, 2, '1');
    ndfa.add_edge(2, 3, '0');
    ndfa.add_edge(3, 4, '1');
    ndfa.set_final(4);
    ndfa.set_initial(1);

    REQUIRE(ndfa.valid("101011101010") == false);
    REQUIRE(ndfa.valid("111111") == false);
    REQUIRE(ndfa.valid("01011101") == true);
    REQUIRE(ndfa.valid("00000111101") == true);
    REQUIRE(ndfa.valid("22101") == false);

    //Test conversion.
    DFA dfa = ndfa.to_dfa();
    REQUIRE(dfa.valid("101011101010") == false);
    REQUIRE(dfa.valid("111111") == false);
    REQUIRE(dfa.valid("01011101") == true);
    REQUIRE(dfa.valid("00000111101") == true);
    REQUIRE(dfa.valid("22101") == false);
}

TEST_CASE("NFA-Words that only contain 'a' or words of the form 'ab'*") {
    NFA ndfa;
    ndfa.add_edge(1, 2, 'a');
    ndfa.add_edge(2, 2, 'a');
    ndfa.add_edge(1, 3, 'a');
    ndfa.add_edge(3, 4, 'b');
    ndfa.add_edge(4, 3, 'a');
    ndfa.set_final(1);
    ndfa.set_final(2);
    ndfa.set_final(4);
    ndfa.set_initial(1);
    REQUIRE(ndfa.valid("ababbab") == false);
    REQUIRE(ndfa.valid("aaaaaa") == true);
    REQUIRE(ndfa.valid("a") == true);
    REQUIRE(ndfa.valid("ababababab") == true);
    REQUIRE(ndfa.valid("bababab") == false);

    //Test conversion.
    DFA dfa = ndfa.to_dfa();
    REQUIRE(dfa.valid("ababbab") == false);
    REQUIRE(dfa.valid("aaaaaa") == true);
    REQUIRE(dfa.valid("a") == true);
    REQUIRE(dfa.valid("ababababab") == true);
    REQUIRE(dfa.valid("bababab") == false);
}

TEST_CASE("NFA-Words for which the second to last symbol is 1") {
    NFA nfa;
    nfa.add_edge(0, 0, '1');
    nfa.add_edge(0, 0, '0');
    nfa.add_edge(0, 1, '1');
    nfa.add_edge(1, 2, '0');
    nfa.add_edge(1, 2, '1');
    nfa.set_final(2);
    nfa.set_initial(0);
    REQUIRE(nfa.valid("1010111101010") == true);
    REQUIRE(nfa.valid("") == false);
    REQUIRE(nfa.valid("0000001") == false);
    REQUIRE(nfa.valid("1010101000010") == true);

    //Test conversion.
    DFA dfa = nfa.to_dfa();
    REQUIRE(dfa.valid("1010111101010") == true);
    REQUIRE(dfa.valid("") == false);
    REQUIRE(dfa.valid("0000001") == false);
    REQUIRE(dfa.valid("1010101000010") == true);
}

TEST_CASE("NFA-Words that are concatenations of 10 and 101") {
    NFA nfa;
    nfa.add_edge(3, 2, '1');
    nfa.add_edge(2, 3, '0');
    nfa.add_edge(2, 1, '0');
    nfa.add_edge(1, 3, '1');
    nfa.set_initial(3);
    nfa.set_final(3);
    REQUIRE(nfa.valid("") == true);
    REQUIRE(nfa.valid("100110101010111") == false);
    REQUIRE(nfa.valid("1010110") == true);
    REQUIRE(nfa.valid("1010101010") == true);
    REQUIRE(nfa.valid("10110101101010") == true);
    REQUIRE(nfa.valid("1010010101101010") == false);

    //Test conversion.
    DFA dfa = nfa.to_dfa();

    REQUIRE(nfa.valid("") == true);
    REQUIRE(nfa.valid("100110101010111") == false);
    REQUIRE(nfa.valid("1010110") == true);
    REQUIRE(nfa.valid("1010101010") == true);
    REQUIRE(nfa.valid("10110101101010") == true);
    REQUIRE(nfa.valid("1010010101101010") == false);
}

TEST_CASE("NFA-Words that have a 1 two characters from the end of the string") {
    NFA nfa;
    nfa.add_edge(0, 0, '0');
    nfa.add_edge(0, 0, '1');
    nfa.add_edge(0, 1, '1');
    nfa.add_edge(1, 2, '0');
    nfa.add_edge(1, 2, '1');
    nfa.add_edge(2, 3, '0');
    nfa.add_edge(2, 3, '1');
    nfa.set_initial(0);
    nfa.set_final(3);

    REQUIRE(nfa.valid("") == false);
    REQUIRE(nfa.valid("101011101010") == false);
    REQUIRE(nfa.valid("101111010110") == true);
    REQUIRE(nfa.valid("100") == true);
    REQUIRE(nfa.valid("00010101000") == false);

    //Test conversion.
    DFA dfa = nfa.to_dfa();
    std::cout << dfa;
    REQUIRE(dfa.valid("") == false);
    REQUIRE(dfa.valid("101011101010") == false);
    REQUIRE(dfa.valid("101111010110") == true);
    REQUIRE(dfa.valid("100") == true);
    REQUIRE(dfa.valid("00010101000") == false);
}
