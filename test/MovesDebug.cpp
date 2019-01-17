#include "libraries.h"
#include "Triangulation.h"
#include "MoveManager.h"
//#include "Metropolis.h"

//make metropolis class to do carry out metropolis steps
//remember
//	pick and record O(4) vertices
//	try interleaving (2,2)'s, (2,4)'s with "suitable frequency"

int main(void)
{
	long N_2 = 18;
	long N_fix = 32;
	long TIME = 3;
	double K_2 = 0.71;
	
	Triangulation geom(N_2, TIME, N_fix, K_2);
	
	MoveManager moves;
	
	
	

	return 0;
}
