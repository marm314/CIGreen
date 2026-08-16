#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<cstring>
#include"gitver.h"

using namespace std;

void read_store_files(string inp_name);

struct idx
{
 int i,sigma; // Sigma 0 is alpha, 1 is beta
};
struct C_det
{
 double Coef;
 vector<idx>indices_ref;
 vector<idx>indices_work;
};
vector<C_det>Cdet;
string file_N;
vector<string>file_Np1;
vector<string>file_Nm1;


int main(int argc, char *argv[])
{
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"---  From CI vector to Green's function  ---"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"-- Developed by: Dr. M. Rodriguez-Mayorga --"<<endl;
 cout<<"--      email: marm3.14@gmail.com         --"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 string sha;
 gitversion(sha);
 if(argc!=2)
 {
  cout<<"Include the input file"<<endl;
  cout<<"./CIGreen input "<<endl;
  cout<<endl;
  cout<<"Git sha: "<<sha<<endl;
  cout<<endl;
  cout<<"----------------------------------------"<<endl;
  cout<<"--        Normal termination          --"<<endl;
  cout<<"----------------------------------------"<<endl;
  cout<<"----------------------------------------"<<endl;
  return 0;
 }
 string inp_name=argv[1];
 // Read input file
 read_store_files(inp_name);
 
 cout<<endl;
 cout<<"Git sha: "<<sha<<endl;
 cout<<endl;
 cout<<"----------------------------------------"<<endl;
 cout<<"--        Normal termination          --"<<endl;
 cout<<"----------------------------------------"<<endl;
 cout<<"----------------------------------------"<<endl;
 return 0;
}

void read_store_files(string inp_name)
{
 cout<<endl; 
 cout<<" Reading input file "<<inp_name<<endl; 
 cout<<endl; 
}
