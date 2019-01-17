#include "Simulation.h"

//fix rel_path

double Simulation::update_progress(double progress, double progress_rate, int bar_width)
{
		int pos = progress * bar_width;
		std::cout << "[";
		for(int b = 0; b < bar_width; b++)
		{
			if(b <= pos)
				std::cout << "=";
			else
				std::cout << " ";
		}
		std::cout << "]" << std::setprecision(1) << std::fixed << progress * 100  << "%\r";
		std::cout.flush();

		return progress + progress_rate;
}

void Simulation::start()
{
	double progress = 0;
	int bar_width = 70;
	long N_2i = lat.N_2();
	long thermSteps = N_conf/10;
	std::string ratio = "N_f/N_i";
	obs[ratio] = Observable();
	//std::string avN_2 = "<N_2>";
	//obs[avN_2] = Observable();
	//std::string avN_2Squared = "<N_2^2>";
	//obs[avN_2Squared] = Observable();
	//std::string avFluct = "<deltaN_2/N_2>";
	std::string ratiofullName = relPath + ratio + "_test" + ".txt";	
	data.open(ratiofullName, std::ofstream::out | std::ofstream::app);
	std::cout << "Thermalizing...\n";
	for(int t = 1; t <= thermSteps; t++)
	{
		progress = update_progress(progress, 1./(thermSteps-1.), bar_width);
		met.sweep(lat);
	}
	std::cout << "\nThermalization Complete!\nGenerating ensemble...\n";
	progress = 0;
	for(int n = 1; n <= N_conf; n++)
	{
		for(int nc = 1; nc <= N_cor; nc++)
			met.sweep(lat);
		progress = update_progress(progress, 1./(N_conf-1.), bar_width);
		obs.at(ratio).record(1.*lat.N_2()/N_2i);
		//obs.at(avN_2).record(1.*lat.N_2());
		//obs.at(avN_2Squared).record(1.*lat.N_2()*lat.N_2());
	}
	data.file(ratiofullName) << "\nK_2 = " + std::to_string(lat.K_2()) + " " + ratio + " = " + std::to_string(obs.at(ratio).back()) + "\n";
	std::cout << met.toString() + "\n";
}
