#ifndef bootstrap_h
#define bootstrap_h
#include "libraries.h"
#include "ErrorEstimator.h"

class Bootstrap : public ErrorEstimator 
{
	private:
		size_t numBootstrap;
		std::vector<std::vector<double> > bootstrap;
		std::unique_ptr<gsl_rng, void(*)(gsl_rng*)> r;
		void generateBootstrap(size_t numBootstrap, std::vector<double> data)
		{
			for(int j = 0; j < numBootstrap; j++)
			{
				std::vector<double> bs;
				for(int i = 0; i < data.size(); i++)
					bs.push_back(data[gsl_rng_uniform_int(r.get(), data.size())]);
				bootstrap.push_back(bs);
			}
		}
	public:
		Bootstrap(size_t sz) : r(gsl_rng_alloc(gsl_rng_taus2), gsl_rng_free){numBootstrap = sz; gsl_rng_set(r.get(), (unsigned long)time(NULL));}
		Bootstrap() : Bootstrap(100){}

		void generateError()
		{
			double* bstrp;
			for(int i = 0; i < numBootstrap; i++)
			{
				bstrp = &bootstrap[i][0];
				error.push_back(gsl_stats_sd(bstrp, 1, bootstrap[i].size()));
			}
		}
};

#endif
