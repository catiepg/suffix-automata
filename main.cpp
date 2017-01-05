#include <fcntl.h>
#include <unistd.h>
#include <cstdio>

#include "automata.h"

const unsigned int BUF_SIZE = 1<<10;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Expecting file name\n");
        return 1;
    }

    SuffixAutomata* automata = new SuffixAutomata();

    int fileDesc = open(argv[1], O_RDONLY);;
    if (fileDesc == -1) perror("open");
    ssize_t n = 0;
    char* buffer = new char[BUF_SIZE];
    do {
        n = read(fileDesc, buffer, BUF_SIZE);
        for (int i = 0; i < n; i++) {
            if (buffer[i] == '\n') break;
            automata->add(buffer[i]);
        }
    } while (n > 0);

    int finalStatesCount = automata->setFinalStates();
    printf("states count: %d\ntransitions count: %d\nfinal count: %d\n",
            automata->statesCount, automata->transitionsCount, finalStatesCount);

    return 0;
}
