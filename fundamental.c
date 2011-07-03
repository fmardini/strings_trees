#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

void fundamental(char *t, int len, int **z) {
  int r = 0, l = 0, j = 0;
  *z = malloc(sizeof(int) * len);
  (*z)[0] = 0;
  for (int k = 1; k < len; k++) {
    if (k > r) {
      for (j = 0; j + k < len && t[j] == t[k + j]; j++);
      if (j > 0) {
        l = k;
        r = k + j - 1;
      }
      (*z)[k] = j;
    } else {
      int beta = r - k + 1;
      int zk = (*z)[k - l];
      if (zk < beta) {
        (*z)[k] = zk;
      } else {
        for (j = 0; r + j + 1 < len && t[r + 1 + j] == t[beta + j]; j++);
        (*z)[k] = r + j - k + 1;
        l = k;
        r = r + j;
      }
    }
  }
}

void random_fill(char *s, int len) {
  int blen = len / 2 + 1;
  char *buf = malloc(blen);
  int fd = open("/dev/urandom", O_RDONLY);
  read(fd, buf, blen);
  char masks[] = { 0x07, 0x38 };
  for (int i = 0; i < len; i++) {
    char rnd = (buf[i / 2] & masks[i & 0x01]) >> (i & 0x01 ? 3 : 0);
    s[i] = 'a' + rnd;
  }
}

void inspect(int *l, int len) {
  for (int i = 0; i < len; i++)
    printf(i == len - 1 ? "%d\n" : "%d, ", l[i]);
}
void inspect_c(char *l, int len) {
  for (int i = 0; i < len; i++)
    printf(i == len - 1 ? "%c\n" : "%c, ", l[i]);
}

int main(int argc, char **argv) {
  int len = 10;
  if (argc > 1)
    len = atoi(argv[1]);
  if (len < 10) len = 10;
  char *t = malloc(len + 1);
  if (len == 10)
    memcpy(t, "aabaaabcaab", 10);
  else
    random_fill(t, len);
  t[len] = '\0';
  int *z;

  fundamental(t, len, &z);
  inspect(z, len);
  inspect_c(t, len);
  free(z);

  return 0;
}
