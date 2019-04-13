#include "stringtoNum.h"
#include "ActiveSetMethod.h"
int main(int argc, char *argv[]) 
{   
	MatrixXd MI(7,9);
  Initialize(MI,argv[1]);
	MatrixXd IniPre(4,9);
  Initialize(IniPre,argv[2]);
  VectorXd Ini=IniPre.transpose();
  std::cout<<"Ini: "<<Ini<<'\n';
	ActiveSetMethod(MI,Ini);	
	 system("pause");
}
