#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<cstring>
#include"Input_commands.h"
#include"gitver.h"
#include"io.h"

using namespace std;

vector<C_det>Cdet;

int main(int argc, char *argv[])
{
 size_t istate,ibas;
 double **Nm1_an_N;
 double **Np1_cr_N;
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
 // Read input file
 string inp_name=argv[1];
 cout<<endl; 
 cout<<" Reading input file "<<inp_name<<endl; 
 cout<<endl; 
 Input Input_commands(inp_name);
 Np1_cr_N=new double*[Input_commands.file_Np1.size()];
 Nm1_an_N=new double*[Input_commands.file_Nm1.size()];
 for(istate=0;istate<Input_commands.file_Np1.size();istate++)
 {
  Np1_cr_N[istate]=new double[Input_commands.nBasis];
  for(ibas=0;ibas<Input_commands.nBasis;ibas++)
  {
   Np1_cr_N[istate][ibas]=ZERO;
  }
 }
 for(istate=0;istate<Input_commands.file_Nm1.size();istate++)
 {
  Nm1_an_N[istate]=new double[Input_commands.nBasis];
  for(ibas=0;ibas<Input_commands.nBasis;ibas++)
  {
   Nm1_an_N[istate][ibas]=ZERO;
  }
 }
 // Store the N electron system
 read_nsystem(Input_commands,Cdet);
 // Compute the < N-1 | anh_p | N > overlaps
 ovlp_nm1_an_n_system(Input_commands,Cdet,Nm1_an_N);
 // Compute the < N+1 | cre_p | N > overlaps
 ovlp_np1_cr_n_system(Input_commands,Cdet,Np1_cr_N);

 // Deallocate arrays
 for(istate=0;istate<Input_commands.file_Np1.size();istate++)
 {
  delete[] Np1_cr_N[istate];Np1_cr_N[istate]=NULL;
 }
 for(istate=0;istate<Input_commands.file_Nm1.size();istate++)
 {
  delete[] Nm1_an_N[istate];Nm1_an_N[istate]=NULL;
 }
 delete[] Np1_cr_N;Np1_cr_N=NULL;
 delete[] Nm1_an_N;Nm1_an_N=NULL;
 cout<<endl;
 cout<<"Git sha: "<<sha<<endl;
 cout<<endl;
 cout<<"----------------------------------------"<<endl;
 cout<<"--        Normal termination          --"<<endl;
 cout<<"----------------------------------------"<<endl;
 cout<<"----------------------------------------"<<endl;
 return 0;
}

