#include <stdio.h>
#include <stdlib.h>

void result_to_csv (int, double*, double*);
void set_correct_values (int, double*, double*);
int check (double, double);

int main (void) {
  int N = 500;
  double x [N];
  double y [N];

  set_correct_values(N, x, y);
  result_to_csv(N, x, y);
  return 0;
}

void set_correct_values (int N, double* x, double* y) {
  srand(691);
  int i, j;
  double x_, y_;
  for (i = 0; i < N; ++i) {
    x[i] = x_ =  -1.0 + (2.0 * rand() / (RAND_MAX + 1.0));
    y_ = -                     1.0 + (2.0 * rand() / (RAND_MAX + 1.0));
    while (check (x_, y_)) {
      y_ = -1.0 + (2.0 * rand() / (RAND_MAX + 1.0));
    }
    y [i] = y_;
  }
}

int check (double x, double y) {
   if (1.0 >= ((x * x) + (y * y))) {
     return 0;
   }
  return 1;
}

void result_to_csv (int N, double* x, double* y) {
  FILE *fo;
  int i;
  char* fname = "data.csv";
  if ((fo = fopen(fname, "w")) == NULL) {
    printf ("File[%s] does not open!! \n", fname);
    exit (0);
  }
  for (i = 0; i < N; ++i) {
    fprintf (fo, "%f, %f\n", x [i], y [i]);
  }
}
