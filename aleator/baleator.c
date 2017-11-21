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

  unsigned char m[64] = {0};
  for (i=0; i<64; i++) m[i]=1ULL;

  //number m = pow(2,64)-1;
  //number m = (number)(pow(2,64)-1);
  number a = 1181783497276652981ULL;

  double ran, r;

  double inv = 1./((double)m);
  printf("%.52lf \n", inv);
/*
  for (i=0; i<pow(10,6); i++){
    ran *= (double)a;
    r = (double)ran*inv;
    if (r<0.5) printf("0 ");
    else printf("1 ");
  }*/

  exit(0);
}

struct dim init(){
  dim a;
  a.x = 0;
  a.y = 0;
  return a;
}