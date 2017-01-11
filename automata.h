#ifndef SUFFIX_AUTOMATA_H
#define SUFFIX_AUTOMATA_H

#include <vector>
#include <bitset>

#include "intarray.h"

const int NONE = -1;

const unsigned int ALPHABET_SIZE = 26;
const unsigned int FIRST_LETTER = 97;

const int SOURCE = 0;

struct State {
    IntArray<ALPHABET_SIZE> next;
    std::bitset<ALPHABET_SIZE> primary;

    int suffixLink;

    State() : suffixLink(NONE) {}
};

struct SuffixAutomata {
    std::vector<State> states;
    int transitionsCount;
    int sink;
    int inputSize;

    SuffixAutomata(int size);

    int addState();
    void addTransition(int from, int index, int to, bool primary);

    void addLetter(char letter);
    int update(int currentSink, char letter);
    int split(int parent, int child, int index);
    int getFinalStates();
};

#endif
