#ifndef errorestimator_h
#define errorestimator_h
#include "libraries.h"

class ErrorEstimator
{
	public:
		std::vector<double> error;
		virtual void generateError(std::vector<double> data){}
		std::string toString()
		{
			std::string output = "error: ";
			for(int i = 0; i < error.size(); i++)
			{
				output.append(std::to_string(error[i]) + " ");
			}
			output.append("\n");
			return output;
		}
};
#endif
