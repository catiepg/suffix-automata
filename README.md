# Suffix Automata

Construct a minimum acyclic deterministic suffix automaton.

## Implementation

The suffix automaton is constructed using the algorithm described in
[The smallest automation recognizing the subwords of a text](https://ac.els-cdn.com/0304397585901574/1-s2.0-0304397585901574-main.pdf?_tid=1e6951fe-dfc0-44cd-a0e0-7606d2c275ca&acdnat=1551550753_91433383b2eef243ac6ef28dd42d36bf) by Blumer et al.

The input is a word *w* in Σ\*. The size of the constructed automaton
is *O(|w|)* and the construction time is *O(|w|)*.

## Usage
```sh
$ ./main.out word.txt
```

`word.txt` contains the input word. Each symbol in the file must be one
byte in size and an integer from Σ = {i ∈ Z | 97 ≤ i ≤ 122}.
