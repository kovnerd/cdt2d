#include "TwoTwoMove.h"

//is label a triangle or vertex label???
//write like its a triangle label...
void TwoTwoMove::prepMove(long label, Triangulation& geom)
{
	moveDone = false;
	sameT.resize(2);
	diffT.resize(2);
	upperV.resize(2);
	lowerV.resize(2);
	if(geom.triangle(label).type != geom.triangle(label).nextTriangle()->type)
	{
		sameT[0] = &geom.triangle(label);
		sameT[1] = sameT[0]->nextTriangle();
		diffT[0] = sameT[0]->vertTriangle();
		diffT[1] = sameT[1]->vertTriangle();
	}
	else if(geom.triangle(label).type != geom.triangle(label).prevTriangle()->type)
	{
		sameT[0] = geom.triangle(label).prevTriangle();
		sameT[1] = &geom.triangle(label);
		diffT[0] = sameT[0]->vertTriangle();
		diffT[1] = sameT[1]->vertTriangle();
	}
	if(sameT[0]->type == 1)
	{
		upperV[0] = sameT[0]->prevVertex();
		upperV[1] = upperV[0]->nextVertex();
		lowerV[0] = sameT[0]->vertVertex();
		lowerV[1] = lowerV[0]->nextVertex();
	}
	else if(sameT[0]->type == 2)
	{
		upperV[0] = sameT[0]->vertVertex();
		upperV[1] = upperV[0]->nextVertex();
		lowerV[0] = sameT[0]->prevVertex();
		lowerV[1] = lowerV[0]->nextVertex();
	}
}

//always possible???
bool TwoTwoMove::isPossible(long label, Triangulation& geom)
{
	if(geom.triangle(label).type == geom.triangle(label).nextTriangle()->type && geom.triangle(label).type == geom.triangle(label).prevTriangle()->type)
		return false;
	else
		return true;
}

double TwoTwoMove::acceptProb(Triangulation& geom)
{
	return 1.;
}

void TwoTwoMove::doMove(Triangulation& geom)
{
	if(sameT[0]->type == 1)
	{
		//update triangles
		std::swap(sameT[0]->type, sameT[1]->type);
		std::swap(sameT[0]->vertTriangle(), sameT[1]->vertTriangle());
		std::swap(diffT[0]->vertTriangle(), diffT[1]->vertTriangle());
		sameT[0]->nextVertex() = lowerV[1];
		std::swap(sameT[0]->prevVertex(), sameT[0]->vertVertex());
		sameT[1]->prevVertex() = upperV[0];
		std::swap(sameT[1]->nextVertex(), sameT[1]->vertVertex());
		//update vertices
		upperV[0]->adjT(PAST).push_back(sameT[1]);
		upperV[1]->adjT(PAST).pop_front();
		lowerV[0]->adjT(FUTURE).pop_back();
		lowerV[1]->adjT(FUTURE).push_front(sameT[0]);
	}
	else if(sameT[0]->type == 2)
	{
		//update triangles
		std::swap(sameT[0]->type, sameT[1]->type);
		std::swap(sameT[0]->vertTriangle(), sameT[1]->vertTriangle());
		std::swap(diffT[0]->vertTriangle(), diffT[1]->vertTriangle());
		sameT[0]->nextVertex() = upperV[1];
		std::swap(sameT[0]->prevVertex(), sameT[0]->vertVertex());
		sameT[1]->prevVertex() = lowerV[0];
		std::swap(sameT[1]->nextVertex(), sameT[1]->vertVertex());
		//update vertices
		upperV[0]->adjT(PAST).pop_back();
		upperV[1]->adjT(PAST).push_front(sameT[0]);
		lowerV[0]->adjT(FUTURE).push_back(sameT[1]);
		lowerV[1]->adjT(FUTURE).pop_front();
	}
}


std::string TwoTwoMove::toString()
{
	std::string output;
	output.append("triangles on same time slice:\n");
	output.append(sameT[0]->toString() + "\n" + sameT[1]->toString() + "\n");
	output.append("triangles on different time slice:\n");
	output.append(diffT[0]->toString() + "\n" + diffT[1]->toString() + "\n");
	output.append("upper vertices:\n");
	output.append(upperV[0]->toString() + "\n" + upperV[1]->toString() + "\n");
	output.append("lower vertices:\n");
	output.append(lowerV[0]->toString() + "\n" + lowerV[1]->toString() + "\n");

	return output;
}
