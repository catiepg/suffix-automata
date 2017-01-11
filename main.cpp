#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>

#include "automata.h"

const unsigned int BUF_SIZE = 1<<20;

SuffixAutomata* construct(char* in) {
    int fileDesc = open(in, O_RDONLY);;

    struct stat buf;
    fstat(fileDesc, &buf);
    int size = buf.st_size;

    SuffixAutomata* automata = new SuffixAutomata(size);

    if (fileDesc == -1) perror("open");
    ssize_t n = 0;
    char* buffer = new char[BUF_SIZE];
    do {
        n = read(fileDesc, buffer, BUF_SIZE);
        for (int i = 0; i < n; i++) {
            if (buffer[i] == '\n') break;
            automata->addLetter(buffer[i]);
        }
    } while (n > 0);
    delete[] buffer;

    return automata;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Expecting file name\n");
        return 1;
    }

    SuffixAutomata* automata = construct(argv[1]);

    int finalStatesCount = automata->getFinalStates();
    printf("states count: %lu\ntransitions count: %d\nfinal count: %d\n",
            automata->states.size(), automata->transitionsCount, finalStatesCount);

    return 0;
}
