#ifndef SUFFIX_AUTOMATA_H
#define SUFFIX_AUTOMATA_H

#include <string>

const int FIRST_SYMBOL = 97;
const int ALPHABET_SIZE = 26;

struct Transition;

struct State {
    Transition* next[ALPHABET_SIZE];
    State* suffixLink;
    bool isFinal;

    State();
    int getTransition(State* state);
};

struct Transition {
    State* state;
    bool primary;

    Transition(State* s, bool p) : state(s), primary(p) {}
    Transition(State* s) : Transition(s, false) {}
};

struct SuffixAutomata {
    State* source;
    int statesCount;
    int transitionsCount;
    int finalStatesCount;

    SuffixAutomata() :
        statesCount(0), transitionsCount(0), finalStatesCount(0) {}

    void build(std::string content);
    State* update(State* currentSink, char a);
    State* split(State* parent, State* child, int a);
};

#endif
