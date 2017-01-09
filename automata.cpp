#include <cstring>

#include "automata.h"

State::State() {
    this->suffixLink = NONE;
    this->isFinal = false;
}

void SuffixAutomata::addTransition(int from, int index, int to, bool primary) {
    this->states[from].next[index] = to;
    this->states[from].primary[index] = primary;
    this->transitionsCount++;
}

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

    int newSink = this->states.size();
    this->states.emplace_back();

    this->addTransition(currentSink, index, newSink, true);

    int current = currentSink;
    int suffix = NONE;

    while (current != SOURCE && suffix == NONE) {
        current = this->states[current].suffixLink;
        State currentState = this->states[current];
        if (currentState.next[index] == NONE) {
            this->addTransition(current, index, newSink, false);
        } else if (currentState.primary[index]) {
            suffix = currentState.next[index];
        } else {
            int child = currentState.next[index];
            suffix = this->split(current, child, index);
        }
    }

    if (suffix == NONE) suffix = SOURCE;

    this->states[newSink].suffixLink = suffix;
    return newSink;
}

int SuffixAutomata::split(int parent, int child, int index) {
    int newChild = this->states.size();
    this->states.emplace_back();

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

int SuffixAutomata::setFinalStates() {
    this->states[SOURCE].isFinal = true;
    int count = 1;
    int s = this->sink;
    while (s != SOURCE) {
        this->states[s].isFinal = true;
        count++;
        s = this->states[s].suffixLink;
    }
    return count;
}

bool SuffixAutomata::recognize(const char* word) {
    State currentState = this->states[SOURCE];
    int len = std::strlen(word);
    for (int i = 0; i < len; i++) {
        int next = currentState.next[word[i] - FIRST_LETTER];
        if (next == NONE) return false;
        currentState = this->states[next];
    }
    if (currentState.isFinal) return true;
    return false;
}
