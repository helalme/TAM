//double check Layer*i or j, since i,j start with 0

#include "stdafx.h"

//InTMatrix should not contain time column, only should hold data, should be modified later
void solveFHCP(const dVector2D& InTMatrix, const dVector2D& refMatrix, dVector2D& outTMatrix)
{ 
	//calculating initial Temperature
	dVector1D initTemp;
	calculateInitialTemp(InTMatrix, initTemp);
	
	//evaluating supporting data
	double dInvRefTemp = 0.01;
	std::size_t time = InTMatrix.size();
	std::size_t responseTimeOfUT = time;
	std::size_t nLayer = InTMatrix[1].size();
	
	dVector3D vvvResponsesForAllTimeSteps;
	vvvResponsesForAllTimeSteps = dVector3D(time-1,dVector2D(time-1,dVector1D(nLayer)));

	for (std::size_t i=0; i<time-1; ++i)
	{
		for (std::size_t j=0; j< nLayer; ++j)
		{
			for (std::size_t k=i; k<i+responseTimeOfUT-1; ++k)
			{
				if(k<time-1)
				{
					for (std::size_t l=0; l<nLayer; ++l)
					{
						vvvResponsesForAllTimeSteps[i][k][j] += (InTMatrix[i+1][l]- InTMatrix[i][l]) *(refMatrix[k-i+1][j+(l+1)*nLayer-nLayer+1])*dInvRefTemp;
					}
				}
			}
		}
	}
	//initializing with inital temp
	for (std::size_t i=0; i<InTMatrix.size(); ++i)
	{
		for (std::size_t j=0; j<initTemp.size(); ++j)
		{
			outTMatrix[i][j] = initTemp[j];
		}
	}
	//calculating out temp
	for (std::size_t i=1; i<time; ++i)
	{
		for (std::size_t j=0; j< nLayer; ++j)
		{
			for (std::size_t k=0; k<time-1; ++k)
			{
				outTMatrix[i][j] += vvvResponsesForAllTimeSteps[k][i-1][j];
			}
		}
	}
	
}  

void calculateInitialTemp(const dVector2D& M, dVector1D& V)
{
	for (size_t i=0; i<M[0].size(); ++i)
		V.push_back( M[0][i]);
}  
