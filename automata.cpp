#include "automata.h"

// TODO: check if final states are correct.

State::State() {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        this->next[i] = nullptr;
    }
    this->suffixLink = nullptr;
    this->isFinal = false;
}

// TODO: retrieve state in linear time.
int State::getTransition(State* state) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (this->next[i]->state == state) {
            return i;
        }
    }
    return -1;
}

SuffixAutomata::SuffixAutomata() {
    this->source = new State;
    this->statesCount = 1;

    this->transitionsCount = 0;

    this->sink = this->source;
}

void SuffixAutomata::add(char letter) {
    this->sink = this->update(this->sink, letter);
}

State* SuffixAutomata::update(State* currentSink, char letter) {
    int index = letter - FIRST_SYMBOL;

    currentSink->isFinal = false;

    State* newSink = new State;
    newSink->isFinal = true;
    this->statesCount++;

    Transition* primaryTransition = new Transition(newSink, true);
    currentSink->next[index] = primaryTransition;
    this->transitionsCount++;

    State* current = currentSink;
    State* suffixState = nullptr;

    while (current != this->source && suffixState == nullptr) {
        current = current->suffixLink;
        if (current->next[index] == nullptr) {
            Transition* secondaryTransition = new Transition(newSink);
            this->transitionsCount++;
            current->next[index] = secondaryTransition;
        } else if (current->next[index]->primary) {
            suffixState = current->next[index]->state;
        } else {
            State* childState = current->next[index]->state;
            suffixState = this->split(current, childState, index);
        }
    }

    if (suffixState == nullptr) suffixState = this->source;

    newSink->suffixLink = suffixState;
    return newSink;
}

State* SuffixAutomata::split(State* parent, State* child, int a) {
    State* newChildState = new State;
    this->statesCount++;

    parent->next[a]->state = newChildState;
    parent->next[a]->primary = true;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (child->next[i] != nullptr) {
            Transition* t = new Transition(child->next[i]->state);
            newChildState->next[i] = t;
            this->transitionsCount++;
        }
    }

    newChildState->suffixLink = child->suffixLink;
    child->suffixLink = newChildState;

    State* current = parent;
    while (current != this->source) {
        current = current->suffixLink;
        int a = current->getTransition(child);
        if (a > 0 && !current->next[a]->primary) {
            current->next[a]->state = newChildState;
        } else {
            break;
        }
    }
    return newChildState;
}

int SuffixAutomata::setFinalStates() {
    int count = 0;
    State* s = this->sink;
    while (s != this->source) {
        s->isFinal = true;
        count++;
        s = s->suffixLink;
    }
    return count;
}
