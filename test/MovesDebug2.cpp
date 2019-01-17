#include "libraries.h"
#include "Lattice.h"
#include "TwoTwoMove.h"
#include "TwoFourMove.h"
#include "FourTwoMove.h"


int main(void)
{
	long N_2 = 18;
	long N_fix = 32;
	long TIME = 3;
	double K_2 = 0.71;
	Lattice lat(N_2, N_fix, TIME, K_2);
	std::cout << lat.toString() + "\n";
	long newVLabel = 99;
	std::pair<long, long> newT = std::make_pair(66, 77);
	std::vector<Triangle*> upt, downt;

	//swap move: WORKS
	//split move: WORKS
	//delete move: WORKS
	
	FourTwoMove ftmove(5, lat);
	std::cout << "BEFORE MOVE:\n" + ftmove.toString() + "\n";
	ftmove.makeMove(lat);
	std::cout << "AFTER MOVE:\n" + ftmove.toString() + "\n";
	

	return 0;
}
