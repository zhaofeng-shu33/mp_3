#ifndef DUALSIMPLEXMETHOD_H
#define DUALSIMPLEXMETHOD_H
#include <iostream> 
#include "stringtoNum.h"
using namespace Eigen;
void DualSimplexMethod(MatrixXd& m,VectorXd& BV){
	MatrixXd A(m.rows()-1,m.cols()-1);
  VectorXd c(A.cols());
  VectorXd b(BV.size());
  std::cout <<"DualSimplexMatrix:\n"<< m << std::endl;
  for(int i=0;i<BV.size();i++){
       m.row(i+1)/=m(i+1,BV(i)-1);
       for(int j=0;j<m.rows();j++){
           if(j!=(i+1))
           	  m.row(j)-=m.row(i+1)*m(j,BV(i)-1);
      }
  }
  std::cout <<"DualSimplexMatrixInCanonicalForm:\n"<< m << std::endl;
	while(1){
  A=m.bottomLeftCorner(A.rows(),A.cols());
  c=m.topLeftCorner(1,c.size()).transpose(); 
  b=m.bottomRightCorner(b.size(),1);
  
  double mindest=b(0);
  int Rahne=0;
  for(int i=1;i<b.size();i++)
      if(b(i)<mindest){
      	 mindest=b(i);
      	 Rahne=i;
      	}
  if(mindest>=0){
  	 std::cout<<"The optimal condition has been reached.\n";
  	 std::cout<<"The basic variables and their corresponding values are:\n";
  	 for(int i=0;i<BV.size();i++)
  	     std::cout<<BV(i)<<":"<<b(i)<<"\n";
  	 std::cout<<"The optimal value is: "<<-1*m(0,m.cols()-1);
  	 return;
  }

  else{
  	std::cout<<"OuterVariable: "<<BV(Rahne)<<"\n";
  	int Spalte=0;
  	mindest=100;
  	for(int i=0;i<A.cols();i++)
  	    if(A(Rahne,i)<0&&((-1*c(i))/A(Rahne,i)<mindest)){
  	    	 mindest=(-1*c(i))/A(Rahne,i);
  	    	 Spalte=i;
  	    }
    if(mindest==100){std::cout<<"The LP problem is infeasible";exit(0);}
    std::cout<<"EnterVariable: "<<Spalte+1<<"\n";	
  	BV(Rahne)=Spalte+1;
    m.row(Rahne+1)/=m(Rahne+1,Spalte);
    for(int i=0;i<m.rows();i++)
        if(i!=(Rahne+1))
        	 m.row(i)-=m.row(Rahne+1)*m(i,Spalte);
    std::cout<<"After transformation, the DualSimplex Matirx changes to:\n"<<m<<"\n";
   }
   }
	
}
#endif




