#include "automata.h"

SuffixAutomata::SuffixAutomata() {
    this->transitionsCount = 0;
    this->states.emplace_back();
    this->sink = SOURCE;
}

void SuffixAutomata::add(char letter) {
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
        if (this->states[current].next[index] == NONE) {
            this->addTransition(current, index, newSink, false);
        } else if (this->states[current].primary[index]) {
            suffix = this->states[current].next[index];
        } else {
            int child = this->states[current].next[index];
            suffix = this->split(current, child, index);
        }
    }

    if (suffix == NONE) suffix = SOURCE;

    this->states[newSink].suffixLink = suffix;
    return newSink;
}

int SuffixAutomata::split(int parent, int child, int index) {
    int newChild = this->addState();

    this->states[parent].next[index] = newChild;
    this->states[parent].primary[index] = true;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (this->states[child].next[i] != NONE) {
            int next = this->states[child].next[i];
            this->addTransition(newChild, i, next, false);
        }
    }

    this->states[newChild].suffixLink = this->states[child].suffixLink;
    this->states[child].suffixLink = newChild;

    int current = parent;
    while (current != SOURCE) {
        current = this->states[current].suffixLink;
        int a = this->states[current].next.getIndex(child);
        if (a != NONE && !this->states[current].primary[a]) {
            this->states[current].next[a] = newChild;
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

int SuffixAutomata::addState() {
    this->states.emplace_back();
    if (this->states.capacity() > 70000000 && this->states.size() % 100000 == 0) {
        this->states.shrink_to_fit();
    }
    return this->states.size() - 1;
}

void SuffixAutomata::addTransition(int from, int index, int to, bool primary) {
    this->states[from].next[index] = to;
    this->states[from].primary[index] = primary;
    this->transitionsCount++;
}
