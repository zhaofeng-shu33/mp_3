#include <windows.h>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
void Initialize(){
    using namespace std;
    using namespace boost;
    string str;
    vector<string> split_result;
    int numR=0;
    ifstream fin("testData3.txt");
    while(getline(fin,str))numR++;
    cout<<str<<'*';
    split(split_result,str,is_any_of(" "),token_compress_on);
    int numC=split_result.size();
    cout<<numR<<' '<<numC<<endl;
    fin.close();
    fin.open("testData3.txt");
    while(getline(fin,str)){
    split(split_result,str,is_any_of(" "),token_compress_on);
    for(int i=0;i<split_result.size();i++)
        cout<<lexical_cast<double>(split_result[i])<<' ';
    cout<<endl;
    }    
    fin.close();  
    
/*    for(tokenizer<char_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg){
       double num=lexical_cast<double>(*beg);
       cout<<num<<endl;
     }
  */  
}
