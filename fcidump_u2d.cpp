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
 cout<<"---  Swap the spin on the FCIDUMP.out    ---"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"-- Developed by: Dr. M. Rodriguez-Mayorga --"<<endl;
 cout<<"--      email: marm3.14@gmail.com         --"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 cout<<"--------------------------------------------"<<endl; 
 if(argc!=5)
 {
  cout<<"Include the input file"<<endl;
  cout<<"./fcidump_u2d nBasis nElectrons Delta_spin_up_spin_down FCIDUMP.out"<<endl;
  cout<<endl;
  cout<<"----------------------------------------"<<endl;
  cout<<"--        Normal termination          --"<<endl;
  cout<<"----------------------------------------"<<endl;
  cout<<"----------------------------------------"<<endl;
  return 0;
 }
 bool active=false;
 int nBasis=atoi(argv[1]);
 int nElectrons=atoi(argv[2]);
 int Delta_ud=atoi(argv[3]);
 int idet,ielec,ndet=0,*index,nSpinUp;
 double val;
 nSpinUp=(nElectrons+Delta_ud)/2;
 string file=argv[4];
 string line;
 index=new int[nElectrons];
 ifstream read_N(file);
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
 ofstream write_N((file+"_u2d").c_str());
 write_N<<setprecision(12)<<scientific<<fixed;
 read_N.open(file);
 while(getline(read_N,line))
 {
  if(line==" Final CI vector")
  {
   write_N<<line<<endl;
   write_N<<endl;
   getline(read_N,line);
   for(idet=0;idet<ndet;idet++)
   {
    read_N>>val;
    write_N<<setw(21)<<val; 
    for(ielec=0;ielec<nElectrons;ielec++)
    {
     read_N>>index[ielec];
    }
    for(ielec=nSpinUp;ielec<nElectrons;ielec++)
    {
     write_N<<setw(3)<<index[ielec]; 
    }
    for(ielec=0;ielec<nSpinUp;ielec++)
    {
     write_N<<setw(3)<<index[ielec]+nBasis; 
    }
    write_N<<endl;
   }
   write_N<<" /EOF"<<endl;
  }
  else
  {
   if(line!=" /EOF")
   {
    write_N<<line<<endl;
   }
  }
 }
 read_N.close();
 write_N.close();
 delete[] index;index=NULL;
 cout<<endl;
 cout<<" See the file "<<file+"_u2d"<<endl;
 cout<<endl;
 cout<<"----------------------------------------"<<endl;
 cout<<"--        Normal termination          --"<<endl;
 cout<<"----------------------------------------"<<endl;
 cout<<"----------------------------------------"<<endl;
 return 0;
}
