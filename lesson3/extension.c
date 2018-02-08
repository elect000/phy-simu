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
int check (double, double);
void move ();
void print_move ();

double vx[500];
double vy[500];


void init_v () {
  for (int i = 0; i < 500; ++i) {
    vx[i] = H * X [i];
    vy[i] = H * Y [i];
  }
}

int check (double x, double y) {
  if ((x * x + y * y) > 25.0) {
    return 0;
  } else {
    return 1;
  }
}

void init_place () {
  double x, y;
  srand(seed);
  for (int t = 0; t < 500; ++t) {
    x = -5.0 + (double) (10.0 * rand()/RAND_MAX);
    y = -5.0 + (double) (10.0 * rand()/RAND_MAX);
    while (0 == check (x, y)) {
      x = -5.0 + (double) (10.0 * rand()/RAND_MAX);
      y = -5.0 + (double) (10.0 * rand()/RAND_MAX);
    }
    X [t] = x;
    Y [t] = y;
  }
}


void move () {
  for (int ip = 0; ip < 500; ++ip) {

    X [ip] = X [ip] + vx[ip] * delta_t;
    Y [ip] = Y [ip] + vy[ip] * delta_t;
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
  init_v ();
  for (int ip = 0; ip < 500; ++ip) {
    X [ip] = X [ip] + org;
    Y [ip] = Y [ip] + org;
  }
  print_move ();
  for (int i = 0; i < nk; ++i) {
    move ();
  }
  print_move ();
  return 0;
}
 
