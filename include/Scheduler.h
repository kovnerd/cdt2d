#ifndef scheduler_h
#define scheduler_h
#include "libraries.h"

//make it like a priority queue...
template <class T>
class Scheduler
{
	protected:
		std::deque<T> schedule;
		std::shared_ptr<gsl_rng> r;
	public:
		Scheduler(){r = std::shared_ptr<gsl_rng>(gsl_rng_alloc(gsl_rng_taus2), gsl_rng_free); gsl_rng_set(r.get(), (unsigned long)time(NULL));}
		Scheduler(std::deque<T> lst){schedule = lst; r = std::shared_ptr<gsl_rng>(gsl_rng_alloc(gsl_rng_taus2), gsl_rng_free); gsl_rng_set(r.get(), (unsigned long)time(NULL));}
		//typical queue attributes
		size_t size(){return schedule.size();}
		bool empty(){return schedule.empty();}
		T front(){return schedule.front();}
		T pop()
		{
			if(!schedule.empty())
			{
				schedule.pop_front();
				int randIndex = gsl_rng_uniform_int(r.get(), schedule.size()- 1)  + 1;
				std::swap(schedule.front(), schedule[randIndex]);//swap element at randIndex with element at 1?
			}
		}
		void push(T element){schedule.push_back(element);}
		std::string toString()
		{
			std::string output = "";
			output.append("Schedule: " + std::to_string(schedule.front()) + " | ");
			int num_items = schedule.size();	
			for(int i = 1; i < num_items; i++)
			{
				output.append(std::to_string(schedule[i]) + " ");
			}
			output.append("\n");
			return output;
		}
};

#endif
