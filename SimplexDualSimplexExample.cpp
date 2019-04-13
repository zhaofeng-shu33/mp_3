#include "SimplexMethod.h"
#include "stringtoNum.h"
int main(int argc, char *argv[]) 
{   
	MatrixXd MI(4,9);
  VectorXd BV(3);	   	
  Initialize(MI,argv[1]);
	BV.resize(MI.rows()-1);
	BV=TwoStageSimplexMethod(MI);
  system("pause");
}
