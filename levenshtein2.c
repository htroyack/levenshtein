#include <stdio.h>
#include <string.h>

#define EDIT "\e[34m"
#define DEL "\e[31m"
#define ADD "\e[97m"
#define UNDERLINE "\e[4m"
#define YELLOWBG "\e[43m"
#define DARKGRAYBG "\e[100m"
#define INVERTED "\e[7m"
#define BOLD DARKGRAYBG "\e[1m"
#define NORMAL "\e[0m"
#define MIN2(a,b) (((a)<=(b))?(a):(b))
// #define MIN2_(a,b) (((a)>(b))?(b):(a))
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

  printf("   ");
  for (int x=0; x<b_len; ++x)
    printf("%2c", b[x]);

  putchar('\n');
  for (int x=0; x<=a_len; ++x)
  {
    printf("%c", x==0?' ':a[x-1]);
    for (int y=0; y<=b_len; ++y)
    {
      if (x == 0) printf("%s", DEL);
      else if (y == 0) printf("%s", ADD);
      else if (matrix[x][y] == (matrix[x-1][y-1]+1)) printf("%s", EDIT);
      else if (matrix[x][y] == (matrix[x-1][y]+1)) printf("%s", ADD);
      else if (matrix[x][y] == (matrix[x][y-1]+1)) printf("%s", DEL);
      else printf("%s", BOLD);

      {
        if (x+1 <= a_len && y+1 <= b_len)
        {
          if ((matrix[x][y] < matrix[x+1][y]) && (matrix[x][y] < matrix[x][y+1]))
            printf("%s", BOLD);
        }
      }

      printf("%2d", matrix[x][y]);
      printf("%s", NORMAL);
    }
    putchar('\n');
  }

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
