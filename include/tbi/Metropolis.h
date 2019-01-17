#ifndef metropolis_h
#define metropolis_h
#include "libraries.h"
#include "MoveManager.h"

class Metropolis : public MoveManager
{
	private:
		std::unique_ptr<gsl_rng, void(*)(gsl_rng*)> r;
		void prepMove(int move, long label, Lattice& lat);
		double moveWeight(int move, Lattice& lat);//figure out probabilities...
		bool metroTest(int move, Lattice& lat);
		bool movePossible(int move, long label, Lattice& lat);
	public:
		double epsilon;
		long sweepSize;
		Metropolis(Lattice& latt, long sz) : MoveManager(latt), r(gsl_rng_alloc(gsl_rng_taus2), gsl_rng_free){gsl_rng_set(r.get(), (unsigned long)time(NULL)); sweepSize = sz; epsilon = 2e-5;}
		Metropolis(Lattice& latt) : Metropolis(latt, latt.N_2()){}
		Metropolis() : MoveManager(), r(gsl_rng_alloc(gsl_rng_taus2), gsl_rng_free){gsl_rng_set(r.get(), (unsigned long)time(NULL));}
		void step(Lattice& lat);
		void sweep(Lattice& lat);
		
		std::string toString();
};
#endif
