#ifndef SUFFIX_AUTOMATA_H
#define SUFFIX_AUTOMATA_H

#include <unordered_map>
#include <vector>

const int NONE = -1;

struct Transition;

struct State {
    std::unordered_map<char, int> next;
    std::unordered_map<char, bool> primary;
    int suffixLink;
    bool isFinal;

    State() : suffixLink(NONE), isFinal(false) {}
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
    int update(int currentSink, char a);
    int split(int parent, int child, int a);
    int setFinalStates();
};

#endif
