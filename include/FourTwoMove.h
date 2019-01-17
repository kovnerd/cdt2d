#ifndef fourtwo_h
#define fourtwo_h
#include "libraries.h"
#include "Triangulation.h"
#include "Move.h"

class FourTwoMove : public Move
{
	private:
		Vertex* upperV;
		std::deque<Vertex*> sameV;
		Vertex* lowerV;
		std::deque<Triangle*> upperT;
		std::deque<Triangle*> lowerT;
	public:
		std::string name = "FourTwo";
		FourTwoMove(){moveDone = false; sameV.resize(3);upperT.resize(3);lowerT.resize(3);}
		void prepMove(long label, Triangulation& geom) override;
		bool isPossible(long label, Triangulation& geom) override;
		double acceptProb(Triangulation& geom) override;
		void doMove(Triangulation& geom) override;
		std::string toString();
};

#endif
