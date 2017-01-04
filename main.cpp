#include <fcntl.h>
#include <unistd.h>
#include <cstdio>

#include "automata.h"

const unsigned int BUF_SIZE = 1<<10;

struct Reader {
    int fd;

    Reader(char* fileName);
    ssize_t readInto(char*& buffer);
};

Reader::Reader(char* fileName) {
    int fd = open(fileName, O_RDONLY);
    if (fd == -1) {
        perror("open");
    }
    this->fd = fd;
}

ssize_t Reader::readInto(char*& buffer) {
    ssize_t r = read(this->fd, buffer, BUF_SIZE);

    if (r <= 0) {
        close(this->fd);
    }
    return r;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Expecting file name\n");
        return 1;
    }

    SuffixAutomata* automata = new SuffixAutomata();

    Reader* r = new Reader(argv[1]);
    ssize_t n = 1;
    char* b = new char[BUF_SIZE];
    while (n > 0) {
        n = r->readInto(b);
        for (int i = 0; i < n; i++) {
            if (b[i] == '\n') break;
            automata->add(b[i]);
        }
    }

    int finalStatesCount = automata->setFinalStates();
    printf("states count: %d\ntransitions count: %d\nfinal count: %d\n",
            automata->statesCount, automata->transitionsCount, finalStatesCount);

    return 0;
}
