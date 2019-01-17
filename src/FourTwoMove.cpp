#include "FourTwoMove.h"

//label is the vertex label being deleted
void FourTwoMove::prepMove(long label, Triangulation& geom)
{
	moveDone = false;
	sameV[1] = &geom.vertex(label);
	sameV[0] = sameV[1]->prevVertex();
	sameV[2] = sameV[1]->nextVertex();

	upperT[1] = sameV[1]->adjT(FUTURE)[sameV[1]->n_f()];
	upperT[0] = upperT[1]->prevTriangle();
	upperT[2] = upperT[1]->nextTriangle();

	lowerT[1] = sameV[1]->adjT(PAST)[sameV[1]->n_p()];
	lowerT[0] = lowerT[1]->prevTriangle();
	lowerT[2] = lowerT[1]->nextTriangle();
	
	upperV = upperT[0]->vertVertex();
	lowerV = lowerT[0]->vertVertex();
}
bool FourTwoMove::isPossible(long label, Triangulation& geom)
{
	if(geom.vertex(label).n_f() == 1 && geom.vertex(label).n_p() == 1)//add minimal kneck condition???
		return true;
	else
		return false;
}
double FourTwoMove::acceptProb(Triangulation& geom)
{
	return exp(geom.K_2())*(geom.N_0() + 1.)/geom.N_0();//isn't this just 1. REEEE
}
void FourTwoMove::doMove(Triangulation& geom)
{
	//update triangle neighbors of triangles
	upperT[0]->nextTriangle() = upperT[2];
	upperT[2]->prevTriangle() = upperT[0];
	lowerT[0]->nextTriangle() = lowerT[2];
	lowerT[2]->prevTriangle() = lowerT[0];
	
	//update vertex neighbors of triangles
	upperT[0]->nextVertex() = sameV[2];
	lowerT[0]->nextVertex() = sameV[2];
	
	//update triangle neighbors of vertices
	sameV[2]->adjT(FUTURE).pop_front();
	sameV[2]->adjT(PAST).pop_front();
	sameV[2]->adjT(FUTURE).push_front(upperT[0]);
	sameV[2]->adjT(PAST).push_front(lowerT[0]);

	upperV->remove(PAST, upperT[1]);//remove upperT[1] from upperV
	lowerV->remove(FUTURE, lowerT[1]);//remove lowerT[1] from lowerV
	

	//geom.remove CAUSING MEMORY LEAK??
	
	//remove sameV[1] from triangulation
	geom.remove(VERTEX, sameV[1]->label);
	//remove upperT[1] and lowerT[1] from triangulation
	geom.remove(TRIANGLE, upperT[1]->label);
	geom.remove(TRIANGLE, lowerT[1]->label);
	moveDone = true;
}
std::string FourTwoMove::toString()
{
	std::string output;
	if(moveDone)//print out everything except for sameV[1], upperT[1], lowerT[1]
	{
		output.append("AFTER MOVE IS PERFORMED:\n");
		output.append("same vertices:\n");
		output.append(sameV[0]->toString()  + "\n" + sameV[2]->toString() + "\n");
		output.append("upper vertex:\n");
		output.append(upperV->toString() + "\n");
		output.append("lower vertex:\n");
		output.append(lowerV->toString() + "\n");
		output.append("upper triangles:\n");
		output.append(upperT[0]->toString()  + "\n" + upperT[2]->toString() + "\n");
		output.append("lower triangles:\n");
		output.append(lowerT[0]->toString()  + "\n" + lowerT[2]->toString() + "\n");
	}
	else//print out everthing
	{
		output.append("BEFORE MOVE IS PERFORMED:\n");
		output.append("same vertices:\n");
		output.append(sameV[0]->toString() + "\n" + sameV[1]->toString() + "\n" + sameV[2]->toString() + "\n");
		output.append("upper vertex:\n");
		output.append(upperV->toString() + "\n");
		output.append("lower vertex:\n");
		output.append(lowerV->toString() + "\n");
		output.append("upper triangles:\n");
		output.append(upperT[0]->toString() + "\n" + upperT[1]->toString() + "\n" + upperT[2]->toString() + "\n");
		output.append("lower triangles:\n");
		output.append(lowerT[0]->toString() + "\n" + lowerT[1]->toString() + "\n" + lowerT[2]->toString() + "\n");
	}
	
	return output;
}
