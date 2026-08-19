#ifndef _Gpq_VERSION_H_
#define _Gpq_VERSION_H_
#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<cstring>
#include<complex>
#include"Input_commands.h"

using namespace std;
complex<double>CZERO(ZERO,ZERO);
complex<double>im(ZERO,ONE);
void build_Gpq_tau(double &tau,Input Input_commands,double **Np1_cr_N, double **Nm1_an_N,complex<double> **Gpq);
void build_Gpq_w(double &wfreq,Input Input_commands,double **Np1_cr_N, double **Nm1_an_N,complex<double> **Gpq);
void build_Gpq_w_Retarded(double &wfreq,Input Input_commands,double **Np1_cr_N, double **Nm1_an_N,complex<double> **Gpq);

#endif // _Gpq_VERSION_H_

