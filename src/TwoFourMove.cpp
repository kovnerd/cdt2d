#include "TwoFourMove.h"

void TwoFourMove::prepMove(Simplex* v, Triangulation& geom)
{
	moveDone = false;	
	sameV[0] = ;//polymorph v into Vertex*???
	sameV[2] = sameV[0]->nextVertex();
	upperV = sameV[0]->adjT(FUTURE).back()->vertVertex();
	lowerV = sameV[0]->adjT(PAST).back()->vertVertex();
	//alternatively
	//lowerV = sameV[0][FUTURE].back()->vertTriangle()->vertVertex();
	upperT[0] = sameV[0]->adjT(FUTURE).back();
	lowerT[0] = sameV[0]->adjT(PAST).back();
	//insert new triangles into geom
	//insert new vertex into geom
	geom.insert(VERTEX);
	sameV[1] = &geom.vertex(geom.N_0()-1); 	
	geom.insert(TRIANGLE);
	geom.insert(TRIANGLE);
	upperT[1] = &geom.triangle(geom.N_2()-1);
	lowerT[1] = &geom.triangle(geom.N_2()-2);
}

//always possible
bool TwoFourMove::isPossible(long vindex, Triangulation& geom)
{
	return true;
}

double TwoFourMove::acceptProb(Triangulation& geom)
{
	return (1.*geom.N_0())/(geom.N_0() + 1.) * exp(-2*geom.K_2());
}

void TwoFourMove::doMove(Triangulation& geom)
{	
	//fill in new triangles 
	upperT[1]->deleted = false;
	upperT[1]->time = upperT[0]->time;
	upperT[1]->type = upperT[0]->type;
	upperT[1]->setVertices(adjList<Vertex*>({sameV[1], sameV[2], upperV}));
	upperT[1]->setTriangles(adjList<Triangle*>({upperT[0], upperT[0]->nextTriangle(), lowerT[1]}));
	
	upperT[1]->deleted = false;
	lowerT[1]->time = lowerT[0]->time;
	lowerT[1]->type = lowerT[0]->type;
	lowerT[1]->setVertices(adjList<Vertex*>({sameV[1], sameV[2], lowerV}));
	lowerT[1]->setTriangles(adjList<Triangle*>({lowerT[0], lowerT[0]->nextTriangle(), upperT[1]}));	
	
	//update neighboring triangles	
	upperT[0]->nextTriangle()->prevTriangle() = upperT[1];
	upperT[0]->nextTriangle() = upperT[1];
	upperT[0]->nextVertex() = sameV[1];
	lowerT[0]->nextTriangle()->prevTriangle() = lowerT[1];
	lowerT[0]->nextTriangle() = lowerT[1];
	lowerT[0]->nextVertex() = sameV[1];

	//fill in geom.vertex(geom.N_0()-1);
	sameV[1]->deleted = false;
	sameV[1]->time = sameV[0]->time;
	sameV[1]->adjT(FUTURE).push_back(upperT[0]);
	sameV[1]->adjT(FUTURE).push_back(upperT[1]);
	sameV[1]->adjT(PAST).push_back(lowerT[0]);
	sameV[1]->adjT(PAST).push_back(lowerT[1]);
	
	//update old vertices
	sameV[2]->adjT(FUTURE)[0] = upperT[1];
	sameV[2]->adjT(PAST)[0] = lowerT[1];

	//insert upperT[1], lowerT[1] into adjLists of upperV and lowerV
	auto it1 = std::find(upperV->adjT(PAST).begin(), upperV->adjT(PAST).end(), upperT[0]);
	auto it2 = std::find(lowerV->adjT(FUTURE).begin(), lowerV->adjT(FUTURE).end(), lowerT[0]);
	
	upperV->insert(PAST, it1 - upperV->adjT(PAST).begin() + 1, upperT[1]);	
	lowerV->insert(FUTURE, it2 - lowerV->adjT(FUTURE).begin() + 1, lowerT[1]);	
	
	moveDone = true;
}


std::string TwoFourMove::toString()
{
	std::string output;
	if(moveDone)
	{
		output.append("AFTER MOVE IS PERFORMED:\n");
		output.append("upper triangles:\n");
		output.append(upperT[0]->toString() + "\n" + upperT[1]->toString() + "\n");
		output.append("lower triangles:\n");
		output.append(lowerT[0]->toString() + "\n" + lowerT[1]->toString() + "\n");
		output.append("upper vertex:\n");
		output.append(upperV->toString() + "\n");
		output.append("lower vertex:\n");
		output.append(lowerV->toString() + "\n");
		output.append("vertices on same time slice:\n");
		output.append(sameV[0]->toString() + "\n" + sameV[1]->toString() + "\n" +sameV[2]->toString() + "\n");
	}
	else
	{
		output.append("BEFORE MOVE IS PERFORMED:\n");
		output.append("upper triangles:\n");
		output.append(upperT[0]->toString() + "\n");
		output.append("lower triangles:\n");
		output.append(lowerT[0]->toString() + "\n");
		output.append("upper vertex:\n");
		output.append(upperV->toString() + "\n");
		output.append("lower vertex:\n");
		output.append(lowerV->toString() + "\n");
		output.append("vertices on same time slice:\n");
		output.append(sameV[0]->toString() + "\n" + sameV[2]->toString() + "\n");
	}


	return output;
}
