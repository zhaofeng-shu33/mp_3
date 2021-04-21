#ifndef STRINGTONUM_H
#define STRINGTONUM_H
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <Eigen/Dense> 
#include <string>
#include <fstream>
void Initialize(Eigen::MatrixXd& m1,char* txtName){
    using namespace std;
    using namespace boost;
    string str;
    vector<string> split_result;
    int numR=0;
    ifstream fin(txtName);
    while(getline(fin,str))numR++;
    split(split_result,str,is_any_of(" "),token_compress_on);
    int numC=split_result.size();
    fin.close();
    fin.open(txtName);
    m1.resize(numR, numC);
    int i=0;
    while(getline(fin,str)){
    split(split_result,str,is_any_of(" "),token_compress_on);
    for(int j=0;j<split_result.size();j++)
        m1(i,j)=lexical_cast<double>(split_result[j]);
    i++;
    }
    fin.close();  
}
#endif