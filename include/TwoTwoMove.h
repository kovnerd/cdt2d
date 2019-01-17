#ifndef twotwo_h
#define twotwo_h
#include "libraries.h"
#include "Triangulation.h"
#include "Move.h"

class TwoTwoMove : public Move
{
	private:
		std::vector<Vertex*> upperV;
		std::vector<Vertex*> lowerV;
		std::vector<Triangle*> sameT;
		std::vector<Triangle*> diffT;

	public:
		std::string name = "TwoTwo";
		TwoTwoMove(){moveDone = false; upperV.resize(2); lowerV.resize(2); sameT.resize(2); diffT.resize(2);}
		void prepMove(long label, Triangulation& geom) override;
		bool isPossible(long label, Triangulation& geom) override;
		double acceptProb(Triangulation& geom) override;
		void doMove(Triangulation& geom) override;
		std::string toString();
};

#endif
