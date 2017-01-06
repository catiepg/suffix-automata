#ifndef SUFFIX_AUTOMATA_H
#define SUFFIX_AUTOMATA_H

#include <unordered_map>
#include <vector>

const unsigned int ALPHABET_SIZE = 26;
const unsigned int FIRST_SYMBOL = 97;

const int NONE = -1;

struct Transition;

struct State {
    int next[ALPHABET_SIZE];
    bool primary[ALPHABET_SIZE];

    int suffixLink;
    bool isFinal;

    // State() : suffixLink(NONE), isFinal(false) {}
    State();
    void addTransition(char symbol, int state, bool primary);
    char getTransition(int state);
};

struct SuffixAutomata {
    std::vector<State> states;

    int transitionsCount;

    int source;
    int sink;

    SuffixAutomata();

    void add(char letter);
    int update(int currentSink, char symbol);
    int split(int parent, int child, int symbol);
    int setFinalStates();
};

#endif
