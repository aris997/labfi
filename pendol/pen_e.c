#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Rodari Riva
//begin 5th october 2017	- v.0.3.0

struct vector{
	double a;
	double va;
	double t;
};

struct vector cromer(struct vector, double, double);

double energy(struct vector, double);
double acceleration(struct vector, double, double, double, double, double);

int main() {

	int k;
	double omega2, gamma, f0, omegaf, dt, tmax, e, e0, phi;
	long int i, steps;
	char filename[20];

	struct vector state;

	FILE *input;
	FILE *output;

	input = fopen("input.dat", "r");
	printf("Cromer\n");

	for (k=0; k<1; k++) {

	  fscanf(input, "%lf %lf %lf %lf %lf %lf %lf %lf", &state.a, &state.va, &omega2, &dt, &tmax, &gamma, &f0, &omegaf);

	  e0 = energy(state, omega2);

	  steps = (long int)(tmax/dt);

	  sprintf(filename, "p_cromer%d.dat", k+1);
	  output = fopen(filename, "w");
	  
	  fprintf(output, "#t, \ta_i, \tva_i, \tE(t)/E0 - 1\n");
	  fprintf(output, "%lf %lf %lf %lf\n", 0., state.a, state.va, 0.);

	  for (i=0; i<steps; i++) {
	  	phi = acceleration(state, omega2, gamma, f0, omegaf, dt * (i+1));
	  	state = cromer(state, dt, phi);
	  	e = energy(state, omega2);
	  	fprintf(output, "%lf %lf %lf %lf\n", dt*(i+1), state.a, state.va, e/e0 - 1.);
	  }

}
	fclose(input);
	fclose(output);

	exit(0);
}

struct vector cromer(struct vector old, double dt, double phi) {
	
	struct vector new;
	
	new.va = old.va + phi * dt;
	new.a = old.a + new.va * dt;

	return new;
  
}

double energy(struct vector state, double omega2) {

  return 0.5 * state.va * state.va + omega2 * (1 - cos(state.a));
}

double acceleration(struct vector state, double omega2, double gamma, double f0, double omegaf, double t) {

  return - omega2 * sin(state.a) - gamma * state.va + f0 * cos(omegaf * t);
  
}