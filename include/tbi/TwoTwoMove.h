#ifndef twotwo_h
#define twotwo_h
#include "libraries.h"
#include "Move.h"
#include "Lattice.h"

class TwoTwoMove : public Move
{
	private:
		std::vector<Triangle*> sameT;
		std::vector<Triangle*> diffT;//0 is below, 1 is above
		std::vector<Vertex*> upperV;
		std::vector<Vertex*> lowerV;
	public:
		TwoTwoMove(std::vector<Triangle*> samt, std::vector<Triangle*> dift, std::vector<Vertex*> upv, std::vector<Vertex*> lwv){sameT = samt; diffT = dift; upperV = upv; lowerV = lwv;}
		TwoTwoMove(long label, Lattice& lat){prepMove(label, lat);}
		
		TwoTwoMove() : TwoTwoMove(std::vector<Triangle*>(), std::vector<Triangle*>(), std::vector<Vertex*>(), std::vector<Vertex*>()){}

		void prepMove(long vlabel, Lattice& lat)
		{
			long vlabelvert = lat.triangles.at(lat.vertices.at(vlabel).adjT(PAST, 0)).vert(VERTEX);
			long tlabel = lat.vertices.at(vlabel).adjT(PAST, 0);
			std::vector<Vertex*> uV({&lat.vertices.at(lat.triangles.at(lat.vertices.at(vlabel).getToPrev()).prev(VERTEX)), &lat.vertices.at(vlabel)});
			std::vector<Vertex*> lV(&lat.vertices.at(lat.triangles.at(lat.vertices.at(vlabelvert).getToPrev()).prev(VERTEX)) , &lat.vertices.at(vlabelvert));
			std::vector<Triangle*> sT({&lat.triangles.at(tlabel), &lat.triangles.at(lat.triangles.at(tlabel).next(TRIANGLE))});
			std::vector<Triangle*> dT({&lat.triangles.at(lat.triangles.at(tlabel).vert(TRIANGLE)), &lat.triangles.at(lat.triangles.at(lat.triangles.at(tlabel).next(TRIANGLE)).vert(TRIANGLE))});
			sameT = sT;
			diffT = dT;
			upperV = uV;
			lowerV = lV;
		}
		void makeMove()
		{
			//fix triangle neighborhood of upperV[0]
			upperV[0]->push(PAST, sameT[0]->self);
			upperV[0]->adjT(PAST, upperV[0]->n_p) = sameT[1]->self;
			//fix triangle neighborhood of upperV[1]
			upperV[1]->adjT(PAST, 0) = sameT[1]->self;
			upperV[1]->remove(PAST, sameT[1]->self);//removing duplicate
			//fix triangle neighborhood of lowerV[0]
			lowerV[0]->adjT(FUTURE, lowerV[0]->n_f) = sameT[0]->self;
			lowerV[0]->remove(FUTURE, sameT[0]->self);//removing duplicate
			//fix triangle neighborhood of lowerV[1]
			lowerV[1]->push(FUTURE, sameT[0]->self);
			lowerV[1]->adjT(FUTURE, 0) = sameT[0]->self;
			
			//swap vertical neighbors of diffT's
			std::swap(diffT[0]->vert(TRIANGLE), diffT[1]->vert(TRIANGLE));
			//swap sameT's types
			std::swap(sameT[0]->type, sameT[1]->type);
			//swap sameT's vertical neighbors
			std::swap(sameT[0]->vert(TRIANGLE), sameT[1]->vert(TRIANGLE));
			//fix sameT's vertices
			std::array<long, 3> newST0({sameT[0]->vert(VERTEX), sameT[1]->next(VERTEX), sameT[0]->prev(VERTEX)}), newST1({sameT[0]->prev(VERTEX), sameT[1]->vert(VERTEX), sameT[1]->next(VERTEX)});
			sameT[0]->setVs(newST0);
			sameT[1]->setVs(newST1);
		}
		
		std::string toString()
		{
			std::string output;
			output.append("Triangles on same slice:\n");
			for(int i = 0; i < sameT.size(); i++)
				output.append(sameT[i]->toString() + "\n");
			output.append("\nTriangles on different slice:\n");
			for(int i = 0; i < diffT.size(); i++)
				output.append(diffT[i]->toString() + "\n");
			output.append("\nVertices on upper slice:\n");
			for(int i = 0; i < upperV.size(); i++)
				output.append(upperV[i]->toString() + "\n");
			output.append("\nVertices on lower slice:\n");
			for(int i = 0; i < lowerV.size(); i++)
				output.append(lowerV[i]->toString() + "\n");
			output.append("\n");
			return output;
		}
};
#endif
