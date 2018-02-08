#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

double rho [500] [500];
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
int find_point (double);
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
    X [ip] = X [ip] + vx[ip] * delta_t;
    Y [ip] = Y [ip] + vy[ip] * delta_t;
  }
}

void calc_rho () {
  for (int ix = 0; ix < 500; ++ix) {
    for (int iy = 0; iy < 500; ++iy) {
      rho [ix] [iy] = 6 * X [ix] - 3 * Y [iy];
    }
  }
}

void calc_phi () {
  double p1;
  double p2;
  for (int i = 1; i <= ni; ++i) {
    for (int ix = 1; ix <= nm; ++ix) {
      for (int iy = 1; iy <= nm; ++iy) {
        p1 = phi [ix + 1] [iy] + phi [ix - 1] [iy] + phi [ix] [iy + 1] + phi [ix] [iy - 1];
        p2 = G * rho [ix] [iy] * delta_x * delta_y;
        phi [ix] [iy] = p1 / 4.0 - p2 / 4.0;
      }
    }
  }
}

void calc_power_field () {
  for (int ix = 0; ix < 500; ++ix) {
    for (int iy = 0; iy < 500; ++iy) {
      Fx[ix][iy] = -(phi[ix + 1][iy] + phi[ix][iy]) / delta_x;
      Fx[ix][iy] = -(phi[ix][iy + 1] + phi[ix][iy]) / delta_y;
    }
  }
}

int find_point (double p) {
  float p_;
  if (modff (p, &p_) < 0.5) {
    return (int) p_;
  } else {
    return (int) (p_ + 1);
  }
}

void calc_power () {
  int x, y;
  for (int i = 0; i < 500; i++) {
    x = find_point (X [i]);
    y = find_point (Y [i]);
    Fpx [i] = M * Fx [x] [y];
    Fpy [y] = M * Fy [x] [y];
  }
}

void calc_velocity () {
  for (int ip = 0; ip < 500; ip++) {
    vx [ip] = vx [ip] + (Fpx [ip] / M) * delta_t;
    vy [ip] = vy [ip] + (Fpy [ip] / M) * delta_t;
  }
}

void calc_position () {
  for (int i = 0; i < 500; ++i) {
    X[i] = X[i] + vx[i] * delta_t;
    Y[i] = Y[i] + vy[i] * delta_t;
  }
}

void calc_move () {
  calc_power ();
  calc_velocity ();
  calc_position ();
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

  for (int ip = 0; ip < 500; ++ip) {
    vx[ip] = H * X [ip];
    vy[ip] = H * Y [ip];

    X [ip] = X [ip] + org;
    Y [ip] = Y [ip] + org;
  }

  print_move ();
  init_phi ();

  for (int i = 0; i < 20; ++i) {
    move_b ();
  }

  print_move ();
 
  for (int i = 0; i < 20; ++i) {
    move_b ();
  }
 
  print_move ();
  return 0;
}

