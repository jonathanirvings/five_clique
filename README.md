# Five Clique

Copyright (C) 2022 - Jonathan Irvin Gunawan

A solution to the problem of finding five English words with 25 distinct characters, using dynamic programming with bitmask.

## Description

The problem is inspired by the wonderful [A problem squared podcast](https://aproblemsquared.libsyn.com/) by Hill and Parker, and has been previously attempted by
Matt Parker, Benjamin Paasen and Scott Mansell.
While Matt's solution run for a long period of time, [Benjamin's solution](https://gitlab.com/bpaassen/five_clique) and [Scott's solution](https://github.com/phire/five_clique) have been running much faster.
In [their tweet](https://twitter.com/phirenz/status/1555072727534694400), Benjamin claimed that Scott's and Benjamin's solution run for 19.5 minutes and 36 seconds respectively.
The author attempted to find a better solution that runs in approximately 3 seconds.

For simplicity, let us first assume that there are 25 letters in the alphabet.
Once we can solve this task quickly, we can solve the main task by trying 26 possibilities, each trying a letter which we do not use.

Instead of attempting this problem as a graph problem, we attempt this problem using dynamic programming with bitmask operations.
First, for each 5-letter word without duplicate letters, we convert them to 25-bit integer.
The i-th bit is active if and only if the i-th letter (e.g., ASCII code 97 + i) is present in the word.
For any integer v, we define cnt(v) as the number of 1's in its binary representation.
For any v (0 &le; v &le; 2^25) where cnt(v) is a multiple of 5, we define C(v) as the number of distinct set of cnt(v) / 5 words without using the same letter twice, and letter i can be used if and only if the i-th bit of v is 1.
By definition, cnt(0) = 1.

For v > 0, we can compute cnt(v) recursively as follows:

cnt(v) = sum(cnt(v - w) | w is a word and w is a submask of v).

However, doing this will count duplicates.
Suppose "abcde" and "fghij" are both words.
When computing cnt(2^10 - 1), we will compute both {"abcde", "fghij"} and {"fghij", "abcde"}.
The solution to remove the duplicates is by changing the recursion to the following optimization, which also saves runtime.

cnt(v) = sum(cnt(v - w) | w is a word and w is a submask of v and hsb(w) = hsb(v)), where hsb(v) is the index of the highest significant bit in v, i.e. hsb(v) = floor(log2(v)).

To actually construct the solution (instead of just counting them), for each v, we need to keep the list of words w which contributes to the value of cnt(v), and then uses backtrack.

This is the basic idea of the solution.
There are several other optimizations being done to improve the runtime of the solution, but they are not algorithmic.


## Result

Using a Macbook Air (M1, 2020), the solution was ran 10 times, with the runtime average of 3.1803 seconds and variance of 0.07848361 seconds.
The solution finds 538 sets of 5 words (anagram excluded) without using the same letter twice, which agrees with Matt's solution.


## Quickstart guide

To reproduce my calculation, please execute the following steps:

1. Download the `words_alpha.txt` file from https://github.com/dwyl/english-words (this is the same file that Parker used), or just use the file in the repository.
2. Compile `gen.cpp` file, using the following command: `g++ -O2 -o gen gen.cpp -std=c++17`
3. Run the executable and time it: `time ./gen`
4. The sets of 5 words without using the same letter twice (anagram excluded) is printed to the standard output. The last line will also print the number of such sets.
