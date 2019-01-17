#ifndef movemanager_h
#define movemanager_h
#include "libraries.h"
#include "Triangulation.h"
#include "TwoTwoMove.h"
#include "TwoFourMove.h"
#include "FourTwoMove.h"

class MoveManager
{
	protected:
		//maybe change to a map<moveType, Move*>
		std::map<moveType, Move*> moves;
	public:
		MoveManager();
		~MoveManager();
		Move* operator[](const moveType mtype){return moves.at(mtype);}
		void addMove(moveType name, Move* move);
		void prepMove(moveType mtype, long label, Triangulation& geom);
		bool movePossible(moveType mtype, long label, Triangulation& geom);
		double acceptProb(moveType mtype, Triangulation& geom);
		void doMove(moveType mtype, Triangulation& geom); 
			
		std::string toString();
};
#endif
