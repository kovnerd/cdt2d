#include "SpecDim.h"


SpecDim(Lattice* latt)
{
	lat = latt;

}

void prepK(long label_0)
{
	labels.push(label_0);
	std::deque<long> tempLabels = lat->getSchedule(TRIANGLE);
	for(int i = 0; i < tempLabels.size(); i++)
	{
		if(tempLabels[i] == label_0)
			diffKernel.insert(std::make_pair(label_0, 1.));
		else
			diffKernel.insert(std::make_pair(tempLabels[i], 0));	
	}
}

void evolveK()
{
	for(int l = 0; l < labels.size(); l++)
	{
		nextKernel.at(labels[l]) = (1-DIFF_CONST)diff.at(labels[l]) + DIFF_CONST/3.(diffKernel.at(lat->triangles.at(labels[l]).prev(TRIANGLE)) + diffKernel.at(lat->triangles.at(labels[l]).next(TRIANGLE)) + diffKernel.at(lat->triangles.at(labels[l]).vert(TRIANGLE)));
		labels.push_back(diffKernel.at(lat->triangles.at(labels[l]).prev(TRIANGLE));	
		labels.push_back(diffKernel.at(lat->triangles.at(labels[l]).next(TRIANGLE));	
		labels.push_back(diffKernel.at(lat->triangles.at(labels[l]).vert(TRIANGLE));	
	}
	//swap kernels
	nextKernel.swap(diffKernel);
}

double returnKernel(long label_0, long sigma_max)
{
	prepK(label_0);
	for(int sigma = 1; sigma <= sigma_max; sigma++)
		evolveK();
	return diffKernel.at(label_0);
}


double returnProb(long sigma)
{
	//find way to 	
}
