#include <stdio.h>

double rho_func(int, int);
void init_phi();
void init_rho();
void gaus_xaiel(int);
void print_phi();

#define G  1.0
const int ni = 200;
const int nm = 2;
const double delta_x = 1;
const double delta_y = 1;
double phi[4][4];
double rho[4][4];

double rho_func(int x, int y) {
  return (6 * x) - (3 * y);
}

void init_phi () {
  for (int t = 0; t < 4 ; t++) {
    phi[t][0] = 0.0;
    phi[0][t] = 0.0;
  }
  phi[1][3] = 22.5;
  phi[2][3] = 36.0;
  phi[3][1] = -4.5;
  phi[3][2] = 9.0;
}

void init_rho () {
  for (int ix = 0; ix < 4; ix++) {
    for(int iy = 0; iy < 4; iy++) {
      rho[ix][iy] = rho_func(ix, iy);
    }
  }
}

void gaus_xaiel (int nm) {
  double p1;
  double p2;
  for (int i = 1; i <= ni; i++) {
    for (int ix = 1; ix <= nm; ix++) {
      for (int iy = 1; iy <= nm; iy++) {
        p1 = phi[ix+1][iy] + phi[ix-1][iy] + phi[ix][iy+1] + phi[ix][iy-1];
        p2 = G * rho[ix][iy] * delta_x * delta_y;
        phi[ix][iy] = p1 / 4.0 - p2 / 4.0;
      }
    }
  }
}

void print_phi(){
  for (int iy = 3; iy > -1; iy--) {
    for (int ix = 0; ix < 4; ix++) {
      printf("%f ",phi[ix][iy]);
    }
    printf("\n");
  }
}
int main (void) {
  init_phi();
  init_rho();
  gaus_xaiel(nm);
  print_phi();
  return 0;
}
