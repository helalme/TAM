#include "stdafx.h"

//output Temp data file should contain an additional column of time 
void solveIHCP(const dVector2D& outTMatrix, const dVector2D& refMatrix, dVector2D& InTMatrix)
{
	dVector1D initTemp;
	calculateInitTemp(outTMatrix, initTemp);

	//evaluating supporting data
	double dRefTemp=100.0, dInvRefTemp = 0.01;
	std::size_t time = outTMatrix.size();
	std::size_t responseTimeOfUT = time; //probably can be optimized here, hence responseTimeOfUT is initiated
	std::size_t nLayer = outTMatrix[1].size()- 1;

	dVector2D vvResponsesForAllTimeSteps;
	vvResponsesForAllTimeSteps = dVector2D(time,dVector1D(nLayer*nLayer));
	dVector2D vvResponsesForAllTimeStepsSum;
	vvResponsesForAllTimeStepsSum = dVector2D(time,dVector1D(nLayer*nLayer));
	dVector2D deltaInnWallTemp;
	deltaInnWallTemp = dVector2D(time-1,dVector1D(nLayer));
	
	//construct A , b
	dVector2D A = dVector2D(nLayer,dVector1D(nLayer));
	constructA(refMatrix, A);
	

	for (std::size_t i=0; i<time-1; ++i)
	{
		dVector1D b = dVector1D(nLayer);
		for (std::size_t j=0; j< nLayer; ++j)
		{
			double temp=0.0;
			if(i>0)
			{
				
				for (size_t l=0; l<nLayer; ++l)
				{
					temp +=  vvResponsesForAllTimeStepsSum[i+1][(l+1)*nLayer-nLayer+j];
				}
				
			}
			b[j] = (outTMatrix[i+1][j+1] - initTemp[j] - temp) * dRefTemp;
		}
		dVector1D T;
		T = conjugateGradient(A,b);
		for (size_t m=0; m<nLayer; ++m)
		{
			deltaInnWallTemp[i][m] = T[m];
		}

		vvResponsesForAllTimeSteps=dVector2D(time,dVector1D(nLayer*nLayer));
		for (size_t j=0; j<nLayer*nLayer; ++j)
		{
			for (size_t k=i+1; k< i+responseTimeOfUT; ++k)
			{
				if(k<time)
				{
					if(nLayer>1)
					{
						vvResponsesForAllTimeSteps[k][j] = refMatrix[k-i][j+1] * deltaInnWallTemp[i][j/nLayer] * dInvRefTemp;
					}
				}
			}
		}
		for (std::size_t it=1; it<time; ++it)
		{
			for (std::size_t jt=0; jt<nLayer*nLayer; ++jt)
			{
				vvResponsesForAllTimeStepsSum[it][jt]= vvResponsesForAllTimeStepsSum[it][jt]+ vvResponsesForAllTimeSteps[it][jt];
			}
		}
	}
	
	

	//setting initial Temp on InTMatrix
	for (std::size_t p=0; p<time; ++p)
	{
		InTMatrix[p] = initTemp;
	}

	//forming final inpT matrix
	for (std::size_t m=1; m<time; ++m)
	{
		for (std::size_t n=0; n<nLayer; ++n)
		{
			InTMatrix[m][n] = deltaInnWallTemp[m-1][n];
			InTMatrix[m][n] += InTMatrix[m-1][n];
		}
	}
}

void constructA(const dVector2D& vvOuterT, dVector2D& vvA )
{
	std::size_t Layer = vvA.size();
	for (std::size_t i=0; i<Layer; ++i)
	{
		for (std::size_t j=0; j< Layer; ++j)
		{
			vvA[i][j] = vvOuterT[1][j+(i+1)*Layer-Layer+1];
		}
	}
}

void calculateInitTemp(const dVector2D& M, dVector1D& V)
{
	for (size_t i=1; i<M[0].size(); ++i)
		V.push_back( M[0][i]);
}  
