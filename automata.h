#ifndef SUFFIX_AUTOMATA_H
#define SUFFIX_AUTOMATA_H

#include <vector>
#include <bitset>

#include "array.h"

const unsigned int ALPHABET_SIZE = 26;
const unsigned int FIRST_LETTER = 97;

const int SOURCE = 0;

struct State {
    Array<int, NONE, ALPHABET_SIZE> next;
    std::bitset<ALPHABET_SIZE> primary;

    int suffixLink;
    bool isFinal;

    State();
};

struct SuffixAutomata {
    std::vector<State> states;
    int transitionsCount;
    int sink;

    SuffixAutomata();

    void add(char letter);
    int update(int currentSink, char symbol);
    int split(int parent, int child, int symbol);
    int setFinalStates();

    void addTransition(int from, int index, int to, bool primary);

    bool recognize(const char* suffix);
};

#endif
