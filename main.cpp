#include <cstdio>
#include <string>

#include "automata.h"

int main(int argc, char *argv[]) {
    SuffixAutomata* automata = new SuffixAutomata();

    std::string word = "abcbcab";
    for (int i = 0; i < word.length(); i++) {
        automata->add(word[i]);
    }

    int finalStatesCount = automata->setFinalStates();
    printf("states count: %d\ntransitions count: %d\nfinal count: %d\n",
            automata->statesCount, automata->transitionsCount, finalStatesCount);

    return 0;
}
