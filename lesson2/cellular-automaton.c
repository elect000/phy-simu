#include <stdio.h>
#include <stdlib.h>

// 111, 101, 100, 011 -> 1 : others -> 0
static int rules[4] = {111, 101, 100, 11};

int check (int);
void celluar_automaton (int, int*, int*);
void generate_vector (float, int, int*);
void shuffle (int, int*);
void print_vector (int, int, int*);
void move_vector (int, int*, int*);

int main (void) {
  int i, j;
  float density[3] = {0.3, 0.5, 0.7};
  int size = 20;
  int prev[size];
  int next[size];
  for (i = 0; i < 3; ++i) {
    printf ("density: %.1f\n", density [i]);
    generate_vector(density[i], size, prev);
    print_vector(0, size,  prev);
    for (j = 1; j < 21; ++j) {
      celluar_automaton(size, prev, next);
      print_vector(j, size, next);
      move_vector(size, prev, next);
    }
    printf ("\n");
  }
  return 0;
}

int check (int k) {
  int i;
  for (i = 0; i < (sizeof (rules)/ sizeof (rules [0])); ++i) {
    if (k == rules [i]) {
      return 1;
    }
  }
  return 0;
}

void celluar_automaton (int size, int* prev, int* next) {
  int i, k;
  // i = 0
  k = prev [size - 1] * 100 + prev [0] * 10 + prev [0 + 1] * 1;
  next [0] = check (k);
  // i = 1 ... (size - 1) - 1
  for (i = 1; i < (size - 1); ++i) {
    k = prev [i - 1] * 100 + prev [i] * 10 + prev [i + 1] * 1;
    next [i] = check (k);
  }
  // i = size - 1
  k = prev [(size - 1) - 1] * 100 + prev [size - 1] * 10 + prev [0] * 1;
  next [i] = check (k);
}

void generate_vector (float density, int size, int* vec) {
  int i;
  int l = (int) (density * size);
  for (i = 0; i < size; ++i) {
    if (i < l) {
      vec [i] = 1;
    } else {
      vec [i] = 0;
    }
  }
  shuffle (size, vec);
}

void shuffle (int size, int* vec) {
  int i;
  srand (691);
  for (i = 0; i < size; ++i) {
    int j = (int) (10 * (rand () / (RAND_MAX + 1.0)));
    int t = vec [i];
    vec [i] = vec [j];
    vec [j] = t;
  }
}

void print_vector (int n, int size, int* vec) {
  int i;
  printf ("t = %2d:", n);
  for (i = 0; i < size; ++i) {
    printf (" %d", vec [i]);
  }
  printf ("\n");
}

void move_vector (int size, int* prev, int* next) {
  int i;
  for (i = 0; i < size; ++i) {
    prev [i] = next [i];
  }
}
