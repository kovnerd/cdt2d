#include "Triangulation.h"
#include "TwoFourMove.h"
#include "TwoTwoMove.h"
#include "FourTwoMove.h"

//make Vertex and Triangle inherit Simplex

//pass Simplex to prepMoves
//make random simplex selection in other class

//FourTwo move XXX

//implement and debug move manager in MovesDebig
int main(void)
{
	long N = 18;
	long N_fix = 32;
	long TIME = 3;
	double K_2 = 0.72;
	Triangulation geom(N, TIME, N_fix, K_2);
	//std::cout << geom.toString() + "\n";
	/*	
	TwoTwoMove ttmove;
	ttmove.prepMove(7, geom);
	//std::cout << ttmove.toString() + "\n";	
	ttmove.doMove(geom);
	std::cout << ttmove.toString() + "\n";
	ttmove.prepMove(9, geom);
	//std::cout << ttmove.toString() + "\n";
	ttmove.doMove(geom);
	//std::cout << ttmove.toString() + "\n";
	ttmove.prepMove(8, geom);
	std::cout << ttmove.toString() + "\n";
	ttmove.doMove(geom);
	std::cout << ttmove.toString() + "\n";
	*/
	/*
	TwoFourMove tfmove;	
	tfmove.prepMove(7, geom);
	tfmove.doMove(geom);
	tfmove.prepMove(geom.vertex(7).nextVertex()->label, geom);
	tfmove.doMove(geom);
	std::cout << tfmove.toString() + "\n";	
	*/
	/*
	FourTwoMove ftmove;
	std::cout << "is (4,2) move possible? " + std::to_string(ftmove.isPossible(geom.vertex(7).nextVertex()->label, geom)) + "\n";
	ftmove.prepMove(geom.vertex(7).nextVertex()->label, geom);
	std::cout << ftmove.toString() + "\n";	
	ftmove.doMove(geom);
	//MEMORY LEAK WHEN TRYING TO PRINT ftmove.toString()
	std::cout << ftmove.toString() + "\n";	
	*/
	
	return 0;
}
