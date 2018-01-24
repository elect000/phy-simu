#include <stdio.h>
#include <stdlib.h>

#define MY_PI 3.14159

void set_values (int, int, double*, double*);
double hit_miss_test (int, double*, double*);

int main (void) {
  double *x;
  double *y;

  int t[3] = {100, 1000, 10000};
  int seed [10] = {149, 193, 251, 383, 457, 503, 691, 761, 829, 991};
  int i, j;
  double hits;
  for (i = 0; i < sizeof (t) / sizeof (t [0]); ++i) {
    hits = 0.0;
    x = (double*) malloc (sizeof (double) * t[i]);
    y = (double*) malloc (sizeof (double) * t[i]);

    if ((x == NULL) || (y == NULL)) {
      printf ("malloc error \n");
      exit (0);
    }

    for (j = 0; j < 10; ++j) {
      set_values(seed [j], t[i], x, y);
      hits += hit_miss_test (t [i], x, y);
    }
    hits = (hits / 10.0) * 4.0;
    printf ("%5d: %f : %f\n",
            t [i], hits, ((MY_PI - hits) / MY_PI));
  }
  free(x);
  free(y);
  return 0;
}

double hit_miss_test (int N, double* x, double* y) {
  int i;
  int hit = 0;
  for (i = 0; i < N; ++i) {
    if (1.0 >= ((x [i] * x [i]) + (y [i] * y [i]))) {
      hit++;
    }
  }
  return ((double) hit / N);
}

void set_values (int seed, int N, double *x, double *y) {
  srand(seed);
  int i;
  for (i = 0; i < N; ++i) {
    x[i] = -1.0 + (2.0 * rand() / (RAND_MAX + 1.0));
    y[i] = -1.0 + (2.0 * rand() / (RAND_MAX + 1.0));
  }
}

