#ifndef QPESOLVER_H
#define QPESOLVER_H
#include <iostream> 
#include "stringtoNum.h"
using namespace Eigen;
VectorXd LagrangeMethod(MatrixXd& m){
	int dim=m.cols()-1;
	MatrixXd G(dim,dim);
	G<<m.topLeftCorner(dim,dim);
	VectorXd g(dim);
	g<<m.topRightCorner(dim,1);
	int Erow=m.rows()-dim;
	MatrixXd A(Erow,dim);
	A<<m.bottomLeftCorner(Erow,dim);
	VectorXd b(Erow);
	b<<m.bottomRightCorner(Erow,1);
	MatrixXd A1(m.rows(),m.rows());
	A1<<G,(-1*A.transpose()),(-1*A),MatrixXd::Zero(Erow,Erow);
	VectorXd b1(m.rows());
	b1<<(-1*g),(-1*b);
	VectorXd sln = A1.colPivHouseholderQr().solve(b1);
	VectorXd x=sln.head(dim);
	std::cout<<"The optimal solution x: "<<x<<'\n';
	std::cout<<"The optimal value at x: "<<(0.5*x.transpose()*G*x+g.transpose()*x)<<'\n';
	return sln;
}
#endif