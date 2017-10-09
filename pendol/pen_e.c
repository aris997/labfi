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
struct vector copy(struct vector, double);


double acceleration(struct vector, double, double, double, double, double);
double period(struct vector, struct vector, double);
double energy(struct vector, double);


int main(int argc, char *argv[]) {

	int k;
	double omega2, gamma, f0, omegaf, dt, tmax, e, e0, phi, T;
	long int i, steps;
	char filename[20];

	struct vector state;
	struct vector last;

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
	  	last = copy(state, dt * (i+1));
	  	
	  	state = cromer(state, dt, phi);
	  	e = energy(state, omega2);
	  	
	  	fprintf(output, "%lf %lf %lf %lf", dt*(i+1), state.a, state.va, e/e0 - 1.);
	  	
	  	if ( last.a-state.a < 0 ) {
	  		T = period(last, state, dt);
	  		fprintf(output, " %lf", T);
	  	}
	  	fprintf(output, "\n");
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


double period(struct vector old, struct vector new, double dt) {

		return old.t + old.a * old.t * (old.a - new.a) / dt;
}


struct vector copy(struct vector state, double t) {
	
	struct vector new;

	new.a = state.a;
	new.va = state.va;
	new.t = t;

	return new;
}