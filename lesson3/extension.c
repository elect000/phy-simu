#include <stdio.h>
#include <stdlib.h>

const double H = 3.5;
const int org = 50;
const double delta_t = 0.1;
const int nk = 20;
const int seed = 449;
double X [500];
double Y [500];

void init_place();
int check (int, int);
void move ();
void print_move ();

int check (int x, int y) {
  if (x * x + y * y <= 5 * 5) {
    return 1;
  }
  return 0;
}

void init_place () {
  double x, y;
  srand(seed);
  for (int t = 0; t < 500; ++t) {
    x = -5.0 + (double) (10.0 * rand()/RAND_MAX);
    y = -5.0 + (double) (10.0 * rand()/RAND_MAX);
    while (check (x, y)) {
      x = -5.0 + (double) (10.0 * rand()/RAND_MAX);
      y = -5.0 + (double) (10.0 * rand()/RAND_MAX);
    }
    X [t] = x;
    Y [t] = y;
  }
}

void move () {
  for (int ip = 0; ip < 500; ++ip) {
    double vx_ip = H * X [ip];
    double vy_ip = H * Y [ip];

    X [ip] = X [ip] + org;
    Y [ip] = Y [ip] + org;

    X [ip] = X [ip] + vx_ip * delta_t;
    Y [ip] = Y [ip] + vy_ip * delta_t;
  }
}

void print_move () {
  printf ("\n");
  for (int t = 0; t < 500; ++t) {
    printf ("%f,%f\n", X [t], Y [t]);
  }
}

int main (void) {
  init_place ();
  for (int i = 0; i < nk; ++i) {
    print_move ();
    move ();
  }
  return 0;
}
