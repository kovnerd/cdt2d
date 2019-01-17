#include "Vertex.h"
#include "Triangle.h"

//crappy O(N^2) intersection algorithm
//returns positions of first intersection in both A and B


Vertex::Vertex(long label, long tme, adjList<Triangle*> tF, adjList<Triangle*> tP)
{
	label = label;
	deleted = false;
	time = tme;
	this->futureT = tF;
	this->pastT = tP;
}

void Vertex::insert(const direction dir, int pos, Triangle* tri)
{
	adjT(dir).insert(adjT(dir).begin() + pos, tri);//adjust insert pos by +/-1?
}

void Vertex::remove(const direction dir, int pos)
{
	adjT(dir).erase(adjT(dir).begin() + pos);
}

void Vertex::remove(const direction dir, Triangle* tri)
{
	auto pos = std::find(adjT(dir).begin(), adjT(dir).end(), tri);
	adjT(dir).erase(pos);
}

void Vertex::erase(Vertex* v)
{
	v->deleted = true;
	for(int i = 0; i < v->adjT(FUTURE).size(); i++)
		v->adjT(FUTURE)[i] = (Triangle*)NULL;
	for(int i = 0; i < v->adjT(PAST).size(); i++)
		v->adjT(PAST)[i] = (Triangle*)NULL;
}

Vertex* Vertex::nextVertex() 
{
	return futureT.back()->nextVertex();
}
Vertex* Vertex::prevVertex() 
{
	return futureT[0]->prevVertex();
}

std::string Vertex::toString()
{
	std::string output;
	std::string delsign = (deleted) ? "-" : "+";
	output.append("(v = " + delsign + std::to_string(label) + ", time = " + std::to_string(time) + ", adjTri(t+1) = [");
	for(int i = 0; i < futureT.size(); i++)
	{
		output.append(std::to_string(futureT[i]->label));
		if(i != futureT.size()-1)
			output.append(" ");
	}		
	output.append("], n_f = " + std::to_string(futureT.size()-1));
	output.append(", adjTri(t-1) = [");	
	for(int i = 0; i < pastT.size(); i++)
	{
		output.append(std::to_string(pastT[i]->label));
		if(i != pastT.size()-1)
			output.append(" ");
	}		
	output.append("], n_p = " + std::to_string(pastT.size()-1) + ")");

	return output;
}
