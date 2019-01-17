#ifndef move_h
#define move_h
#include "libraries.h"
#include "Simplex.h"

class Move
{
	public:
		bool moveDone = false;
		std::string name;
		unsigned int accepts;
		unsigned int rejects;
		Move(){accepts = rejects = 0;}
		
		virtual void prepMove(Simplex* s, Triangulation& geom) = 0;
		virtual bool isPossible(long index, Triangulation& geom) = 0;
		virtual double acceptProb(Triangulation& geom) = 0;
		virtual void doMove(Triangulation& geom) = 0;
		
		unsigned int attempts(){return accepts + rejects;}

		virtual std::string toString() = 0;
};
#endif
