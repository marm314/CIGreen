#include"io.h"

void read_nsystem(Input Input_commands,vector<C_det>&Cdet)
{
 bool active=false;
 size_t idet,ielec,ndet=0,*index;
 double val,norm=ZERO;
 index=new size_t[Input_commands.nelectrons];
 string line;
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
 cout<<endl;
 delete index;index=NULL;
}

