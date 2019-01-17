#ifndef twofour_h
#define twofour_h
#include "libraries.h"
#include "Move.h"
#include "Lattice.h"

class TwoFourMove : public Move
{
	private:
		std::vector<Vertex*> diffV;
		std::vector<Vertex*> sameV;//index 1 has empty vertex that needs to be filled

		//each are of size 3
		//index 1 is the empty triangle that needs to be filled
		std::vector<Triangle*> upperT;
		std::vector<Triangle*> lowerT;
	public:
		std::vector<Triangle*> operator[](const direction dir){return (dir == FUTURE) ? upperT : lowerT;}
		TwoFourMove(std::vector<Triangle*> upt, std::vector<Triangle*> dwnt) {upperT = upt; lowerT = dwnt;}
		TwoFourMove(long label, Lattice& lat) {prepMove(label, lat);}
		TwoFourMove() {upperT = std::vector<Triangle*>(); lowerT = std::vector<Triangle*>();}

		void prepMove(long label, Lattice& lat)
		{
			if(lat.deleted(TRIANGLE).empty())
				lat.refill_deleted(TRIANGLE, lat.N_2());
			long newTlabel1 = lat.deleted(TRIANGLE).front(); lat.deleted(TRIANGLE).pop();
			
			if(lat.deleted(TRIANGLE).empty())
				lat.refill_deleted(TRIANGLE, lat.N_2());
			long newTlabel2 = lat.deleted(TRIANGLE).front(); lat.deleted(TRIANGLE).pop();
			
			auto newItT1 = lat.triangles.find(newTlabel1);
			if(newItT1 == lat.triangles.end())
				lat.triangles.insert(std::make_pair(newTlabel1, Triangle(newTlabel1)));
			else
				lat.triangles.at(newTlabel1).self = newTlabel1;
			auto newItT2 = lat.triangles.find(newTlabel2);
			if(newItT2 == lat.triangles.end())
				lat.triangles.insert(std::make_pair(newTlabel2, Triangle(newTlabel2)));
			else
				lat.triangles.at(newTlabel2).self = newTlabel2;

			std::vector<Triangle*> ts1({&lat.triangles.at(label), &lat.triangles.at(newTlabel1), &lat.triangles.at(lat.triangles.at(label).next(TRIANGLE))});
			std::vector<Triangle*> ts2({&lat.triangles.at(lat.triangles.at(label).vert(TRIANGLE)), &lat.triangles.at(newTlabel2), &lat.triangles.at(lat.triangles.at(lat.triangles.at(label).vert(TRIANGLE)).next(TRIANGLE))});
			if(lat.triangles.at(label).type == 2)
			{
				upperT = ts1;
				lowerT = ts2;
			}
			else
			{
				upperT = ts2;
				lowerT = ts1;

			}
		}

		void makeMove(Lattice& lat)
		{
			//change labels of neighboring triangles
			upperT[0]->next(TRIANGLE) = upperT[1]->self;
			upperT[2]->prev(TRIANGLE) = upperT[1]->self;
			lowerT[0]->next(TRIANGLE) = lowerT[1]->self;
			lowerT[2]->prev(TRIANGLE) = lowerT[1]->self;
			
			//create new triangles
			upperT[1]->time = upperT[0]->time;
			upperT[1]->type = upperT[0]->type;
			upperT[1]->setTs(std::array<long, 3>({upperT[0]->self, upperT[2]->self, lowerT[1]->self})); 
			lowerT[1]->time = lowerT[0]->time;
			lowerT[1]->type = lowerT[0]->type;
			lowerT[1]->setTs(std::array<long, 3>({lowerT[0]->self, lowerT[2]->self, upperT[1]->self})); 
			if(lat.largest(TRIANGLE) <= upperT[1]->self)
				lat.largest(TRIANGLE) = upperT[0]->self;
			if(lat.largest(TRIANGLE) <= lowerT[1]->self)
				lat.largest(TRIANGLE) = lowerT[0]->self;
			lat.incrN_2();
			//lat.incrN_0();
			lat.incrSlices(upperT[0]->time, 2);
			lat.incrSlices(lowerT[0]->time, 1);
		}
		
		std::string toString()
		{
			std::string output;
			output.append("Upper Triangles:\n");
			for(int i = 0; i < upperT.size(); i++)
				output.append(upperT[i]->toString() + "\n");
			output.append("Lower Triangles:\n");
			for(int i = 0; i < lowerT.size(); i++)
				output.append(lowerT[i]->toString() + "\n");
			output.append("\n");
			return output;
		}
};
#endif
