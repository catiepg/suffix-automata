#ifndef SUFFIX_AUTOMATA_H
#define SUFFIX_AUTOMATA_H

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
    State* sink;

    int statesCount;
    int transitionsCount;

    SuffixAutomata();

    void add(char letter);
    State* update(State* currentSink, char a);
    State* split(State* parent, State* child, int a);
    int setFinalStates();
};

#endif
