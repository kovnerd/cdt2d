#include "libraries.h"
#include "Lattice.h"
#include "Metropolis.h"
#include "Observable.h"
#include "Simulation.h"


int main(void)
{
	//move to bash file
	long N_2 = 4096;
	long N_fix = N_2;
	long TIME = 32;
	double kmin = 0.570;
	long sweepSize = N_2;
	long ensembleSize = 1e4;
	int corSteps = 2;
	long thermSteps = ensembleSize/10; 
	double kmax = 0.586;
	int num_points = 50;
	double kstep = (kmax - kmin)/num_points;
	
	
	
	int bar_width = 70;
	double progress = 0.;

	Simulation sim(ensembleSize, corSteps, sweepSize, N_2, N_fix, TIME, kmin);
	
	std::string relPath = "../data_files/";
	Lattice lat(N_2, N_fix, TIME, kmin);
	Metropolis met(lat, sweepSize);	
	std::string ratioName = "avNOverN_i";
	std::string flucName = "avdeltaNOverN";
	//std::string ratioFullName = relPath + ratioName + "_" + std::to_string(N_2) + ".txt";
	//std::string flucFullName = relPath + flucName + "_" + std::to_string(N_2) + ".txt";
	std::string ratioFullName = relPath + ratioName + "_" + "PROBTEST" + ".txt";
	std::string flucFullName = relPath + flucName + "_" + "PROBTEST" + ".txt";
	
	Observable ratio;
	Observable avN;
	Observable avNN;
	DataManager data;
	data.open(ratioFullName, std::ofstream::out | std::ofstream::app);
	data.open(flucFullName, std::ofstream::out | std::ofstream::app);
	///*
	for(double k = kmin; k < kmax; k += kstep)
	{
		lat = Lattice(N_2, N_fix, TIME, k);
		met =  Metropolis(lat, sweepSize);
		met.epsilon = 0;
		ratio = Observable();
		avN = Observable();
		avNN = Observable();
		progress = 0;
		printf("Thermalizing...\n");
		for(int t = 1; t <= thermSteps; t++)
		{
			met.sweep(lat);
			progress = sim.update_progress(progress, 1./(thermSteps-1.), bar_width);
		}
		printf("\nThermalization Complete!\nGenerating ensemble...\n");
		progress = 0;
		for(int n = 1; n <= ensembleSize; n++)
		{
			for(int nc = 1; nc <= corSteps; nc++)
				met.sweep(lat);
			progress = sim.update_progress(progress, 1./(ensembleSize-1.), bar_width);
			ratio.record(1.*lat.N_2()/N_2);
			avN.record(lat.N_2());
			avNN.record(lat.N_2()*lat.N_2());
		}
		double aveN = avN.report(); 
		double aveNN = avNN.report();
		printf(("\nK_2 = " + std::to_string(k) + ", " + ratioName + " = " + std::to_string(aveN/N_2) + "\n").c_str());
		printf(("\nK_2 = " + std::to_string(k) + ", " + flucName + " = " + std::to_string(sqrt(aveNN - aveN*aveN)/aveN) + "\n").c_str());
		data.file(ratioFullName) << std::to_string(k) + " " +  " " + std::to_string(ratio.back()) + "\n";
		data.file(flucFullName) <<  std::to_string(k) + " " + " " + std::to_string(sqrt(aveNN - aveN*aveN)/aveN) + "\n";
	}
	//*/

	return 0;
}
