#include "automata.h"

SuffixAutomata::SuffixAutomata(int size) {
    this->transitionsCount = 0;
    this->sink = SOURCE;
    this->inputSize = size;

    this->states.emplace_back();
}

int SuffixAutomata::addState() {
    if (this->states.size() > this->inputSize &&
            this->states.capacity() == this->states.size()) {
        this->states.reserve(this->states.capacity() + (this->inputSize / 2));
    }
    this->states.emplace_back();
    return this->states.size() - 1;
}

void SuffixAutomata::addTransition(int from, int index, int to, bool primary) {
    this->states[from].next.set(index, to);
    this->states[from].primary[index] = primary;
    this->transitionsCount++;
}

void SuffixAutomata::addLetter(char letter) {
    this->sink = this->update(this->sink, letter);
}

int SuffixAutomata::update(int currentSink, char letter) {
    int index = letter - FIRST_LETTER;

    int newSink = this->addState();
    this->addTransition(currentSink, index, newSink, true);

    int current = currentSink;
    int suffix = NONE;

    while (current != SOURCE && suffix == NONE) {
        current = this->states[current].suffixLink;
        if (this->states[current].next.get(index) == NONE) {
            this->addTransition(current, index, newSink, false);
        } else if (this->states[current].primary[index]) {
            suffix = this->states[current].next.get(index);
        } else {
            int child = this->states[current].next.get(index);
            suffix = this->split(current, child, index);
        }
    }

    if (suffix == NONE) suffix = SOURCE;

    this->states[newSink].suffixLink = suffix;
    return newSink;
}

int SuffixAutomata::split(int parent, int child, int index) {
    int newChild = this->addState();

    this->states[parent].next.set(index, newChild);
    this->states[parent].primary[index] = true;

    if (this->states[child].next.size == 1) {
        int i = this->states[child].next.idx;
        int next = this->states[child].next.get(i);
        this->addTransition(newChild, i, next, false);
    } else if (this->states[child].next.size > 1) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (this->states[child].next.get(i) != NONE) {
                int next = this->states[child].next.get(i);
                this->addTransition(newChild, i, next, false);
            }
        }
    }

    this->states[newChild].suffixLink = this->states[child].suffixLink;
    this->states[child].suffixLink = newChild;

    int current = parent;
    while (current != SOURCE) {
        current = this->states[current].suffixLink;
        int a = this->states[current].next.index(child);
        if (a != NONE && !this->states[current].primary[a]) {
            this->states[current].next.set(a, newChild);
        } else {
            break;
        }
    }
    return newChild;
}

int SuffixAutomata::getFinalStates() {
    int count = 1;
    int s = this->sink;
    while (s != SOURCE) {
        count++;
        s = this->states[s].suffixLink;
    }
    return count;
}
