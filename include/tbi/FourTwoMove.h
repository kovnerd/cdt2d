#ifndef fourtwo_h
#define fourtwo_h
#include "libraries.h"
#include "Move.h"
#include "Lattice.h"

class FourTwoMove : public Move
{
	private:
		//each are of size 3
		//index 1 gets flagged for deletion
		std::vector<Triangle*> upperT;
		std::vector<Triangle*> lowerT;
	public:
		std::vector<Triangle*> operator[](const direction dir){return (dir == FUTURE) ? upperT : lowerT;}
		FourTwoMove(std::vector<Triangle*> upt, std::vector<Triangle*> dwnt){upperT = upt; lowerT = dwnt;}
		FourTwoMove(long label, Lattice& lat){prepMove(label, lat);}
		
		FourTwoMove() {upperT = std::vector<Triangle*>(); lowerT = std::vector<Triangle*>();}

		void prepMove(long label, Lattice& lat)
		{	
			std::vector<Triangle*> ts1({&lat.triangles.at(lat.triangles.at(label).prev(TRIANGLE)), &lat.triangles.at(label), &lat.triangles.at(lat.triangles.at(label).next(TRIANGLE))});
			std::vector<Triangle*> ts2({&lat.triangles.at(lat.triangles.at(lat.triangles.at(label).vert(TRIANGLE)).prev(TRIANGLE)), &lat.triangles.at(lat.triangles.at(label).vert(TRIANGLE)), &lat.triangles.at(lat.triangles.at(lat.triangles.at(label).vert(TRIANGLE)).next(TRIANGLE))});
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
			upperT[0]->next(TRIANGLE) = upperT[2]->self;
			lowerT[0]->next(TRIANGLE) = lowerT[2]->self;
			upperT[2]->prev(TRIANGLE) = upperT[0]->self;
			lowerT[2]->prev(TRIANGLE) = lowerT[0]->self;
			//delete triangles
			long upperTlabel = upperT[1]->self;
			long lowerTlabel = lowerT[1]->self;
			if(upperTlabel == lat.ref(TRIANGLE)[lat.triangles.at(upperTlabel).time])
				lat.ref(TRIANGLE)[lat.triangles.at(upperTlabel).time] = lat.triangles.at(upperTlabel).next(TRIANGLE);
			if(lowerTlabel == lat.ref(TRIANGLE)[lat.triangles.at(lowerTlabel).time])
				lat.ref(TRIANGLE)[lat.triangles.at(lowerTlabel).time] = lat.triangles.at(lowerTlabel).next(TRIANGLE);
			lat.decrN_2();
			//lat.decrN_0();
			lat.decrSlices(upperT[0]->time, 2);
			lat.decrSlices(lowerT[0]->time, 1);
			lat.deleted(TRIANGLE).push(upperTlabel);
			lat.deleted(TRIANGLE).push(lowerTlabel);
			
			upperT[1]->flagForDeletion();
			lowerT[1]->flagForDeletion();
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
