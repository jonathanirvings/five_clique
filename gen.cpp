#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<string> word_to_str(1 << 26);
  vector<vector<int>> words_with_hsb(26);

  {
    ifstream words_alpha;
    words_alpha.open("words_alpha.txt");
    string s;
    int res = 0;
    while (words_alpha >> s) {
      if (s.size() == 5) {
        int word = 0;
        for (char c : s) {
          word |= (1 << (c - 'a'));
        }
        if (__builtin_popcount(word) == 5 && word_to_str[word] == "") {
          word_to_str[word] = s;
          int hsb = 0;
          for (int i = 25; i >= 0; --i) {
            if (word & (1 << i)) {
              hsb = i;
              break;
            }
          }
          words_with_hsb[hsb].push_back(word);
        }
      }
    }
  }
  vector<int> possibilities(1 << 26);
  vector<vector<int>> can_use_word(1<<26);
  possibilities[0] = 1;
  vector<int> hsb(1 << 26);
  for (int bit = 1; bit < (1 << 26); ++bit) {
    for (int i = 25; i >= 0; --i) {
      if (bit & (1 << i)) {
        hsb[bit] = i;
        break;
      }
    }
  }
  for (int bit = 0; bit < (1 << 26); ++bit) {
    if (possibilities[bit] > 0) {
      for (int i = (bit == 0 ? -1 : hsb[bit]) + 1; i < 26; ++i) {
        for (int word : words_with_hsb[i]) {
          if ((word & bit) == 0) {
            possibilities[word | bit] += possibilities[bit];
            can_use_word[word | bit].push_back(word);
          }
        }
      }
    }
  }

  vector<int> words;
  function<void(int)> dfs = [&] (int bit) {
    if (bit == 0) {
      for (int word : words) {
        printf("%s ", word_to_str[word].c_str());
      }
      puts("");
      return;
    }
    for (int word : can_use_word[bit]) {
      words.push_back(word);
      dfs(bit ^ word);
      words.pop_back();
    }
  };

  int total_possibilities = 0;
  for (int i = 0; i < 26; ++i) {
    total_possibilities += possibilities[((1 << 26) - 1) ^ (1 << i)];
  }
  for (int i = 0; i < 26; ++i) {
    dfs(((1 << 26) - 1) ^ (1 << i));
  }
  printf("TOTAL NUMBER OF SETS (ANAGRAM EXCLUDED) = %d\n", total_possibilities);
}
