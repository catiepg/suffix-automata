#include <cstdio>

#include "automata.h"

int main() {
    SuffixAutomata* automata = new SuffixAutomata;

    automata->build("abcbc");

    printf("states count: %d, transitions count: %d, final count: %d\n",
            automata->statesCount, automata->transitionsCount,
            automata->finalStatesCount);
    return 0;
}
