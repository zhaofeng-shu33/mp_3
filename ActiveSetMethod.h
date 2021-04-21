#ifndef ACTIVESETMETHOD_H
#define ACTIVESETMETHOD_H
#include <iostream> 
#include "stringtoNum.h"
#include "QPESolver.h"
using namespace Eigen;
void ActiveSetMethod(MatrixXd& m,VectorXd& InitialPoint){ //all the constraints are greater than
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
	VectorXd x=InitialPoint;
	bool* W=new bool[Erow];
	int j=0;	
	for(int i=0;i<Erow;i++){
			if((A.row(i)*x)(0,0)==b(i)){
				 W[i]=true;j++;
			}
			else W[i]=false;
	}

	while(1){
	std::cout<<"The Working set: ";
	j=0;
	for(int i=0;i<Erow;i++)
			if(W[i]){
					std::cout<<i+1<<' ';j++;}
	std::cout<<'\n';
		
	MatrixXd SM(dim+j,dim+1);
	SM<<G,(g+G*x),MatrixXd::Zero(j,dim+1);
	j=0;	
	for(int i=0;i<Erow;i++)
			if(W[i]){
				SM.row(j+dim)=m.row(dim+i);
				SM(j+dim,dim)=0;
				j++;
			}
	VectorXd sln=LagrangeMethod(SM);
	VectorXd d=sln.head(dim);
	VectorXd lambda=sln.tail(j);
	std::cout<<"d: "<<d<<'\n';
	std::cout<<"lambda: "<<lambda<<'\n';

	if(d.transpose()*d<0.00001){
		 double mindest=lambda(0);int enter_candidate=0;
		 for(int i=1;i<j;i++)
		 			if(lambda(i)<mindest){
		 					mindest=lambda(i);
		 					enter_candidate=i;
		 			}
		 if(mindest>=0){
		 		std::cout<<"Optimal solution found:\n x= "<<x<<"\n optimal value equals "<<(0.5*x.transpose()*G*x+g.transpose()*x);
		 		return;
		 	}
		 else{
		 	  j=-1;
		 	  for(int i=0;i<Erow;i++){
		 	  		if(W[i])j++;
    		 	  if(j==enter_candidate){W[i]=false;break;}
		 	 }
		 }	
	}
	else{
			VectorXd temp=A*(x+d)-b;bool value=true;
			for(int i=0;i<Erow;i++)if(temp(i)<0){value=false;break;}
			if(value)x+=d;
			else{
				double alpha=1;int k=-1;
				for(int i=0;i<Erow;i++){
						if((!W[i])&&(A.row(i)*d)(0,0)<0){
						   double t=(b(i)-A.row(i)*x)/(A.row(i)*d)(0,0);
						   if(alpha>t){alpha=t;k=i;}
						}
				}
				W[k]=true;
				x+=alpha*d;
				std::cout<<"The next iteration point x= "<<x<<'\n';
			}
	}
	}
}
#endif