#include <stdio.h>
#include <string.h>
#define MIN2(a,b) (((a)<=(b))?(a):(b))
#define MIN3(a,b,c) (MIN2((a),MIN2((b),(c))))

int levenshtein_distance(const char* a, size_t a_len, const char* b, size_t b_len) {
  int matrix[a_len+1][b_len + 1], i=0, j=0;
  for (i = 0; i < a_len+1; ++i)
    matrix[i][0] = i;
  for (j = 0; j < b_len+1; ++j)
    matrix[0][j] = j;

  for (i = 1; i <= a_len; ++i)
    for (j = 1; j <= b_len; ++j)
      matrix[i][j] = MIN3(matrix[i-1][j], matrix[i][j-1], matrix[i-1][j-1]) + (a[i-1] != b[j-1]);

  return matrix[a_len][b_len];
}

static inline int levenshtein(const char* a, const char* b) {
  return levenshtein_distance(a, strlen(a), b, strlen(b));
}

int main() {
  struct {const char* a; const char* b;} words[] = {
    {"casa", "cada"},
    {"cada", "cadaver"},
    {"cada", "caBdaver"},
    {"cadaver", "cada"},
    {"cabsa", "casa"},
    {"meilenstein", "levenshtein"},
    {"kitten", "sitting"},
    {"pairs", "cars"},
    {"car", ""},
    {"abcdef", "azced"},
    {"Saturday", "Sunday"},
    {"soylent green is people", "people soiled our green"},
    {"abc", "aZc"},
    {"abc", "abcz"},
    {"abcz", "abc"},
    {"k9st@", "kOrst"},
    {NULL, NULL}
  };
  int i = 0;
  while (words[i].a != NULL) {
    printf("%d:\tlevenshtein(\"%s\", \"%s\")\n",
      levenshtein(words[i].a, words[i].b),
      words[i].a, words[i].b);
    ++i;
  }
}
