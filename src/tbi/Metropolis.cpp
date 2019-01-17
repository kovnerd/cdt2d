#include "Metropolis.h"


bool Metropolis::movePossible(int move, long label, Lattice& lat)
{
	if(move == 0)
		return true;
	else if(move == 1)
	{
		if ((lat.slices[lat.triangles.at(label).time][1] > 3 && lat.slices[lat.triangles.at(label).time][0] > 3) || (lat.slices[lat.triangles.at(lat.triangles.at(label).vert(TRIANGLE)).time][0] > 3 && lat.slices[lat.triangles.at(lat.triangles.at(label).vert(TRIANGLE)).time][1] > 3))
			return true;
		else
			return false;
	}
	else
	{
			return true;
	}
}

double Metropolis::moveWeight(int move, Lattice& lat)
{
	double metro_weight, move_weight;
	//double volFixing = exp(-epsilon*((deltaN_2)*(deltaN_2) + 2*(deltaN_2)*(lat.N_2() - lat.N_fix())));
	if(move == 0)
	{
		metro_weight = exp(-lat.K_2());
		move_weight = 1.*lat.N_2()/(lat.N_2() + 2);
	}
	else if(move == 1)
	{
		metro_weight = exp(lat.K_2());
		move_weight = (lat.N_2() + 2.)/lat.N_2();
	}
	else
		metro_weight = move_weight = 1.;		

	return move_weight * metro_weight;
}

bool Metropolis::metroTest(int move, Lattice& lat)
{
	if(gsl_rng_uniform(r.get()) < moveWeight(move, lat))
		return true;
	else
		return false;
}

void Metropolis::prepMove(int move, long label, Lattice& lat)
{
	if(move == 0)//split
	{
		split.prepMove(label, lat);
	}
	else if (move == 1)//fuse
	{
		fuse.prepMove(label, lat);
	}
	else if(move == 2)//swap
	{
		swap.prepMove(label, lat);
	}
}

void Metropolis::step(Lattice& lat)
{
	int randMove = gsl_rng_uniform_int(r.get(), 3);//randomly chooses a move 0 or 1: 0 for split, 1 for fuse
	bool success = false;
	if(!movePossible(randMove, schedule.front(), lat))
		success = false;
	else
	{
		if(metroTest(randMove, lat))
		{
			success = true;
			prepMove(randMove, schedule.front(), lat);
			if(randMove == 0)
			{
				split.makeMove(lat);
				schedule.push(split[FUTURE][1]->self);
				schedule.push(split[PAST][1]->self);
			}
			else if(randMove == 1)
				fuse.makeMove(lat);
			else if(randMove == 2)
				swap.makeMove();
		}
	}
	if(randMove == 0)
	{
		schedule.push(schedule.front());
		(success) ? split.accepts++ : split.rejects++;
	}
	else if(randMove == 1)
	{
		if(success) {fuse.accepts++;} else{fuse.rejects++; schedule.push(schedule.front());}
	}
	else if(randMove == 2)
	{
		schedule.push(schedule.front());
		(success) ? swap.accepts++ : swap.rejects++;
	}
	schedule.pop();
}

void Metropolis::sweep(Lattice& lat)
{
	for(int i = 0; i < sweepSize; i++)
	{
		if(schedule.empty())
		{
			std::cout << "schedule machine broke...\n";
			break;
		}
		if(!lat.isDeleted(TRIANGLE, schedule.front()))
			step(lat);
		else
			schedule.pop();
	}
}

std::string Metropolis::toString()
{
	std::string output = "";
	output.append("Move | accept rate | reject rate |\n");
	output.append("split: | " + std::to_string(1.*split.accepts/(split.attempts() + fuse.attempts() + swap.attempts())) + " | " + std::to_string(1.*split.rejects/(split.attempts() + fuse.attempts() + swap.attempts())) + " |\n");
	output.append("fuse: | " + std::to_string(1.*fuse.accepts/(split.attempts() + fuse.attempts() + swap.attempts())) + " | " + std::to_string(1.*fuse.rejects/(split.attempts() + fuse.attempts() + swap.attempts())) + " |\n");
	output.append("swap: | " + std::to_string(1.*swap.accepts/(split.attempts() + fuse.attempts() + swap.attempts())) + " | " + std::to_string(1.*swap.rejects/(split.attempts() + fuse.attempts() + swap.attempts())) + " |\n");	
	output.append("total accept rate: " + std::to_string((1.*split.accepts + 1.*fuse.accepts + swap.accepts)/(split.attempts() + fuse.attempts() + swap.attempts())) + " | total reject rate: " + std::to_string((1.*split.rejects + 1.*fuse.rejects + 1.* swap.rejects)/(split.attempts() + fuse.attempts() + swap.attempts())) + "\n");	

	/*
	output.append("(2,4) MOVE\n" + split.toString() + "\n");
	output.append("(4,2) MOVE\n" + fuse.toString() + "\n");
	output.append("(2,2) MOVE\n" + swap.toString() + "\n");
	*/
	//output.append(schedule.toString() + "\n");

	return output;
}
