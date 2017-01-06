#include "automata.h"

State::State() {
    this->suffixLink = NONE;
    this->isFinal = false;
}

SuffixAutomata::SuffixAutomata() {
    this->source = 0;
    this->states.emplace_back();
    this->sink = this->source;
}

void SuffixAutomata::add(char letter) {
    this->sink = this->update(this->sink, letter);
}

int SuffixAutomata::update(int currentSink, char letter) {
    int symbol = letter - FIRST_SYMBOL;

    int newSink = this->states.size();
    this->states.emplace_back();

    this->transitions.emplace_back(newSink, true);
    this->states[currentSink].next[symbol] = this->transitions.size() - 1;

    int current = currentSink;
    int suffix = NONE;

    while (current != this->source && suffix == NONE) {
        current = this->states[current].suffixLink;
        State currentState = this->states[current];
        // ???
        if (currentState.next.find(symbol) == currentState.next.end()) {
            this->transitions.emplace_back(newSink, false);
            this->states[current].next[symbol] = this->transitions.size() - 1;
        } else if (this->transitions[currentState.next[symbol]].primary) {
            suffix = this->transitions[currentState.next[symbol]].state;
        } else {
            int child = this->transitions[currentState.next[symbol]].state;
            suffix = this->split(current, child, symbol);
        }
    }

    if (suffix == NONE) suffix = this->source;

    this->states[newSink].suffixLink = suffix;
    return newSink;
}

int SuffixAutomata::split(int parent, int child, int symbol) {
    int newChild = this->states.size();
    this->states.emplace_back();

    int t = this->states[parent].next[symbol];
    this->transitions[t].state = newChild;
    this->transitions[t].primary = true;

    for (auto it : this->states[child].next) {
        this->transitions.emplace_back(this->transitions[it.second].state, false);
        this->states[newChild].next[it.first] = this->transitions.size() - 1;
    }

    this->states[newChild].suffixLink = this->states[child].suffixLink;
    this->states[child].suffixLink = newChild;

    int current = parent;
    while (current != this->source) {
        current = this->states[current].suffixLink;
        char a = this->getTransition(current, child);
        int t = this->states[current].next[a];
        if (a > 0 && !this->transitions[t].primary) {
            this->transitions[t].state = newChild;
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

// TODO: retrieve state in linear time.
char SuffixAutomata::getTransition(int from, int to) {
    for (auto it : this->states[from].next) {
        if (this->transitions[it.second].state == to) {
            return it.first;
        }
    }
    return -1;
}
