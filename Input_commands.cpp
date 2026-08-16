#include"Input_commands.h"
Input::Input(){cout<<"Not allowed default constructor"<<endl;}
Input::Input(string rho_in)
{
 nBasis=0;nBasis2=0;
 string name=rho_in;
 ifstream rho_input_file;
 rho_in.erase(std::remove_if(rho_in.begin(),rho_in.end(),::isspace),rho_in.end());
 rho_input_file.open((rho_in).c_str());
 if(rho_input_file.good()) //Check existence of file
 {
  while(getline(rho_input_file,rho_in))
  {
   rho_in.erase(std::remove_if(rho_in.begin(),rho_in.end(),::isspace),rho_in.end());
   lowercase(rho_in);
   if(rho_in=="$name")
   {
    getline(rho_input_file,rho_in);
    rho_in.erase(std::remove_if(rho_in.begin(),rho_in.end(),::isspace),rho_in.end());
//   name_fchk_wfn=rho_in;
   }
   else if(rho_in=="$nbasis"){rho_input_file>>nBasis;nBasis2=2*nBasis;}
   else{}
  }
 }
 else
 {cout<<"File "<<name<<" not found!"<<endl;}
}
Input::~Input()
{
}
