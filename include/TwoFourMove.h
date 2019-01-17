#ifndef twofour_h
#define twofour_h
#include "libraries.h"
#include "Triangulation.h"
#include "Move.h"

class TwoFourMove : public Move
{
	//replace individual variables with lists...?
	private:
		std::deque<Vertex*> sameV;
		Vertex* upperV;
		Vertex* lowerV;
		std::deque<Triangle*> upperT;
		std::deque<Triangle*> lowerT;
	public:
		std::string name = "TwoFour";
		TwoFourMove(){sameV.resize(3); upperT.resize(3); lowerT.resize(3); moveDone = false;}
		void prepMove(Vertex* v, Triangulation& geom) override;
		bool isPossible(long vindex, Triangulation& geom) override;
		double acceptProb(Triangulation& geom) override;
		void doMove(Triangulation& geom) override;
		std::string toString();
};
#endif
