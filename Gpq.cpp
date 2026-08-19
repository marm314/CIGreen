#include"Gpq.h"

void build_Gpq_tau(double &tau,Input Input_commands,double **Np1_cr_N, double **Nm1_an_N,complex<double> **Gpq)
{
 size_t ibas,jbas,istate;
 complex<double>factor;
 for(ibas=0;ibas<Input_commands.nBasis;ibas++)
 {
  for(jbas=0;jbas<Input_commands.nBasis;jbas++)
  {
   Gpq[ibas][jbas]=CZERO;
  }
 }
 if(tau>ZERO)
 {
  // N+1 contribution
  for(istate=0;istate<Input_commands.file_Np1.size();istate++)
  {
   factor=-im*exp(-im*tau*(Input_commands.Enp1[istate]-Input_commands.En));
   for(ibas=0;ibas<Input_commands.nBasis;ibas++)
   {
    for(jbas=0;jbas<Input_commands.nBasis;jbas++)
    {
     Gpq[ibas][jbas]+=factor*Np1_cr_N[istate][ibas]*Np1_cr_N[istate][jbas];
    }
   }
  } 
 }
 else
 {
  // N-1 contribution
  if(tau==ZERO){tau=pow(TEN,-EIGHT);}
  for(istate=0;istate<Input_commands.file_Nm1.size();istate++)
  {
   factor=im*exp(-im*tau*(Input_commands.En-Input_commands.Enm1[istate]));
   for(ibas=0;ibas<Input_commands.nBasis;ibas++)
   {
    for(jbas=0;jbas<Input_commands.nBasis;jbas++)
    {
     Gpq[ibas][jbas]+=factor*Nm1_an_N[istate][jbas]*Nm1_an_N[istate][ibas];
    }
   }
  } 
 }
}

void build_Gpq_w(double &wfreq,Input Input_commands,double **Np1_cr_N, double **Nm1_an_N,complex<double> **Gpq)
{
 size_t ibas,jbas,istate;
 complex<double>factor;
 for(ibas=0;ibas<Input_commands.nBasis;ibas++)
 {
  for(jbas=0;jbas<Input_commands.nBasis;jbas++)
  {
   Gpq[ibas][jbas]=CZERO;
  }
 }
 // N+1 contribution
 for(istate=0;istate<Input_commands.file_Np1.size();istate++)
 {
  factor=wfreq-(Input_commands.Enp1[istate]-Input_commands.En)+Input_commands.weta*im;
  factor=ONE/factor;
  for(ibas=0;ibas<Input_commands.nBasis;ibas++)
  {
   for(jbas=0;jbas<Input_commands.nBasis;jbas++)
   {
    Gpq[ibas][jbas]+=factor*Np1_cr_N[istate][ibas]*Np1_cr_N[istate][jbas];
   }
  }
 } 
 // N-1 contribution
 for(istate=0;istate<Input_commands.file_Nm1.size();istate++)
 {
  factor=wfreq-(Input_commands.En-Input_commands.Enm1[istate])-Input_commands.weta*im;
  factor=ONE/factor;
  for(ibas=0;ibas<Input_commands.nBasis;ibas++)
  {
   for(jbas=0;jbas<Input_commands.nBasis;jbas++)
   {
    Gpq[ibas][jbas]+=factor*Nm1_an_N[istate][jbas]*Nm1_an_N[istate][ibas];
   }
  }
 } 
}

