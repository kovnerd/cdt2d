#ifndef observable_h
#define observable_h
#include "libraries.h"
#include "ErrorEstimator.h"
#include "Bootstrap.h"
//#include "Jackknife.h"
class Observable
{
	protected:
		std::vector<double> ensemble;
		ErrorEstimator err;
	public:
		Observable(size_t n_ens) {ensemble.resize(n_ens); err = Bootstrap(n_ens);}
		Observable() : Observable(0){}
		size_t size(){return ensemble.size();}
		double back(){return ensemble.back();}
		void record(double element){ensemble.push_back(element);}
		double& operator [](const int i){return ensemble[i];}
		double report()
		{
			double av = 0.;
			for(int i = 0; i < ensemble.size(); i++)
				av += ensemble[i];	
			av /= ensemble.size();
			return av;
		}
		void estimateError(){err.generateError(ensemble);}
		std::string toString(){return "";}
		std::vector<double> error(){return err.error;}
};

#endif
