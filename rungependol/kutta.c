#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NINPUT 1

//RODARI RIVA
//12 ottobre 2017   -   v.0.1.1

typedef struct vector{
  double x; //x = Theta -> angolo
  double v; //v = omega -> vel angolare
} vector;


typedef struct par{
  double omega2;  //omega^2 
  double gamma;   //gamma
  double f0;
  double omegaf;
  double dt;      //tempo di integrazione
} par;

typedef long int counter;

struct vector verlet(vector, par, counter);
struct vector velocityverlet(vector, par);
struct vector RK2(vector, par, counter);
struct vector RK4(vector, par, counter);

double phi(double, double, par, double);
double energy(vector, par);

int main(){

  int j;
  counter i, steps;
  double x0, v0, tmax, e, e0;
  
  vector state;  //creo una struct per state(x,v) e var per parametri
  par var;

  FILE *input;
  FILE *output;
  // FILE *order;
  // FILE *poincare;
  // FILE *accumul;
  // FILE *biforc;
  
  char filename[20];

  input = fopen("input.dat", "r");

  for(j=0; j<NINPUT; j++){

    fscanf(input, "%lf %lf %lf %lf %lf %lf %lf %lf", &x0, &v0, &var.omega2, &var.gamma, &var.f0, &var.omegaf, &var.dt, &tmax);
    
    state.x = x0;
    state.v = v0;

    e0 = energy(state, var);

    steps = (long int)(tmax/var.dt);

    sprintf(filename, "data.dat");  //E' possibile resettare un char richiamandolo in una funzione sprintf
    output = fopen(filename, "w");

    fprintf(output, "%.14lf %.14lf %.14lf %.14lf\n", 0., state.x, state.v, 0.);

    for(i = 0; i<steps; i++){

      //state = verlet(state, var, i);
      //state = velocityverlet(state, var);
      //state = RK2(state, var, i);
      state = RK4(state, var, i);

      e = energy(state, var);

      fprintf(output, "%.14lf %.14lf %.14lf %.14lf\n", var.dt * (i + 1), state.x, state.v, e/e0 - 1.);
      
    }
    
    fclose(output);

  }

  fclose(input);
  exit(0);
}

struct vector verlet(vector old, par var, counter step) {

  //Usabile solo se l'accelerazione non dipende dalla velocita'

  struct vector new;
  static double nextx;
  
  if(step == 0){
    new.x = old.x + old.v * var.dt - 0.5 * var.omega2 * sin(old.x) * var.dt * var.dt; //x1
  }
  else {
    new.x = nextx;
  }

  nextx = 2. * new.x - old.x - var.omega2 * sin(old.x) * var.dt * var.dt; //x2  
  new.v = 0.5 * (nextx - old.x)/var.dt; //v1

  return new;

}

struct vector velocityverlet(vector old, par var) {

  struct vector new;

  new.x = old.x + old.v * var.dt - 0.5 * var.omega2 * sin(old.x) * var.dt * var.dt;
  new.v = old.v - 0.5 * var.omega2 * ( sin(old.x) + sin(new.x) ) * var.dt;

  return new;
}

struct vector RK2(vector old, par var, counter step) {

  struct vector new;
  double acc;
  acc = phi(old.x, old.v, var, (double)var.dt*step); //phi_n

  new.x = old.x + old.v * var.dt + 0.5 * acc * var.dt * var.dt;
  new.v = old.v + phi(old.x + 0.5 * old.v * var.dt, old.v + 0.5 * acc * var.dt, var, (double)var.dt*step + 0.5 * var.dt)*var.dt;
  
  return new;
}

struct vector RK4(vector n, par var, counter step) {

  double X[5], V[5]; //definisco array di 5 celle solo per avere una corrispondenza con la teoria
  double t dt;

  dt = var.dt;
  t = (double)var.dt*step;

  X[1] = n.v * dt;
  V[1] = phi(n.x, n.v, var, t) * dt;
  X[2] = (n.v + V[1]/2) * dt;
  V[2] = phi(n.x + X[1]/2, n.v + V[1]/2, var, t + dt/2) * dt;
  X[3] = (n.v + V[2]/2) * dt;
  V[3] = phi(n.x + X[2]/2, n.v + V[2]/2, var, t + dt/2) * dt;
  X[4] = (n.v + V[3]) * dt;
  V[4] = phi(n.x + X[3], n.v + V[3], var, t + dt) * dt;

  n.x += (X[1] + 2 * X[2] + 2 * X[3] + X[4])/6;
  n.v += (V[1] + 2 * V[2] + 2 ] V[3] + V[4])/6;
  
  return n;
}

double phi(double x, double v, par var, double t) {

  return -var.omega2 * sin(x) -var.gamma * v + var.f0 * cos(var.omegaf * t);
}

double energy(vector state, par var) {

  return 0.5 * state.v * state.v + var.omega2 * (1 - cos(state.x));
}
