#include <stdio.h>
#include <stdlib.h>

const int nm = 99;
const int M = 1;
const int G = 1;
const double H = 3.5;
const int ni = 50;
const double delta_t = 0.1;
const int seed = 449;
const int org = 50;
const double delta_x = 1;
const double delta_y = 1;

double X [500];
double Y [500];

double rho [500];
double phi [500][500];

double Fx[500][500];
double Fy[500][500];
double Fpx[500];
double Fpy[500];
double vx[500];
double vy[500];

void init_place();
int check(double, double);
void move_a ();
void calc_rho ();
void calc_phi ();
void calc_power_field ();
void calc_move ();
void calc_power ();
void calc_velocity ();
void calc_position ();
void move_b ();
void print_move ();

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

void init_phi () {
  for (int i = 0; i < 500; ++i) {
    for (int j = 0; j < 500; ++j) {
      phi[i][j] = 0;
    }
  }
}

void move_a () {
  for (int ip = 0; ip < 500; ++ip) {
    double vx_ip = H * X [ip];
    double vy_ip = H * Y [ip];

    X [ip] = X [ip] + org;
    Y [ip] = Y [ip] + org;

    X [ip] = X [ip] + vx_ip * delta_t;
    Y [ip] = Y [ip] + vy_ip * delta_t;
  }
}

void calc_rho () {
  for (int i = 0; i < 500; ++i) {
    rho [i] = 6 * X [i] - 3 * Y [i];
  }
}

void calc_phi () {
  // not yet
}

void calc_power_field () {
  for (int ix = 0; ix < 500; ++ix) {
    for (int iy = 0; iy < 500; ++iy) {
      Fx[ix][iy] = -(phi[ix + 1][iy] + phi[ix][iy]) / delta_x;
      Fx[ix][iy] = -(phi[ix][iy + 1] + phi[ix][iy]) / delta_y;
    }
  }
}

void calc_power () {
  // not yet
}

void calc_velocity () {
  // not yet
}

void calc_position () {
  for (int i = 0; i < 500; ++i) {
    X[i] = X[i] + vx[i] * delta_t;
    Y[i] = Y[i] + vy[i] * delta_t;
  }
}

void calc_move () {
  for (int ip = 1; ip <= 500; ip++) {
    calc_power ();
    calc_velocity ();
    calc_position ();
  }
}

void move_b () {
  calc_rho ();
  calc_phi ();
  calc_power_field ();
  calc_move ();
}

void print_move () {
  printf ("\n");
  for (int t = 0; t < 500; ++t) {
    printf ("%f,%f\n", X [t], Y [t]);
  }
}

int main (void) {
  init_place ();
  init_phi ();
  print_move ();
  for (int i = 0; i < 20; ++i) {
    move_a ();
  }
  print_move ();
  for (int i = 0; i < 20; ++i) {
    move_a ();
  }
  print_move ();
  return 0;
}

