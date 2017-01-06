#ifndef SUFFIX_AUTOMATA_H
#define SUFFIX_AUTOMATA_H

#include <unordered_map>
#include <vector>

const int FIRST_SYMBOL = 97;
const int ALPHABET_SIZE = 26;

const int NONE = -1;

struct Transition;

struct State {
    std::unordered_map<char, int> next;
    int suffixLink;
    bool isFinal;

    State();
};

struct Transition {
    int state;
    bool primary;

    Transition(int s, bool p) : state(s), primary(p) {}
};

struct SuffixAutomata {
    std::vector<State> states;
    std::vector<Transition> transitions;

    int source;
    int sink;

    SuffixAutomata();

    void add(char letter);
    int update(int currentSink, char a);
    int split(int parent, int child, int a);
    int setFinalStates();
    char getTransition(int from, int to);
};

#endif
