#include"io.h"

void read_nsystem(Input Input_commands,vector<C_det>&Cdet)
{
 bool active=false;
 size_t idet,ielec,ndet=0,*index;
 double val,norm=ZERO;
 string line;
 index=new size_t[Input_commands.nelectrons];
 ifstream read_N(Input_commands.file_N);
 while(getline(read_N,line))
 {
  if(line==" Final CI vector")
  {
   active=true;
   getline(read_N,line);
  }
  if(line==" /EOF"){active=false;}
  if(active){ndet++;}
 }
 read_N.close();
 ndet--;
 read_N.open(Input_commands.file_N);
 while(getline(read_N,line))
 {
  if(line==" Final CI vector")
  {
   getline(read_N,line);
   for(idet=0;idet<ndet;idet++)
   {
    read_N>>val;
    for(ielec=0;ielec<Input_commands.nelectrons;ielec++)
    {
     read_N>>index[ielec];
    }
    for(ielec=Input_commands.nelectrons/2;ielec<Input_commands.nelectrons;ielec++)
    {
     index[ielec]=index[ielec]+Input_commands.nBasis;
    }
    Cdet.push_back({val});
    for(ielec=0;ielec<Input_commands.nelectrons;ielec++)
    {
     Cdet[idet].indices_ref.push_back(index[ielec]); 
    }
   } 
  }
 }
 read_N.close();
 cout<<setprecision(8)<<fixed;
 for(idet=0;idet<ndet;idet++)
 {
  norm=norm+Cdet[idet].Coef*Cdet[idet].Coef;
 }
/*
 for(idet=0;idet<ndet;idet++)
 {
  cout<<setw(20)<<Cdet[idet].Coef; 
  for(ielec=0;ielec<Input_commands.nelectrons;ielec++)
  {
   cout<<setw(5)<<Cdet[idet].indices_ref[ielec]; 
  }
  cout<<endl;
 }
*/
 cout<<" Sum_I | C_I |^2 = "<<setw(20)<<norm<<" N system"<<endl;
 for(idet=0;idet<ndet;idet++)
 {
  Cdet[idet].Coef=Cdet[idet].Coef/sqrt(norm);
 }
 norm=ZERO;
 for(idet=0;idet<ndet;idet++)
 {
  norm=norm+Cdet[idet].Coef*Cdet[idet].Coef;
 }
 cout<<" Sum_I | C_I |^2 = "<<setw(20)<<norm<<" N system (normalized)"<<endl;
 cout<<endl;
 delete[] index;index=NULL;
}

void ovlp_nm1_an_n_system(Input Input_commands,vector<C_det>&Cdet,double **Nm1_an_N)
{
 bool active;
 size_t idet,ielec,istate,*ndet,*index;
 double val,*fact_norm;
 string line;
 ndet=new size_t[Input_commands.file_Nm1.size()];
 index=new size_t[Input_commands.nelectrons-1];
 fact_norm=new double[Input_commands.file_Nm1.size()];
 for(istate=0;istate<Input_commands.file_Nm1.size();istate++){fact_norm[istate]=ZERO;}
 // Compute normalization factors N-1 systems
 for(istate=0;istate<Input_commands.file_Nm1.size();istate++)
 {
  active=false;
  ndet[istate]=0;
  ifstream read_Nm1(Input_commands.file_Nm1[istate]);
  while(getline(read_Nm1,line))
  {
   if(line==" Final CI vector")
   {
    active=true;
    getline(read_Nm1,line);
   }
   if(line==" /EOF"){active=false;}
   if(active){ndet[istate]++;}
  }
  read_Nm1.close();
  ndet[istate]--;
  read_Nm1.open(Input_commands.file_Nm1[istate]);
  while(getline(read_Nm1,line))
  {
   if(line==" Final CI vector")
   {
    getline(read_Nm1,line);
    for(idet=0;idet<ndet[istate];idet++)
    {
     read_Nm1>>val;
     for(ielec=0;ielec<Input_commands.nelectrons-1;ielec++)
     {
      read_Nm1>>index[ielec];
     }
     fact_norm[istate]=fact_norm[istate]+val*val;
    } 
   }
  }
  read_Nm1.close();
  fact_norm[istate]=ONE/sqrt(fact_norm[istate]);
 }  

 delete[] fact_norm;fact_norm=NULL;
 delete[] index;index=NULL;
 delete[] ndet;ndet=NULL;
}


