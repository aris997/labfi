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
  number m = 2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2ULL;
  //number m = (number)(pow(2,64)-1);
  number a = 1181783497276652981ULL;

  printf("m:%lld \na:%lld\n", m, a);


  exit(0);
}

struct dim init(){
  dim a;
  a.x = 0;
  a.y = 0;
  return a;
}