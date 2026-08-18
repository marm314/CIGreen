#ifndef _IO_VERSION_H_
#define _IO_VERSION_H_
#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<cstring>
#include"Input_commands.h"

using namespace std;
void read_nsystem(Input Input_commands,vector<C_det>&Cdet);
void ovlp_nm1_an_n_system(Input Input_commands,vector<C_det>&Cdet,double **Nm1_an_N);
void ovlp_np1_cr_n_system(Input Input_commands,vector<C_det>&Cdet,double **Np1_cr_N);

#endif // _IO_VERSION_H_

