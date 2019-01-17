#ifndef triangle_h
#define triangle_h
#include "libraries.h"

class Vertex;

class Triangle
{
	private:
		bool deleted;
		long label;//debugging
		long time;
		//virtual std::string label();
		//	i = 0 -> prev
		//	i = 1 -> next
		//	i = 2 -> vert
		adjList<Triangle*> triangles;
		adjList<Vertex*> vertices;	
	public:
		int type;//1 for (1,2) simplex, 2 for (2,1) simplex
		Triangle(long label, int type, long time, adjList<Triangle*> tris, adjList<Vertex*> vs);
		Triangle(long label, int type, long time) : Triangle(label, type, time, adjList<Triangle*>(), adjList<Vertex*>()){}
		Triangle(long label) : Triangle(label, -1, -1) {}	
		Triangle() : Triangle(-1) {}	
		static void erase(Triangle* t);
		//access to neighboring vertices
		Vertex*& prevVertex(); 
		Vertex*& nextVertex(); 
		Vertex*& vertVertex(); 
		void setVertices(adjList<Vertex*> vs);

		//access to neighboring triangles
		Triangle*& prevTriangle(); 
		Triangle*& nextTriangle();
		Triangle*& vertTriangle();
		void setTriangles(adjList<Triangle*> tris);
		
		std::string toString();
};

#endif
