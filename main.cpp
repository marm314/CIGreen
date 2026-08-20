#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<cstring>
#include<complex>
#include"Input_commands.h"
#include"Mathematical_Functions.h"
#include"gitver.h"
#include"io.h"
#include"Gpq.h"

using namespace std;

vector<C_det>Cdet;

int main(int argc, char *argv[])
{
 size_t istate,ibas,jbas;
 double tau,wfreq;
 double **Nm1_an_N;
 double **Np1_cr_N;
 double **DM1,**EIGVEC;
 complex<double>spectral_w;
 complex<double>**G_pq;
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
 cout<<setprecision(8)<<fixed;
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
 G_pq=new complex<double>*[Input_commands.nBasis];
 for(ibas=0;ibas<Input_commands.nBasis;ibas++)
 {
  G_pq[ibas]=new complex<double>[Input_commands.nBasis];
 }
 // Store the N electron system
 read_nsystem(Input_commands,Cdet);
 // Compute the < N-1 | anh_p | N > overlaps
 ovlp_nm1_an_n_system(Input_commands,Cdet,Nm1_an_N);
 // Compute the < N+1 | cre_p | N > overlaps
 ovlp_np1_cr_n_system(Input_commands,Cdet,Np1_cr_N);
 // If time evaluation
 if(Input_commands.time)
 {
  cout<<endl;
  cout<<" ----------------------------"<<endl; 
  cout<<" ---  G(tau) evaluations  ---"<<endl; 
  cout<<" ----------------------------"<<endl; 
  cout<<endl;
  if(Input_commands.imtime)
  {
   cout<<endl;
   cout<<" Use of imaginary times is ON"<<endl;
   cout<<endl;
  }
  for(tau=Input_commands.t0;tau<=Input_commands.tlast;tau=tau+Input_commands.tstep)
  {
   cout<<endl;
   cout<<" Evaluating time tau"<<setw(20)<<tau<<endl;
   cout<<endl;
   if(abs(tau)<pow(TEN,-EIGHT)){tau=-pow(TEN,-EIGHT);}
   // Build the G_pq(tau) matrix
   build_Gpq_tau(tau,Input_commands,Np1_cr_N,Nm1_an_N,G_pq);
   for(ibas=0;ibas<Input_commands.nBasis;ibas++)
   {
    for(jbas=0;jbas<Input_commands.nBasis;jbas++)
    {
     cout<<setw(30)<<G_pq[ibas][jbas];
    }
    cout<<endl;
   } 
   // Build the 1RDM from G_pq
   if(tau<ZERO && abs(tau)<pow(TEN,-FIVE))
   {
    cout<<endl;
    cout<<" Building the 1RDM"<<endl;
    DM1=new double*[Input_commands.nBasis];
    EIGVEC=new double*[Input_commands.nBasis];
    for(ibas=0;ibas<Input_commands.nBasis;ibas++)
    {
     DM1[ibas]=new double[Input_commands.nBasis];
     EIGVEC[ibas]=new double[Input_commands.nBasis];
     for(jbas=0;jbas<Input_commands.nBasis;jbas++)
     {
      DM1[ibas][jbas]=(-im*G_pq[ibas][jbas]).real(); // The 1-RDM is real in our case
      cout<<setw(20)<<DM1[ibas][jbas];
     }
     cout<<endl;
    }
    jacobi(Input_commands.nBasis,DM1,EIGVEC);// Build the NOs
    cout<<" Occupation numbers 1RDM"<<endl;
    for(ibas=0;ibas<Input_commands.nBasis;ibas++)
    {
     cout<<setw(20)<<DM1[ibas][ibas]<<endl;
     delete[] DM1[ibas];DM1[ibas]=NULL;
     delete[] EIGVEC[ibas];EIGVEC[ibas]=NULL;
    }
    delete[] DM1; DM1=NULL;
    delete[] EIGVEC; EIGVEC=NULL;
   }
   // Build the hole 1RDM from G_pq
   if(tau>ZERO && abs(tau)<pow(TEN,-FIVE))
   {
    cout<<endl;
    cout<<" Building the (hole) 1RDM"<<endl;
    DM1=new double*[Input_commands.nBasis];
    EIGVEC=new double*[Input_commands.nBasis];
    for(ibas=0;ibas<Input_commands.nBasis;ibas++)
    {
     DM1[ibas]=new double[Input_commands.nBasis];
     EIGVEC[ibas]=new double[Input_commands.nBasis];
     for(jbas=0;jbas<Input_commands.nBasis;jbas++)
     {
      DM1[ibas][jbas]=(im*G_pq[ibas][jbas]).real();
      cout<<setw(20)<<DM1[ibas][jbas];
     }
     cout<<endl;
    }
    jacobi(Input_commands.nBasis,DM1,EIGVEC);// Build the NOs
    cout<<" Occupation numbers (hole) 1RDM"<<endl;
    for(ibas=0;ibas<Input_commands.nBasis;ibas++)
    {
     cout<<setw(20)<<DM1[ibas][ibas]<<endl;
     delete[] DM1[ibas];DM1[ibas]=NULL;
     delete[] EIGVEC[ibas];EIGVEC[ibas]=NULL;
    }
    delete[] DM1; DM1=NULL;
    delete[] EIGVEC; EIGVEC=NULL;
   }
  }
 }
 // If frequency evaluation
 if(Input_commands.freq)
 {
  cout<<endl;
  cout<<" --------------------------"<<endl; 
  cout<<" ---  G(w) evaluations  ---"<<endl; 
  cout<<" --------------------------"<<endl; 
  cout<<endl;
  if(Input_commands.imfreq)
  {
   cout<<endl;
   cout<<" Use of imaginary frequencies is ON"<<endl;
   cout<<endl;
  }
  for(wfreq=Input_commands.w0;wfreq<=Input_commands.wlast;wfreq=wfreq+Input_commands.wstep)
  {
   cout<<endl;
   cout<<" Evaluating frequency "<<setw(20)<<wfreq<<endl;
   cout<<endl;
   // Build the G_pq(w) matrix
   build_Gpq_w(wfreq,Input_commands,Np1_cr_N,Nm1_an_N,G_pq);
   for(ibas=0;ibas<Input_commands.nBasis;ibas++)
   {
    for(jbas=0;jbas<Input_commands.nBasis;jbas++)
    {
     cout<<setw(30)<<G_pq[ibas][jbas];
    }
    cout<<endl;
   }
   // Spectral function
   if(Input_commands.spectral)
   {
    build_Gpq_w_Retarded(wfreq,Input_commands,Np1_cr_N,Nm1_an_N,G_pq);
    spectral_w=CZERO;
    for(ibas=0;ibas<Input_commands.nBasis;ibas++)
    {
     spectral_w-=(G_pq[ibas][ibas]).imag();
    }
    spectral_w=spectral_w/PI;
    cout<<endl;
    cout<<" Spectral function w : "<<setw(20)<<wfreq<<" A(w) : "<<setw(30)<<TWO*spectral_w.real()<<endl; // Times 2 to sum both spin channels
    cout<<endl;
   }
  }
 }
 // Deallocate arrays
 for(istate=0;istate<Input_commands.file_Np1.size();istate++)
 {
  delete[] Np1_cr_N[istate];Np1_cr_N[istate]=NULL;
 }
 for(istate=0;istate<Input_commands.file_Nm1.size();istate++)
 {
  delete[] Nm1_an_N[istate];Nm1_an_N[istate]=NULL;
 }
 for(ibas=0;ibas<Input_commands.nBasis;ibas++)
 {
  delete[] G_pq[ibas];G_pq[ibas]=NULL;
 }
 delete[] Np1_cr_N;Np1_cr_N=NULL;
 delete[] Nm1_an_N;Nm1_an_N=NULL;
 delete[] G_pq;G_pq=NULL;
 cout<<endl;
 cout<<"Git sha: "<<sha<<endl;
 cout<<endl;
 cout<<"----------------------------------------"<<endl;
 cout<<"--        Normal termination          --"<<endl;
 cout<<"----------------------------------------"<<endl;
 cout<<"----------------------------------------"<<endl;
 return 0;
}

