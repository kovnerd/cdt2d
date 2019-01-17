#include "Triangulation.h"

long PREV(long x, long l){return (x % l == 0) ? x + (l-1): x - 1;}
long NEXT(long x, long l){return ((x + 1) % l == 0) ? x - (l - 1) : x + 1;}
long N(long x, long y, long lx){return x+y*lx;}

//make toroidal flat triangulation with time time slices and n2 triangles
Triangulation::Triangulation(long n2, long time, long nfix, double k2)
{
	this->time = time;
	this->n_fix = nfix;
	this->k_2 = k2;
	long num_tri_per_slice = n2/time;
	long num_v_per_slice = num_tri_per_slice/2;
	numDeletedTriangles = 0;
	numDeletedVertices = 0;
	//A WHOLE SLEW OF CONSTANTS, REFER TO README PICTURE (if implemented in time)
	//basically, 	indices u, v, w represent vertices at time tprev, t, tnext
	//		indices l, m, n, o, p represent triangles at certain time, ordered depending on v/i parity:
	//			if i is even, then t(o) < t(n) < t(m) < t(l)	(no p)
	//			if i is odd, then t(m) < t(n) < t(o) < t(p) 	(no l)
	long i = 0;	
	long tprev = 0, tnext = 0;
	long v = 0, vprev = 0, vnext = 0, u = 0, unext = 0, w = 0, wprev = 0, wnext = 0;
	long n = 0, nprev = 0, npprev = 0, nppprev = 0, nnext = 0, nnnext = 0;
	long m = 0, mprev = 0, mpprev = 0, mppprev = 0, mnext = 0;
	long o = 0;
	//initial loop to get allocate memory
	for(long t = 0; t < time; t++)
	{
		i = 0;
		for(long x = 0; x < num_v_per_slice; x++)
		{
			v = N(x, t, num_v_per_slice);
			n = N(i, t, num_tri_per_slice);
			nnext = NEXT(n, num_tri_per_slice);
			//vertices[v] = Vertex(v, t);
			//triangles[n] = Triangle(n, 2, t);
			//triangles[nnext] = Triangle(nnext, 1, t);
			vertices.push_back(Vertex(v, t));
			triangles.push_back(Triangle(n, 2, t));
			triangles.push_back(Triangle(nnext, 1, t));
			i += 2;
		}
	}
	i = 0;
	//fill in neighbor data for existing vertices & triangles
	for(long t = 0; t < time; t++)
	{
		tprev = (t == 0) ? time - 1 : t - 1;
		tnext = (t == (time - 1)) ? 0 : t + 1;
		i = 0;
		for(long x = 0; x < num_v_per_slice; x++)
		{
			u = N(x, tprev, num_v_per_slice);
			v = N(x, t, num_v_per_slice);
			w = N(x, tnext, num_v_per_slice);
			vprev = PREV(v, num_v_per_slice);
			vnext = NEXT(v, num_v_per_slice);
			unext = NEXT(u, num_v_per_slice);
			wprev = PREV(w, num_v_per_slice);
			wnext = NEXT(w, num_v_per_slice);
			n = N(i, t, num_tri_per_slice);
			m = N(i+1, tprev, num_tri_per_slice);
			mprev = PREV(m, num_tri_per_slice);
			mpprev = PREV(mprev, num_tri_per_slice);
			nnext = NEXT(n, num_tri_per_slice);
			nnnext = NEXT(nnext, num_tri_per_slice);
			nprev = PREV(n, num_tri_per_slice);
			npprev = PREV(nprev, num_tri_per_slice);
			o = N(i, tnext, num_tri_per_slice);
			
			//fill in vertex neighbors of v
			vertices[v].adjT(FUTURE).push_back(&triangles[npprev]);
			vertices[v].adjT(FUTURE).push_back(&triangles[nprev]);
			vertices[v].adjT(FUTURE).push_back(&triangles[n]);
			vertices[v].adjT(PAST).push_back(&triangles[mpprev]);
			vertices[v].adjT(PAST).push_back(&triangles[mprev]);
			vertices[v].adjT(PAST).push_back(&triangles[m]);
			
			//fill in vertex neighbors of n,nnext
			triangles[n].setVertices(adjList<Vertex*>({&vertices[v], &vertices[vnext], &vertices[w]})); 
                        triangles[nnext].setVertices(adjList<Vertex*>({&vertices[w], &vertices[wnext], &vertices[vnext]}));
			//fill in triangle neighbors of n,nnext
			triangles[n].setTriangles(adjList<Triangle*>({&triangles[nprev], &triangles[nnext], &triangles[m]}));
			triangles[nnext].setTriangles(adjList<Triangle*>({&triangles[n], &triangles[nnnext], &triangles[o]}));
			i += 2;
		}
	}
	//initialize triangulation with some spare vertex labels 
	int d = 1;
	largestV = N_0() - 1;
	largestT = N_2() - 1;
	while(d <= 3*N_0())
	{
		vertices.push_back(Vertex(largestV + d++));
		numDeletedVertices++;
	}
	d = 1;
	while(d <= 3*N_2())
	{
		triangles.push_back(Triangle(largestT + d++));
		numDeletedTriangles++;
	}
}

void Triangulation::refillDeleted(simplex sim, long amount)
{
	if(sim == VERTEX)
	{
		int d = 1;
		while(d <= amount)
			vertices.push_back(Vertex(largestV + d++));
		largestV += amount;
	}
	else if(sim == TRIANGLE)
	{
		int d = 1;
		while(d <= amount)
			triangles.push_back(Triangle(largestT + d++));
		largestT += amount;
	}
}

void Triangulation::insert(const simplex sim)
{
	if(sim == VERTEX)
	{
		if(numDeletedVertices == 0)
			refillDeleted(VERTEX, 2*N_0());
		numDeletedVertices--;
	}
	else if(sim == TRIANGLE)
	{
		if(numDeletedTriangles == 0)
			refillDeleted(TRIANGLE, 4*N_2());
		numDeletedTriangles--;
	}
}

void Triangulation::remove(const simplex sim, long label)
{
	//deleting a simplex involves flagging the simplex structure for deletion and moving it to the back of the list via swap
	//notice that means that the simplex labels stored in the structures =/= index in simplex list (mainly used for debugging/printing purposes)
	if(sim == VERTEX)
	{
		std::cout << "erasing vertex:\n" + vertices[label].toString() + "\n";
		Vertex::erase(&vertices[label]);
		std::swap(vertices[label], vertices[N_0()-1]);
		numDeletedVertices++;
	}
	else if(sim == TRIANGLE)
	{
		std::cout << "erasing triangle:\n" + triangles[label].toString() + "\n";
		Triangle::erase(&triangles[label]);
		std::swap(triangles[label], triangles[N_2()-1]);
		numDeletedTriangles++;
	}
}

//check if the start of range is correct...(it should be???)
void Triangulation::clean(const simplex sim)
{
	if(sim == VERTEX)
	{
		vertices.erase(vertices.begin() + (N_0()), vertices.end());//N_0 +/ 1 or 0 ???
		numDeletedVertices = 0;
	}
	else if(sim == TRIANGLE)
	{
		triangles.erase(triangles.begin() + (N_2()), triangles.end());//N_0 +/ 1 or 0 ???
		numDeletedTriangles = 0;
	}
}


std::string Triangulation::toString()
{
	std::string output;
	long time_i = 0, label = 0;
	output.append("Constants:\n");
	output.append("N_2:" + std::to_string(N_2()) + "\n");
	output.append("N_0:" + std::to_string(N_0()) + "\n");
	output.append("N_fix:" + std::to_string(N_fix()) + "\n");
	output.append("TIME:" + std::to_string(TIME()) + "\n");
	output.append("K_2:" + std::to_string(K_2()) + "\n");
	output.append("\n");
	output.append("\nTriangles:\n");
	for(long t = 0; t < N_2(); t++)
		if(!triangles[t].deleted)
			output.append(triangles[t].toString() + "\n");
	output.append("\n");
	
	output.append("\nVertices:\n");
	for(long v = 0; v < N_0(); v++)
		if(!vertices[v].deleted)
			output.append(vertices[v].toString() + "\n");
	output.append("\n");
	
	output.append("\nNumber of Spare Vertices:" + std::to_string(numDeletedVertices) + "\n");
	output.append("\nNumber of Spare Triangles:" + std::to_string(numDeletedTriangles) + "\n");
	
	return output;
}
