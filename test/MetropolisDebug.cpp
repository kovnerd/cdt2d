#include "Lattice.h"
#include "Metropolis.h"

int main(void)
{
	long N_2 = 4096;
	long N_fix = N_2;
	long TIME = 32;
	double K_2 = 0.71;
	long sweepSize= 1000;
	Lattice lat(N_2, N_fix, TIME, K_2);
	Metropolis met(lat, sweepSize);	
	
	int num_sweeps = 10;
	int num_print = num_sweeps/10;
	double testVal = 0.;
	std::cout << "K_2 = " + std::to_string(K_2) + "\n";
	met.epsilon = 0;
	for(int i = 1; i <= num_sweeps; i++)
	{
		met.sweep(lat);
		if(i%num_print == 0)	
			std::cout << "config " + std::to_string(i) + ": N_2 =  " + std::to_string(lat.N_2()) + "\n";
	} 
	std::cout << "N_f/N_i = " + std::to_string((double)lat.N_2()/N_2) + "\n";
	std::cout << met.toString() + "\n";



	return 0;
}
