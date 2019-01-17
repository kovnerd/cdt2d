#ifndef vertex_h
#define vertex_h
#include "libraries.h"

class Triangle;


class Vertex
{
	private:
		bool deleted;
		long label;//for debugging purposes
		long time;
		//virtual std::string label();
		//reference to adjacent triangles
		adjList<Triangle*> futureT;
		adjList<Triangle*> pastT;

	public:
		Vertex(long label, long time, adjList<Triangle*> fT, adjList<Triangle*> pT);
		Vertex(long label, long time) : Vertex(label, time, adjList<Triangle*>(), adjList<Triangle*>()){}
		Vertex(long label) : Vertex(label, -1){}	
		Vertex() : Vertex(-1){}	
		long n_p(){return futureT.size()-1;}
		long n_f(){return pastT.size()-1;}
		adjList<Triangle*>& adjT(const direction dT){if(dT == FUTURE){return futureT;} else {return pastT;}}
		void insert(const direction dir, int pos, Triangle* tri);
		void remove(const direction dir, int pos);
		void remove(const direction dir, Triangle* tri);
		static void erase(Vertex* v);

		Vertex* nextVertex(); 
		Vertex* prevVertex(); 
	
		std::string toString();
};
#endif
