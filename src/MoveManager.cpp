#include "MoveManager.h"


MoveManager::MoveManager()
{
	moves[TWOFOUR] = new TwoFourMove();
	moves[FOURTWO] = new FourTwoMove();
	moves[TWOTWO] = new TwoTwoMove();
}

MoveManager::~MoveManager()
{
	for(auto it = moves.begin(); it != moves.end(); it++)
	{	
		it->second = NULL;
		delete it->second;
	}
}


void MoveManager::addMove(moveType mtype, Move* move)
{
	moves[mtype] = move;
}

void MoveManager::prepMove(moveType mtype, long label, Triangulation& geom)
{
	moves.at(mtype)->prepMove(label, geom);
}

bool MoveManager::movePossible(moveType mtype, long label, Triangulation& geom)
{
	return moves.at(mtype)->isPossible(label, geom);
}

double MoveManager::acceptProb(moveType mtype, Triangulation& geom)
{
	return moves.at(mtype)->acceptProb(geom);
}

void MoveManager::doMove(moveType mtype, Triangulation& geom)
{
	moves.at(mtype)->doMove(geom);
}

std::string MoveManager::toString()
{
	std::string output;
	output.append("TwoFourMove:\n" + moves.at(TWOFOUR)->toString() + "\n");
	output.append("FourTwoMove:\n" + moves.at(FOURTWO)->toString() + "\n");
	output.append("TwoTwoMove:\n" + moves.at(TWOTWO)->toString() + "\n");
}
