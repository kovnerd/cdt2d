#ifndef movemanager_h
#define movemanager_h
#include "libraries.h"
#include "Scheduler.h"
#include "TwoFourMove.h"
#include "FourTwoMove.h"
#include "TwoTwoMove.h"
#include "Lattice.h"

class MoveManager
{
	protected:
		FourTwoMove fuse;
		TwoFourMove split;
		TwoTwoMove swap;
		Scheduler<long> schedule;
	public:
		MoveManager(Lattice& lat){schedule = Scheduler<long>(lat.getSchedule(TRIANGLE));}
		MoveManager(){schedule = Scheduler<long>();} 
		void prepMove();
};

#endif
