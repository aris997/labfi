#include <limits.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define NSTORIES 100
#define NSTEPS 100
#define NBIN 10

typedef unsigned long long int number;
typedef long long int pos;

typedef struct dim{
  int x;
  int y;
} dim;


int main () {
  register int i;

  number m = (1<<(8*sizeof(number)))-1;
  number a = 1181783497276652981ULL;

  number ran = time(NULL);
  double r;
  double inv = 1./(double)m;

  number mem;

  //printf("%llu %ld %.52lf\n", m, 8*sizeof(number), inv);
  //printf("%.52lf\n", inv);

  for (i=0; i<pow(10,POW); i++){
    ran = (a*ran)%m;
    r = (double)ran*inv;
    if (r<0.5) mem++;
  }

  double M = mem/pow(10,POW);
  printf("media %lf\n", M);

  exit(0);
}

struct dim init(){
  dim a;
  a.x = 0;
  a.y = 0;
  return a;
}