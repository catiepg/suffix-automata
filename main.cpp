#include <fcntl.h>
#include <unistd.h>
#include <cstdio>

#include "automata.h"

const unsigned int BUF_SIZE = 1<<20;

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
    int count = 0;
    do {
        n = read(fileDesc, buffer, BUF_SIZE);
        for (int i = 0; i < n; i++) {
            if (buffer[i] == '\n') break;
            automata->add(buffer[i]);
            count++;

            if (count % 1000000 == 0) printf("characters added: %d\n", count);
        }
    } while (n > 0);

    int finalStatesCount = automata->setFinalStates();
    printf("states count: %lu\ntransitions count: %d\nfinal count: %d\n",
            automata->states.size(), automata->transitionsCount, finalStatesCount);

    return 0;
}
