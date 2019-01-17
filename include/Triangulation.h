#ifndef triangulation_h
#define triangulation_h
#include "libraries.h"
#include "Triangle.h"
#include "Vertex.h"

class Triangulation
{
	protected:
		long time;
		long n_fix;//triangle number to be fixed at
		double k_2;//rescaled cosmological constant
		std::deque<Vertex> vertices;
		std::deque<Triangle> triangles;

		//std::deque<Vertex> deletedVertices;
		//std::deque<Triangle> deletedTriangles;
		
		size_t numDeletedVertices;
		size_t numDeletedTriangles;

		long largestV, largestT;
		void refillDeleted(simplex sim, long amount);

	public:
		long N_2(){return triangles.size() - numDeletedTriangles;}
		long N_0(){return vertices.size() - numDeletedVertices;}
		long& TIME(){return time;}
		long& N_fix(){return n_fix;}
		double& K_2(){return k_2;}
		Triangulation(long n2, long time, long n_fix, double k_2);
		Triangulation(long time) : Triangulation(4, time, 4, 0.){}
		Triangulation() : Triangulation (4, 2, 4, 0.){}
		Vertex& vertex(long label){return vertices[label];}
		Triangle& triangle(long label){return triangles[label];}
		void insert(const simplex sim);
		void remove(const simplex sim, long vlabel);
		void clean(const simplex sim);//make this a private function...?

		std::string toString();
};
#endif
