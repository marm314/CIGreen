#ifndef _INPUT_COMMANDS_H_
#define _INPUT_COMMANDS_H_

#include<iostream>
#include<algorithm>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<stdio.h>
#include<iomanip>
#include<vector>
#include"String_ops.h"
#include"Numbers.h"

using namespace std;
//////////////////////////
//Functions declaration //
//////////////////////////
struct C_det // Slater determinant information
{
 double Coef;
 bool active;
 vector<size_t>indices_ref;
};
class Input // Input information
{
 private:
 size_t icount;
 public:
 bool time;
 size_t nBasis,nelectrons;
 double En;
 double t0,tlast,tstep;
 vector<double>Enp1;
 vector<double>Enm1;
 string file_N;
 vector<string>file_Np1;
 vector<string>file_Nm1;
 Input();
 Input(string);
 ~Input();
};
#endif // _INPUT_COMMANDS_H_



