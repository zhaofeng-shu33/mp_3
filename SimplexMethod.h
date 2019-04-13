#ifndef SIMPLEXMETHOD_H
#define SIMPLEXMETHOD_H
#include <iostream> 
#include "stringtoNum.h"
using namespace Eigen;
void SimplexMethod(MatrixXd& m,VectorXd& BV){
	
  MatrixXd A(m.rows()-1,m.cols()-1);
  VectorXd c(A.cols());
  VectorXd b(BV.size());
  std::cout <<"SimplexMatrix:\n"<< m << std::endl;
  for(int i=0;i<BV.size();i++){
       m.row(i+1)/=m(i+1,BV(i)-1);
       for(int j=0;j<m.rows();j++)
           if(j!=(i+1))
           	  m.row(j)-=m.row(i+1)*m(j,BV(i)-1);
  }
  std::cout <<"SimplexMatrixInCanonicalForm:\n"<< m << std::endl;

  while(1){
  A=m.bottomLeftCorner(A.rows(),A.cols());
  c=m.topLeftCorner(1,c.size()).transpose(); 
  b=m.bottomRightCorner(b.size(),1);
  
  double mindest=c(0);
  int Spalte=0;
  for(int i=1;i<A.cols();i++)
      if(c(i)<mindest){
      	 mindest=c(i);
      	 Spalte=i;
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
  	std::cout<<"EnterVariable: "<<(Spalte+1)<<"\n";
  	int Rahne=0;
  	double maximal=100;
  	for(int i=0;i<A.rows();i++)
  	    if(A(i,Spalte)>0&&(b(i)/A(i,Spalte)<maximal)){
  	    	 maximal=b(i)/A(i,Spalte);
  	    	 Rahne=i;
  	    }
    if(maximal==0){std::cout<<"The LP problem is unbounded";exit(0);}
    std::cout<<"OuterVariable: "<<BV(Rahne)<<"\n";	
  	BV(Rahne)=Spalte+1;
    m.row(Rahne+1)/=m(Rahne+1,Spalte);
    for(int i=0;i<m.rows();i++)
        if(i!=(Rahne+1))
        	 m.row(i)-=m.row(Rahne+1)*m(i,Spalte);
    std::cout<<"After transformation, the Simplex Matirx changes to:\n"<<m<<"\n";
   }
   }
}
#endif
VectorXd TwoStageSimplexMethod(MatrixXd& MI){
	VectorXd BV(MI.rows()-1);   
  MatrixXd Ma(MI.rows(),MI.rows()-1);
  for(int i=0;i<MI.rows()-1;i++)
      Ma(i+1,i)=1;	
  MatrixXd MIA(MI.rows(),MI.cols()+MI.rows()-1);;
  MIA<<MI.topLeftCorner(MI.rows(),MI.cols()-1),Ma,MI.col(MI.cols()-1);
	for(int i=0;i<MI.cols()-1;i++)
		  MIA(0,i)=0;
  for(int i=MI.cols()-1;i<MI.cols()+MI.rows()-2;i++){
      MIA(0,i)=1;
      BV(i+1-MI.cols())=i+1;
  }
	SimplexMethod(MIA,BV);
  SimplexMethod(MI,BV); 
  return BV;
}



