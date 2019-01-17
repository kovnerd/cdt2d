#include "Triangle.h"
#include "Vertex.h"

Triangle::Triangle(long label, int type, long time, adjList<Triangle*> tris, adjList<Vertex*> vs)
{
	this->label = label;
	this->deleted = false;
	this->type = type;
	this->time = time;
	this->triangles = tris;
	this->vertices = vs;
}

void Triangle::erase(Triangle* t)
{
	t->deleted = true;
	t->prevVertex() = (Vertex*)NULL;
	t->nextVertex() = (Vertex*)NULL;
	t->vertVertex() = (Vertex*)NULL;
	
	t->prevTriangle() = (Triangle*)NULL;
	t->nextTriangle() = (Triangle*)NULL;
	t->vertTriangle() = (Triangle*)NULL;
}

Vertex*& Triangle::prevVertex() 
{
	return vertices[0];
}
Vertex*& Triangle::nextVertex() 
{
	return vertices[1];
}
Vertex*& Triangle::vertVertex() 
{
	return vertices[2];
}
void Triangle::setVertices(adjList<Vertex*> vs)
{
	vertices = vs;
}

Triangle*& Triangle::prevTriangle() 
{
	return triangles[0];
}
Triangle*& Triangle::nextTriangle() 
{
	return triangles[1];
}
Triangle*& Triangle::vertTriangle() 
{
	return triangles[2];
}
void Triangle::setTriangles(adjList<Triangle*> tris)
{
	triangles = tris;
}

std::string Triangle::toString()
{
	std::string output;
	std::string delsign = (deleted) ? "-" : "+";
	output.append("(t = " + delsign + std::to_string(label) + ", type = " + std::to_string(type) + ", time = " + std::to_string(time)  + ", adjT = ["); 
      	for(int i = 0; i < triangles.size(); i++)
	{
		output.append(std::to_string(triangles[i]->label));
		if(i != triangles.size()-1)
			output.append(" ");
		else
			output.append("]");
	}		
	
	output.append(", adjV = [");
       	for(int i = 0; i < vertices.size(); i++)
	{
		output.append(std::to_string(vertices[i]->label));
		if(i != vertices.size()-1)
			output.append(" ");
		else
			output.append("]");
	}	
	output.append(")");
	
	return output;
}

