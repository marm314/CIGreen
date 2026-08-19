#include"Input_commands.h"
Input::Input(){cout<<"Not allowed default constructor"<<endl;}
Input::Input(string cigreen_in)
{
 size_t nP1,nM1;
 double val;
 time=false;freq=false;imfreq=false;imtime=false;
 nBasis=0;nP1=0;nM1=0;
 string name;
 ifstream cigreen_input_file;
 cigreen_in.erase(std::remove_if(cigreen_in.begin(),cigreen_in.end(),::isspace),cigreen_in.end());
 cigreen_input_file.open((cigreen_in).c_str());
 if(cigreen_input_file.good()) //Check existence of file
 {
  while(getline(cigreen_input_file,cigreen_in))
  {
   cigreen_in.erase(std::remove_if(cigreen_in.begin(),cigreen_in.end(),::isspace),cigreen_in.end());
   lowercase(cigreen_in);
   if(cigreen_in=="#nsystem")
   {
    getline(cigreen_input_file,cigreen_in);
    cigreen_in.erase(std::remove_if(cigreen_in.begin(),cigreen_in.end(),::isspace),cigreen_in.end());
    file_N=cigreen_in;
    cigreen_input_file>>En;
   }
   else if(cigreen_in=="#nbasis"){cigreen_input_file>>nBasis;}
   else if(cigreen_in=="#nelectrons"){cigreen_input_file>>nelectrons;}
   else if(cigreen_in=="#n+1system")
   {
    cigreen_input_file>>nP1;
    for(icount=0;icount<nP1;icount++)
    {
     cigreen_input_file>>val;
     Enp1.push_back(val);
    }
    icount=0;
    do
    {
     do
     {
      getline(cigreen_input_file, cigreen_in);
      cigreen_in.erase(std::remove_if(cigreen_in.begin(),cigreen_in.end(),::isspace),cigreen_in.end());
      name=cigreen_in;
     }while(name=="");
     file_Np1.push_back(name);
     icount++;
    }while(icount<nP1);
   }
   else if(cigreen_in=="#n-1system")
   {
    cigreen_input_file>>nM1;
    for(icount=0;icount<nM1;icount++)
    {
     cigreen_input_file>>val;
     Enm1.push_back(val);
    }
    icount=0;
    do
    {
     do
     {
      getline(cigreen_input_file, cigreen_in);
      cigreen_in.erase(std::remove_if(cigreen_in.begin(),cigreen_in.end(),::isspace),cigreen_in.end());
      name=cigreen_in;
     }while(name=="");
     file_Nm1.push_back(name);
     icount++;
    }while(icount<nM1);
   }
   else if(cigreen_in=="#time")
   {
    time=true;
    cigreen_input_file>>t0>>tlast>>tstep;
   }
   else if(cigreen_in=="#frequency")
   {
    freq=true;
    cigreen_input_file>>w0>>wlast>>wstep>>weta;
   }
   else if(cigreen_in=="#imtime"){imtime=true;}
   else if(cigreen_in=="#imfrequency"){imfreq=true;}
   else{}
  }
 }
 else
 {cout<<"File "<<name<<" not found!"<<endl;}
}
Input::~Input()
{
}
