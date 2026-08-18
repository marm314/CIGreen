#include<iostream> 
#include<iomanip>
#include<vector>
#include<fstream>
#include<cstring>

using namespace std;

int main(int argc, char *argv[])
{
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"---    From FCIDUMP.out to spin-with     ---"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"-- Developed by: Dr. M. Rodriguez-Mayorga --"<<endl;
 cout<<"--      email: marm3.14@gmail.com         --"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 if(argc!=5)
 {
  cout<<"Include the input file"<<endl;
  cout<<"./fcidump_sw nBasis nElectrons Delta_spin_up_spin_down FCIDUMP.out"<<endl;
  cout<<endl;
  cout<<"----------------------------------------"<<endl;
  cout<<"--        Normal termination          --"<<endl;
  cout<<"----------------------------------------"<<endl;
  cout<<"----------------------------------------"<<endl;
  return 0;
 }
 int nBasis=atoi(argv[1]);
 int nElectrons=atoi(argv[2]);
 int Delta_ab=atoi(argv[3]);
 string file=argv[4];
 
 
 cout<<endl;
 cout<<"----------------------------------------"<<endl;
 cout<<"--        Normal termination          --"<<endl;
 cout<<"----------------------------------------"<<endl;
 cout<<"----------------------------------------"<<endl;
 return 0;
}
