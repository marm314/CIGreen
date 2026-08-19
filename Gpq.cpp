#include"Gpq.h"

void build_Gpq_tau(double &tau,Input Input_commands,double **Np1_cr_N, double **Nm1_an_N,complex<double> **Gpq)
{
 size_t ibas,jbas,istate;
 complex<double>tau_eval;
 complex<double>factor;
 for(ibas=0;ibas<Input_commands.nBasis;ibas++)
 {
  for(jbas=0;jbas<Input_commands.nBasis;jbas++)
  {
   Gpq[ibas][jbas]=CZERO;
  }
 }
 // Set tau_eval to real or imag
 tau_eval=tau;
 if(Input_commands.imtime){tau_eval=-tau_eval*im;}
 // Heaviside step function
 if(tau>ZERO)
 {
  // N+1 contribution
  for(istate=0;istate<Input_commands.file_Np1.size();istate++)
  {
   factor=-im*exp(-im*tau_eval*(Input_commands.Enp1[istate]-Input_commands.En));
   //cout<<-im*tau_eval*(Input_commands.Enp1[istate]-Input_commands.En)<<endl;
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
  for(istate=0;istate<Input_commands.file_Nm1.size();istate++)
  {
   factor=im*exp(-im*tau_eval*(Input_commands.En-Input_commands.Enm1[istate]));
   //cout<<-im*tau_eval*(Input_commands.En-Input_commands.Enm1[istate])<<endl;
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
 complex<double>wfreq_eval;
 complex<double>factor;
 for(ibas=0;ibas<Input_commands.nBasis;ibas++)
 {
  for(jbas=0;jbas<Input_commands.nBasis;jbas++)
  {
   Gpq[ibas][jbas]=CZERO;
  }
 }
 // Set freq_eval to real or imag
 wfreq_eval=wfreq;
 if(Input_commands.imfreq) wfreq_eval=wfreq_eval*im;
 // N+1 contribution
 for(istate=0;istate<Input_commands.file_Np1.size();istate++)
 {
  factor=wfreq_eval-(Input_commands.Enp1[istate]-Input_commands.En)+Input_commands.weta*im;
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
  factor=wfreq_eval-(Input_commands.En-Input_commands.Enm1[istate])-Input_commands.weta*im;
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

