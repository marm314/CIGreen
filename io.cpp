#include"io.h"

void read_nsystem(Input Input_commands,vector<C_det>&Cdet)
{
 bool active=false;
 int nSwaps;
 size_t idet,ielec,jelec,ndet=0,*index;
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
 // Sort the Slater determinants spin-up | spin-down separately by spin-channel
 for(idet=0;idet<ndet;idet++)
 {
  // Sort spin-up states in Slater det.
  nSwaps=0;
  for(ielec=0;ielec<Input_commands.nelectrons/2;++ielec)
  {
   for(jelec=ielec+1;jelec<Input_commands.nelectrons/2;++jelec)
   {
    if(Cdet[idet].indices_ref[ielec] > Cdet[idet].indices_ref[jelec])
    {
     ++nSwaps;
    }
   }
  }
  if(nSwaps & 1) Cdet[idet].Coef=-Cdet[idet].Coef;
  sort(Cdet[idet].indices_ref.begin(),Cdet[idet].indices_ref.begin()+Input_commands.nelectrons/2);
  // Sort spin-down states in Slater det.
  nSwaps=0;
  for(ielec=Input_commands.nelectrons/2;ielec<Input_commands.nelectrons;++ielec)
  {
   for(jelec=ielec+1;jelec<Input_commands.nelectrons;++jelec)
   {
    if(Cdet[idet].indices_ref[ielec] > Cdet[idet].indices_ref[jelec])
    {
     ++nSwaps;
    }
   }
  }
  if(nSwaps & 1) Cdet[idet].Coef=-Cdet[idet].Coef;
  sort(Cdet[idet].indices_ref.begin()+Input_commands.nelectrons/2,Cdet[idet].indices_ref.begin()+Input_commands.nelectrons);
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
 delete[] index;index=NULL;
}

void ovlp_nm1_an_n_system(Input Input_commands,vector<C_det>&Cdet,double **Nm1_an_N)
{
 bool active;
 int nSwaps;
 size_t ibas,jbas,kbas,idet,jdet,ielec,jelec,istate,*ndet,*index;
 double val,Coef_nm1,*fact_norm;
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
  cout<<" Sum_I | C_I |^2 = "<<setw(20)<<fact_norm[istate]<<" N-1 system"<<endl;
  fact_norm[istate]=ONE/sqrt(fact_norm[istate]);
 }  
 // For each column of Nm1_an_N[istate][ibas] (basis) compute the N-1 states overlap
 for(ibas=0;ibas<Input_commands.nBasis;ibas++)
 {
  // First switch off determinants in the N system that do not contain ibas 
  for(idet=0;idet<Cdet.size();idet++)
  {
   Cdet[idet].active=true;
   if(! (find(Cdet[idet].indices_ref.begin(), Cdet[idet].indices_ref.end(),ibas+1)!=Cdet[idet].indices_ref.end() ) ){Cdet[idet].active=false;}
  }
  // Extract the rest of indices for the active determinants that contain ibas and build the column overlap
  for(idet=0;idet<Cdet.size();idet++)
  {
   if(Cdet[idet].active)
   {
    // Extract indices from N after annihilation of ibas
    vector<int>indices_tmp;
    for(jbas=0;jbas<Input_commands.nelectrons;jbas++)
    {
     if(Cdet[idet].indices_ref[jbas]!=ibas+1)
     {
      indices_tmp.push_back(Cdet[idet].indices_ref[jbas]);
     }
    }
    // Read for each state (N-1) indices (sorting them) and adding phases to the coefs to compute < N-1 | anh_ibas | N >
    for(istate=0;istate<Input_commands.file_Nm1.size();istate++)
    {
     ifstream read_Nm1(Input_commands.file_Nm1[istate]);
     while(getline(read_Nm1,line))
     {
      if(line==" Final CI vector")
      {
       for(jdet=0;jdet<ndet[istate];jdet++)
       {
        vector<int>indices_tmp2;
        // Read a coef of N-1 CI vector (and correct the normalization)
        read_Nm1>>Coef_nm1;
        Coef_nm1=Coef_nm1/sqrt(fact_norm[istate]);
        // Read infices of N-1 CI vector
        for(jbas=0;jbas<Input_commands.nelectrons-1;jbas++)
        {
         read_Nm1>>kbas;
         indices_tmp2.push_back(kbas);
        }
        // Sort the spin up and spin down indices (adjusting the sign of Coef_nm1)
         // Sort spin-up states in Slater det. of N-1
         nSwaps=0;
         for(ielec=0;ielec<Input_commands.nelectrons/2-1;++ielec)
         {
          for(jelec=ielec+1;jelec<Input_commands.nelectrons/2-1;++jelec)
          {
           if(indices_tmp2[ielec] > indices_tmp2[jelec])
           {
            ++nSwaps;
           }
          }
         }
         if(nSwaps & 1) Coef_nm1=-Coef_nm1;
         sort(indices_tmp2.begin(),indices_tmp2.begin()+Input_commands.nelectrons/2-1);
         // Sort spin-down states in Slater det. of N-1
         nSwaps=0;
         for(ielec=Input_commands.nelectrons/2-1;ielec<Input_commands.nelectrons-1;++ielec)
         {
          for(jelec=ielec+1;jelec<Input_commands.nelectrons-1;++jelec)
          {
           if(indices_tmp2[ielec] > indices_tmp2[jelec])
           {
            ++nSwaps;
           }
          }
         }
         if(nSwaps & 1) Coef_nm1=-Coef_nm1;
         sort(indices_tmp2.begin()+Input_commands.nelectrons/2-1,indices_tmp2.begin()+Input_commands.nelectrons-1);
        // Compute overlap N-1 and N and store it at Nm1_an_N[istate][ibas]
        if(indices_tmp==indices_tmp2)
        {
         Nm1_an_N[istate][ibas]+=Coef_nm1*Cdet[idet].Coef;
        }
       }
      }
     }
     read_Nm1.close();
    }
   }
  }
 }
 for(istate=0;istate<Input_commands.file_Nm1.size();istate++)
 {
  for(ibas=0;ibas<Input_commands.nBasis;ibas++)
  {
   cout<<setw(20)<<Nm1_an_N[istate][ibas];
  }
  cout<<endl;
 }
 delete[] fact_norm;fact_norm=NULL;
 delete[] index;index=NULL;
 delete[] ndet;ndet=NULL;
}


