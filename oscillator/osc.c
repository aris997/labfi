#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//RODARI RIVA
//28 settembre 2017   -   v.1.0.1


void eulero(double *x, double *v, double dt, double omega2);
void cromer(double *x, double *v, double dt, double omega2);
double energy(double x, double v, double omega2);

int main(int argc, char *argv[]){

  long int steps;
  int i, j, k;
  double x, v, omega2, dt, tmax, e, e0;

  char filename[50];
  
  FILE *input;
  FILE *output;

  sprintf(filename, "Kappa123");
  puts(filename);

  input = fopen("input.dat", "r");

  
  
  fclose(input);
  
  exit(0);
}


//Implementazione Algoritmi di Integrazione

void eulero(double *x, double *v, double dt, double omega2){    //Eulero
  
  double xnew, vnew;      //Definisco variabili temporali
  
  xnew = (*x) + (*v) * dt;
  vnew = (*v) - omega2*(*x)*dt;

  *x = xnew;            //Assegno tramite puntatori i nuovi valori
  *v = vnew;
  
  return;
}



void cromer(double *x, double *v, double dt, double omega2){    //Eulero-Cromer
  
  double xnew, vnew;    //Definisco variabili temporali
  
  vnew = (*v) - omega2*(*x)*dt;
  xnew = (*x) + vnew * dt;

  *x = xnew;            //Assegno tramite puntatori i nuovi valori
  *v = vnew;
  
  return;
}



double energy(double x, double v, double omega2) {            //Funzione Energia Meccanica

  return 0.5*v*v + 0.5*omega2*x*x;

}
