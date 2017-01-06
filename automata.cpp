#include "automata.h"

void State::addTransition(char symbol, int state, bool primary) {
    this->next[symbol] = state;
    this->primary[symbol] = primary;
}

// TODO: retrieve state in linear time.
char State::getTransition(int state) {
    for (auto it : this->next) {
        if (it.second == state) {
            return it.first;
        }
    }
    return -1;
}

SuffixAutomata::SuffixAutomata() {
    this->transitionsCount = 0;
    this->source = 0;
    this->states.emplace_back();
    this->sink = this->source;
}

void SuffixAutomata::add(char letter) {
    this->sink = this->update(this->sink, letter);
}

int SuffixAutomata::update(int currentSink, char letter) {
    int newSink = this->states.size();
    this->states.emplace_back();

    this->states[currentSink].addTransition(letter, newSink, true);
    this->transitionsCount++;

    int current = currentSink;
    int suffix = NONE;

    while (current != this->source && suffix == NONE) {
        current = this->states[current].suffixLink;
        State currentState = this->states[current];
        // ???
        if (currentState.next.find(letter) == currentState.next.end()) {
            this->states[current].addTransition(letter, newSink, false);
            this->transitionsCount++;
        } else if (currentState.primary[letter]) {
            suffix = currentState.next[letter];
        } else {
            int child = currentState.next[letter];
            suffix = this->split(current, child, letter);
        }
    }

    if (suffix == NONE) suffix = this->source;

    this->states[newSink].suffixLink = suffix;
    return newSink;
}

int SuffixAutomata::split(int parent, int child, int symbol) {
    int newChild = this->states.size();
    this->states.emplace_back();

    this->states[parent].next[symbol] = newChild;
    this->states[parent].primary[symbol] = true;

    for (auto it : this->states[child].next) {
        this->states[newChild].addTransition(it.first, it.second, false);
        this->transitionsCount++;
    }

    this->states[newChild].suffixLink = this->states[child].suffixLink;
    this->states[child].suffixLink = newChild;

    int current = parent;
    while (current != this->source) {
        current = this->states[current].suffixLink;
        char a = this->states[current].getTransition(child);
        int t = this->states[current].next[a];
        if (a > 0 && !this->states[current].primary[a]) {
            this->states[current].next[a] = newChild;
        } else {
            break;
        }
    }
    return newChild;
}

int SuffixAutomata::setFinalStates() {
    this->states[this->source].isFinal = true;

    int count = 1;
    int s = this->sink;
    while (s != this->source) {
        this->states[s].isFinal = true;
        count++;
        s = this->states[s].suffixLink;
    }
    return count;
}
