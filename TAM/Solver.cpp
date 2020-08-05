
#include "stdafx.h"

const dVector1D conjugateGradient(const dVector2D& A, const dVector1D& b)
{
	double tol = 1e-4;
	std::size_t max_iter=1000;
	std::size_t size=A.size();
	dVector1D p(size), x(size), r(size),Ap(size);
	double alpha=0, beta=0, rrOld=0, rrNew=0;

	r = subtractVector(b, matrixDotVector(A,x));
	p = r;
	rrOld = vectorDotProduct(r,r);
	double normr0 = norm(r); 
	if ( normr0 <= tol)
	{
		tol = normr0;
		max_iter = 0;
		return x;
	}

	for (std::size_t i = 1; i <= max_iter; ++i)
	{
		Ap = matrixDotVector(A,p);
		alpha = rrOld/vectorDotProduct(p,Ap);
		//std::transform(p.begin(), p.end(), alpha, p.begin(), helperFunction);
		x = addVector(x, scalarIntoVector(p,alpha));
		r = subtractVector(r, scalarIntoVector(Ap,alpha));
		if (norm(r)<=tol)
			break;
		rrNew = vectorDotProduct(r,r);
		beta = rrNew/rrOld;
		rrOld= rrNew;
		p = addVector(r,scalarIntoVector(p,beta));
	}
	//tol = resid;
	return x;
}
