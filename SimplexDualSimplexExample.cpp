#include "SimplexMethod.h"
#include "stringtoNum.h"
int main(int argc, char *argv[]) 
{
	MatrixXd MI;
  VectorXd BV;	   	
  Initialize(MI, argv[1]);
	BV = TwoStageSimplexMethod(MI, true);
}
